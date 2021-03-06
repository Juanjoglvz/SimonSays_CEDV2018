// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SimonPawn.h"
#include "SimonBlock.h"
#include "SimonManager.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ASimonPawn::ASimonPawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ASimonPawn::BeginPlay()
{
	Super::BeginPlay();
	//Get a reference to the Simon Manager
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Contains(FString("SimonManager")))
		{
			// Conversion to smart pointer
			SimonManager = Cast<ASimonManager>(*ActorItr);
			break;
		}
	}

}

void ASimonPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FVector Start, Dir, End;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		End = Start + (Dir * 8000.0f);
		TraceForBlock(Start, End);
	}
}

void ASimonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &ASimonPawn::TriggerClick);
}

void ASimonPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}

void ASimonPawn::TriggerClick()
{
	if (CurrentBlockFocus)
	{
		if (SimonManager->isPlaying)
		{
			CurrentBlockFocus->Activate(false);
			SimonManager->NotifyBlockClicked(CurrentBlockFocus);
		}
	}
}

void ASimonPawn::TraceForBlock(const FVector& Start, const FVector& End)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (HitResult.Actor.IsValid())
	{
		ASimonBlock* HitBlock = Cast<ASimonBlock>(HitResult.Actor.Get());
		if (CurrentBlockFocus != HitBlock)
		{
			if (CurrentBlockFocus)
			{
				CurrentBlockFocus->OnMouseHover(false);
			}
			if (HitBlock)
			{
				if (SimonManager->isPlaying)
					HitBlock->OnMouseHover(true);
			}
			CurrentBlockFocus = HitBlock;
		}
	}
	else if (CurrentBlockFocus)
	{
		//CurrentBlockFocus->Highlight(false);
		CurrentBlockFocus = nullptr;
	}
}