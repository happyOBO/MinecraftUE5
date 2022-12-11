// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"


// Sets default values
ABlock::ABlock()
{
	bReplicates = true;
	SM_Block = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	DefaultBreakingStage = 10.f;
	BreakingStage = DefaultBreakingStage;
	MinimumMaterial = 0;
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);

}

void ABlock::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABlock, BreakingStage);
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABlock::Break(AWieldable* WieldableItem)
{
	if (BreakingStage <= 0.f)
	{
		OnBroken(true);
	}

	else if (WieldableItem && 0.f < WieldableItem->ToolPower)
	{
		BreakingStage = FMath::Min(DefaultBreakingStage, BreakingStage - (1.0f + WieldableItem->ToolPower));
	}
	else
	{
		BreakingStage -= 1.0f;
	}

	if (GetNetMode() == NM_Standalone)
	{
		OnRep_Breaking();
	}
	// SetBreakBlockMaterial();

}

void ABlock::ResetBlock()
{
	BreakingStage = DefaultBreakingStage;
	UMaterialInstanceDynamic* MatInstance = SM_Block->CreateDynamicMaterialInstance(0);

	if (MatInstance != nullptr)
	{
		MatInstance->SetScalarParameterValue(FName("CrackingValue"), 1.0f);
	}
}

void ABlock::OnBroken(bool HasRequiredPickaxe)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBroken_Implementation"));
	GetWorld()->SpawnActor<AActor>(WieldableBlock, GetActorLocation(), GetActorRotation());

	Destroy();
}

void ABlock::OnRep_Breaking()
{

	SetBreakBlockMaterial();

	UE_LOG(LogTemp, Warning, TEXT("OnRep_Breaking %f"), BreakingStage);
	if (BreakingStage <= 0.f)
	{
		OnBroken(true);
	}

}

void ABlock::SetBreakBlockMaterial()
{
	float CrackingValue = BreakingStage / DefaultBreakingStage; // 1 0.9 ... 0.1
	UE_LOG(LogTemp, Warning, TEXT("SetBreakBlockMaterial %f"), BreakingStage);
	UMaterialInstanceDynamic* MatInstance = SM_Block->CreateDynamicMaterialInstance(0);

	if (MatInstance != nullptr)
	{
		MatInstance->SetScalarParameterValue(FName("CrackingValue"), CrackingValue);
	}
}


