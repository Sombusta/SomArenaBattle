// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "SomArenaBattle.h"
#include "UI/SomABHUDWidget.h"
#include "Core/SomABPlayerState.h"
#include "Player/SomAB_TPCharacter.h"

ASomABPlayerController::ASomABPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<USomABHUDWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/Book/UI/UI_HUD.UI_HUD_C'"));
	
	if (UI_HUD.Succeeded()) HUDWidgetClass = UI_HUD.Class;
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

	HUDWidget = CreateWidget<USomABHUDWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();

	SomABPlayerState = Cast<ASomABPlayerState>(PlayerState);
	ABCHECK(SomABPlayerState != nullptr);

	HUDWidget->BindPlayerState(SomABPlayerState);
	SomABPlayerState->OnPlayerStateChanged.Broadcast();
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

	// InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &ASomABPlayerController::OnGamePause);
	InputComponent->BindKey(EKeys::M, EInputEvent::IE_Pressed, this, &ASomABPlayerController::OnGamePause);
}

void ASomABPlayerController::OnPossess(APawn* InPawn)
{
	ABLOG_S(Warning);
	Super::OnPossess(InPawn);	
}

void ASomABPlayerController::NPCKill(ASomAB_TPCharacter* KilledNPC) const
{
	SomABPlayerState->AddExp(KilledNPC->GetExp());
}

void ASomABPlayerController::AddGameScore() const
{
	SomABPlayerState->AddGameScore();
}

void ASomABPlayerController::OnGamePause()
{
}
