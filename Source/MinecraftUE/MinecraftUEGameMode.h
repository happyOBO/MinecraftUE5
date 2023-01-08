// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/DataTable.h"
#include "TypeDef.h"
#include "Wieldable.h"
#include "MinecraftUEGameMode.generated.h"

UCLASS(minimalapi)
class AMinecraftUEGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMinecraftUEGameMode();

	UPROPERTY()
	TMap<int32, TSubclassOf<AWieldable>> WieldableInfo;
	UPROPERTY()
	TMap<FString, int32> WieldableItemRecipe;

	AWieldable* GetWieldableItemFromID(int32 ID);
	TSubclassOf<AWieldable> LoadWieldableItemClass(FString ID);
	TSubclassOf<AWieldable> GetWieldableItemClassFromID(int32 ID);
	int32 GetWieldableItemIDFromRecipe(FString Recipe);

protected:
	virtual void BeginPlay() override;
	UDataTable* LoadObjFromPath(const FName& Path);
	void LoadWieldableInfo();


};



