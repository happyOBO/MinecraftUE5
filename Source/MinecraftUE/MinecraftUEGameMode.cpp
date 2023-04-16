// Copyright Epic Games, Inc. All Rights Reserved.

#include "MinecraftUEGameMode.h"
#include "MinecraftUEHUD.h"
#include "MinecraftUECharacter.h"
#include "UObject/ConstructorHelpers.h"

AMinecraftUEGameMode::AMinecraftUEGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));

	if (PlayerPawnClassFinder.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnClassFinder.Class;
	}
	
	// use our custom HUD class
	HUDClass = AMinecraftUEHUD::StaticClass();

	LoadWieldableInfo();
}

void AMinecraftUEGameMode::BeginPlay()
{
	Super::BeginPlay();
}

UDataTable* AMinecraftUEGameMode::LoadObjFromPath(const FName& Path)
{
	if (Path == NAME_None) return nullptr;

	return Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *Path.ToString()));

}

void AMinecraftUEGameMode::LoadWieldableInfo()
{
	FString context;
	UDataTable* WieldableInfoDataTable = LoadObjFromPath(TEXT("DataTable'/Game/DataTable/WieldableIDTable.WieldableIDTable'"));
	
	TArray<FWieldableData*> WieldableInfoTable;
	if (WieldableInfoDataTable != nullptr)
		WieldableInfoDataTable->GetAllRows(context, WieldableInfoTable);

	for (int32 i = 0; i < WieldableInfoTable.Num(); i++)
	{
		WieldableInfo.FindOrAdd(WieldableInfoTable[i]->ID, LoadWieldableItemClass(WieldableInfoTable[i]->WieldableItemPath));
		if(0 < WieldableInfoTable[i]->Recipe.Len() )
			WieldableItemRecipe.FindOrAdd(WieldableInfoTable[i]->Recipe, WieldableInfoTable[i]->ID);
	}

}



AWieldable* AMinecraftUEGameMode::GetWieldableItemFromID(int32 ID)
{
	return nullptr;
}


TSubclassOf<AWieldable> AMinecraftUEGameMode::LoadWieldableItemClass(FString WieldableItemPath)
{
	ConstructorHelpers::FClassFinder<AWieldable> WieldableClassAsset(*WieldableItemPath);
	if (WieldableClassAsset.Succeeded())
	{
		return WieldableClassAsset.Class;
	}

	return nullptr;
}

TSubclassOf<AWieldable> AMinecraftUEGameMode::GetWieldableItemClassFromID(int32 ID)
{
	if (!WieldableInfo.Contains(ID)) return nullptr;
	return WieldableInfo[ID];
}


int32 AMinecraftUEGameMode::GetWieldableItemIDFromRecipe(FString Recipe)
{
	if (!WieldableItemRecipe.Contains(Recipe)) return -1;
	return WieldableItemRecipe[Recipe];
}

