// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABGamePlayResultWidget.h"
#include "SomArenaBattle.h"
#include "Components/TextBlock.h"
#include "Core/SomABGameState.h"

void USomABGamePlayResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ABCHECK(CurrentGameState.IsValid());

	UTextBlock* Result = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtResult")));
	ABCHECK(Result != nullptr);
	Result->SetText(FText::FromString(CurrentGameState->IsGameCleared() ? TEXT("Mission Complete") : TEXT("Mission Failed")));

	UTextBlock* TotalScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtTotalScore")));
	ABCHECK(TotalScore != nullptr);
	TotalScore->SetText(FText::FromString(FString::FromInt(CurrentGameState->GetTotalGameScore())));
}

void USomABGamePlayResultWidget::BindGameState(ASomABGameState* GameState)
{
	ABCHECK(GameState != nullptr);
	CurrentGameState = GameState;
}
