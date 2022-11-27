// Copyright Epic Games, Inc. All Rights Reserved.

#include "MinecraftUEHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


AMinecraftUEHUD::AMinecraftUEHUD()
{
	HUDState = EHUDState::HS_Ingame;
}


void AMinecraftUEHUD::ApplyHUDChanges()
{
	/* ������ HUD�� �����ϰ�, �� ���� �����Ѵ�.*/
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromParent();
	}

	/* HUD ���¸� üũ�ϰ�, �׿� �����ϴ� HUD ���� */
	switch (HUDState)
	{
	case EHUDState::HS_Ingame:
	{
		ApplyHUD(IngameHUDClass, false, false);
		break;
	}
	case EHUDState::HS_Inventory:
	{
		ApplyHUD(InventoryHUDClass, true, true);
		break;
	}
	case EHUDState::HS_Craft_Menu:
	{
		ApplyHUD(CraftMenuHUDClass, true, true);
		break;
	}
	default:
	{
		ApplyHUD(IngameHUDClass, false, false);
		break;
	}
	}
}

uint8 AMinecraftUEHUD::GetHUDState()
{
	return HUDState;
}

void AMinecraftUEHUD::SetHUDState(EHUDState state)
{
	HUDState = state;
}

void AMinecraftUEHUD::ChangeHUDState(uint8 NewState)
{
	HUDState = NewState;
	// ApplyHUDChanges();
}

bool AMinecraftUEHUD::ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool ShowMouseCursor, bool EnableClickEvents)
{

	if (WidgetToApply != nullptr)
	{
		/* Set Mouse event and visibility */
		PlayerOwner->bShowMouseCursor = ShowMouseCursor;
		PlayerOwner->bEnableClickEvents = EnableClickEvents;

		/* ���� ���� */
		CurrentWidget = CreateWidget<UUserWidget, APlayerController>(PlayerOwner, WidgetToApply);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
			// CurrentWidget->AddToPlayerScreen();
			return true;
		}
		else
			return false;
	}
	else
		return false;
}