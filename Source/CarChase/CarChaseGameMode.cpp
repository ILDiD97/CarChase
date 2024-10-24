// Copyright Epic Games, Inc. All Rights Reserved.

#include "CarChaseGameMode.h"
#include "CarChasePlayerController.h"

ACarChaseGameMode::ACarChaseGameMode()
{
	PlayerControllerClass = ACarChasePlayerController::StaticClass();
}
