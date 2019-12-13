// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABHUDWidget.h"
#include "SomArenaBattle.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Libraries/Components/SomABCharacterStatComponent.h"
#include "Core/SomABPlayerState.h"

void USomABHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	ABCHECK(HPBar != nullptr);

	ExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbExp")));
	ABCHECK(ExpBar != nullptr);

	PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayerName")));
	ABCHECK(PlayerName != nullptr);

	PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
	ABCHECK(PlayerLevel != nullptr);

	CurrentScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentScore")));
	ABCHECK(CurrentScore != nullptr);

	HighScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtHighScore")));
	ABCHECK(HighScore != nullptr);
}

void USomABHUDWidget::BindCharacterStat(USomABCharacterStatComponent* CharacterStat)
{
	ABCHECK(CharacterStat != nullptr);

	CurrentCharacterStat = CharacterStat;
	CharacterStat->OnHPChanged.AddUObject(this, &USomABHUDWidget::UpdateCharacterStat);
}

void USomABHUDWidget::BindPlayerState(ASomABPlayerState* PlayerStat)
{
	ABCHECK(PlayerStat != nullptr);

	CurrentPlayerState = PlayerStat;
	PlayerStat->OnPlayerStateChanged.AddUObject(this, &USomABHUDWidget::UpdatePlayerState);
}

void USomABHUDWidget::UpdateCharacterStat()
{
	ABCHECK(CurrentCharacterStat.IsValid());

	HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}

void USomABHUDWidget::UpdatePlayerState()
{
	ABCHECK(CurrentPlayerState.IsValid());

	ExpBar->SetPercent(CurrentPlayerState->GetExpRatio());
	PlayerName->SetText(FText::FromString(CurrentPlayerState->GetPlayerName()));
	PlayerLevel->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCharacterLevel())));
	CurrentScore->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetGameScore())));
}