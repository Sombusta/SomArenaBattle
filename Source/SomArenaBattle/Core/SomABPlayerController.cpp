// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "SomArenaBattle.h"
#include "Core/SomABPlayerState.h"
#include "Core/SomABGameState.h"
#include "Player/SomAB_TPCharacter.h"
#include "UI/SomABHUDWidget.h"
#include "UI/SomABGamePlayWidget.h"
#include "UI/SomABGamePlayResultWidget.h"

ASomABPlayerController::ASomABPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<USomABHUDWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/Book/UI/UI_HUD.UI_HUD_C'"));
	static ConstructorHelpers::FClassFinder<USomABGamePlayWidget> UI_Menu(TEXT("WidgetBlueprint'/Game/Book/UI/UI_Menu.UI_Menu_C'"));
	static ConstructorHelpers::FClassFinder<USomABGamePlayResultWidget> UI_Result(TEXT("WidgetBlueprint'/Game/Book/UI/UI_Result.UI_Result_C'"));
	
	if (UI_HUD.Succeeded()) HUDWidgetClass = UI_HUD.Class;
	if (UI_Menu.Succeeded()) MenuWidgetClass = UI_Menu.Class;
	if (UI_Result.Succeeded()) ResultWidgetClass = UI_Result.Class;
}

void ASomABPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ABLOG_S(Warning);
}

void ASomABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);

	HUDWidget = CreateWidget<USomABHUDWidget>(this, HUDWidgetClass);
	ABCHECK(HUDWidget != nullptr);
	HUDWidget->AddToViewport(1);

	SomABPlayerState = Cast<ASomABPlayerState>(PlayerState);
	ABCHECK(SomABPlayerState != nullptr);

	HUDWidget->BindPlayerState(SomABPlayerState);
	SomABPlayerState->OnPlayerStateChanged.Broadcast();

	ResultWidget = CreateWidget<USomABGamePlayResultWidget>(this, ResultWidgetClass);
	ABCHECK(ResultWidget != nullptr);
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

void ASomABPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIIpuntMode);
		bShowMouseCursor = true;
	}
}

void ASomABPlayerController::ShowResultUI()
{
	ASomABGameState* SomABGameState = Cast<ASomABGameState>(UGameplayStatics::GetGameState(this));
	ABCHECK(SomABGameState != nullptr);
	ResultWidget->BindGameState(SomABGameState);
	
	ResultWidget->AddToViewport();
	ChangeInputMode(false);
}

void ASomABPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<USomABGamePlayWidget>(this, MenuWidgetClass);
	ABCHECK(MenuWidget != nullptr);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}