// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SomABHUDWidget.generated.h"

UCLASS()
class SOMARENABATTLE_API USomABHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	class UProgressBar* HPBar;

	UPROPERTY()
	class UProgressBar* ExpBar;

	UPROPERTY()
	class UTextBlock* PlayerName;

	UPROPERTY()
	class UTextBlock* PlayerLevel;

	UPROPERTY()
	class UTextBlock* CurrentScore;

	UPROPERTY()
	class UTextBlock* HighScore;
	
public:
	virtual void NativeConstruct() override;
		
	void BindCharacterStat(class USomABCharacterStatComponent* CharacterStat);
	void BindPlayerState(class ASomABPlayerState* PlayerStat);

protected:
	void UpdateCharacterStat();
	void UpdatePlayerState();

private:
	TWeakObjectPtr<class USomABCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<class ASomABPlayerState> CurrentPlayerState;

};