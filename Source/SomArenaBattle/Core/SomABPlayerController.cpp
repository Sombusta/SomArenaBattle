// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABPlayerController.h"
#include "SomArenaBattle.h"

ASomABPlayerController::ASomABPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASomABPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ABLOG_S(Warning);
}

void ASomABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

}

void ASomABPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void ASomABPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASomABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}

void ASomABPlayerController::OnPossess(APawn* InPawn)
{
	ABLOG_S(Warning);
	Super::OnPossess(InPawn);	
}