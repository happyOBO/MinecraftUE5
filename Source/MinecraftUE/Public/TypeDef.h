// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "TypeDef.generated.h"

/** 레벨 업 표 항목을 정의하는 구조체 */
USTRUCT(BlueprintType)
struct FLevelUpData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FLevelUpData()
		: XPtoLvl(0)
		, AdditionalHP(0)
	{}

	/** 'Name' 열은 XP Level 과 같습니다. */

	/** 이전 레벨에서 해당 레벨로 가기 위해 필요한 XP 입니다. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		int32 XPtoLvl;

	/** 이 레벨에서 얻은 추가 HP 입니다. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		int32 AdditionalHP;

	/** 업적에 사용할 아이콘입니다. */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
	//	TSoftObjectPtr<UTexture> AchievementIcon;
};


USTRUCT(BlueprintType)
struct FWieldableData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FWieldableData()
		: ID(0)
	{}

	int ID;

};

