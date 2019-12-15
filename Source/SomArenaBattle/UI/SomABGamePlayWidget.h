// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SomABGamePlayWidget.generated.h"

UCLASS()
class SOMARENABATTLE_API USomABGamePlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void OnResumeClicked();

	UFUNCTION()
	void OnReturnToTitleClicked();

	UFUNCTION()
	void OnRetryGameClicked();

protected:
	UPROPERTY()
	class UButton* ResumeButton;

	UPROPERTY()
	class UButton* ReturnToTitleButton;

	UPROPERTY()
	class UButton* RetryGameButton;
	
};