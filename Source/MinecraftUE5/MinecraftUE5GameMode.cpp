// Copyright Epic Games, Inc. All Rights Reserved.

#include "MinecraftUE5GameMode.h"
#include "MinecraftUE5Character.h"
#include "UObject/ConstructorHelpers.h"

AMinecraftUE5GameMode::AMinecraftUE5GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
