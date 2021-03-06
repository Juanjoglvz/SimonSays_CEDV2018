// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimonGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ASimonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASimonGameMode();

	// Variables to choose the game mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	bool bIsEasy;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	bool bIsMedium;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	bool bIsHard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	bool bIsEndless;

	UFUNCTION(BlueprintCallable)
		void SetColorBlind(bool IsColorblind);

	UFUNCTION(BlueprintCallable)
		void SetVolume(float volume);

	UFUNCTION(BlueprintCallable)
		void SetPianoAudio(bool piano);

	UFUNCTION(BlueprintCallable)
		float GetVolume() const;

	UFUNCTION(BlueprintCallable)
		bool GetPiano() const;

	UFUNCTION(BlueprintCallable)
		bool GetColorBlind() const;
};

static float Volume = 0.75;

static bool Piano = false;

static bool ColorBlind = false;