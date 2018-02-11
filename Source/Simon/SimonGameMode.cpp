// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SimonGameMode.h"
#include "SimonPlayerController.h"
#include "SimonPawn.h"

ASimonGameMode::ASimonGameMode()
{
	// no pawn by default
	DefaultPawnClass = ASimonPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ASimonPlayerController::StaticClass();
}
