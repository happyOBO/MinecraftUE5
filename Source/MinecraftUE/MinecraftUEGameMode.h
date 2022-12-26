// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/DataTable.h"
#include "TypeDef.h"
#include "MinecraftUEGameMode.generated.h"

UCLASS(minimalapi)
class AMinecraftUEGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMinecraftUEGameMode();

	UPROPERTY()
	TMap<FString, TSoftObjectPtr<AWieldable>> WieldableInfo;
protected:
	virtual void BeginPlay() override;
	UDataTable* LoadObjFromPath(const FName& Path);
	void LoadWieldableInfo();

};



