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
	virtual void NativeConstruct() override;

	void BindCharacterStat(class USomABCharacterStatComponent* NewCharacterStat);
	
protected:
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class USomABCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;

protected:

public:

};