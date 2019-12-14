// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABUIPlayerController.h"
#include "SomArenaBattle.h"
#include "Blueprint/UserWidget.h"

ASomABUIPlayerController::ASomABUIPlayerController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASomABUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ABCHECK(UIWidgetClass != nullptr);

	UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
	ABCHECK(UIWidgetInstance != nullptr);

	UIWidgetInstance->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}