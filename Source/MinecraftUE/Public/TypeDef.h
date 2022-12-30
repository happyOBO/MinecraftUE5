// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "MinecraftUE/Wieldable.h"
#include "TypeDef.generated.h"


USTRUCT(BlueprintType)
struct FWieldableData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FWieldableData()
		: ID(0), Recipe("")
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wieldable)
	int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wieldable)
	FString Recipe;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wieldable)
	FString WieldableItemPath;
};

