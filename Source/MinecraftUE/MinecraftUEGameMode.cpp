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
}

void AMinecraftUEGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	LoadWieldableInfo();
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
	WieldableInfoDataTable->GetAllRows(context, WieldableInfoTable);

	for (int32 i = 0; i < WieldableInfoTable.Num(); i++)
	{
		WieldableInfo.FindOrAdd(WieldableInfoTable[i]->ID,WieldableInfoTable[i]->WieldableItemPath);
		if(0 < WieldableInfoTable[i]->Recipe.Len() )
			WieldableItemRecipe.FindOrAdd(WieldableInfoTable[i]->Recipe, WieldableInfoTable[i]->ID);
	}

	UE_LOG(LogTemp, Warning, TEXT("[jeongmj] WieldableInfo.Num() %d"), WieldableInfo.Num());
}



AWieldable* AMinecraftUEGameMode::GetWieldableItemFromID(int32 ID)
{
	if (!WieldableInfo.Contains(ID)) return nullptr;
	FString ItemPath = WieldableInfo[ID];
	return LoadObject<AWieldable>(NULL, *ItemPath, NULL, LOAD_None, NULL);
}


TSubclassOf<AWieldable> AMinecraftUEGameMode::GetWieldableItemClassFromID(int32 ID)
{
	if (!WieldableInfo.Contains(ID)) return nullptr;
	FString ItemPath = WieldableInfo[ID];
	static ConstructorHelpers::FClassFinder<AWieldable> WieldableClassAsset(*ItemPath);
	if (WieldableClassAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("[jeongmj] GetWieldableItemClassFromID %d"), ID);
		return WieldableClassAsset.Class;
	}

	return nullptr;
}

int32 AMinecraftUEGameMode::GetWieldableItemIDFromRecipe(FString Recipe)
{
	if (!WieldableItemRecipe.Contains(Recipe)) return -1;
	UE_LOG(LogTemp, Warning, TEXT("[jeongmj] GetWieldableItemIDFromRecipe %s"), *Recipe);
	return WieldableItemRecipe[Recipe];
}

