// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/SomABGamePlayWidget.h"
#include "SomABGamePlayResultWidget.generated.h"

UCLASS()
class SOMARENABATTLE_API USomABGamePlayResultWidget : public USomABGamePlayWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void BindGameState(class ASomABGameState* GameState);

private:
	TWeakObjectPtr<class ASomABGameState> CurrentGameState;	
};
