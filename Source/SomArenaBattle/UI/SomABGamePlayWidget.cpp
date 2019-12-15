// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABGamePlayWidget.h"
#include "SomArenaBattle.h"
#include "Components/Button.h"
#include "Core/SomABPlayerController.h"
#include "Kismet/GameplayStatics.h"

void USomABGamePlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
	if (ResumeButton != nullptr)
	{
		ResumeButton->OnClicked.AddDynamic(this, &USomABGamePlayWidget::OnResumeClicked);
	}

	ReturnToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));
	if (ReturnToTitleButton != nullptr)
	{
		ReturnToTitleButton->OnClicked.AddDynamic(this, &USomABGamePlayWidget::OnReturnToTitleClicked);
	}

	RetryGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnRetryGame")));
	if (RetryGameButton != nullptr)
	{
		RetryGameButton->OnClicked.AddDynamic(this, &USomABGamePlayWidget::OnRetryGameClicked);
	}
}

void USomABGamePlayWidget::OnResumeClicked()
{
	ASomABPlayerController* SomABPlayerController = Cast<ASomABPlayerController>(GetOwningPlayer());
	ABCHECK(SomABPlayerController != nullptr);

	RemoveFromParent();
	SomABPlayerController->ChangeInputMode(true);
	SomABPlayerController->SetPause(false);
}

void USomABGamePlayWidget::OnReturnToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void USomABGamePlayWidget::OnRetryGameClicked()
{
	ASomABPlayerController* SomABPlayerController = Cast<ASomABPlayerController>(GetOwningPlayer());
	ABCHECK(SomABPlayerController != nullptr);
	SomABPlayerController->RestartLevel();
}