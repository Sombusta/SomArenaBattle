// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SomABCharacterWidget.generated.h"

UCLASS()
class SOMARENABATTLE_API USomABCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:	
	void BindCharacterStat(class USomABCharacterStatComponent* NewCharacterStat);
	
	virtual void NativeConstruct() override;

	void UpdateHPWidget();

private:
	TWeakObjectPtr<class USomABCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;

protected:

public:
	
};