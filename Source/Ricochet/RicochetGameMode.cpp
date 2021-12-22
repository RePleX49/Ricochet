// Copyright Epic Games, Inc. All Rights Reserved.

#include "RicochetGameMode.h"
#include "RicochetHUD.h"
#include "RicochetCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARicochetGameMode::ARicochetGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ARicochetHUD::StaticClass();
}
