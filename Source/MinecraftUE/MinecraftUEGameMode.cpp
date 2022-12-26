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
		WieldableInfo.FindOrAdd(WieldableInfoTable[i]->ID,WieldableInfoTable[i]->WieldableItem);
	}

	UE_LOG(LogTemp, Warning, TEXT("[jeongmj] WieldableInfo.Num() %d"), WieldableInfo.Num());
}
