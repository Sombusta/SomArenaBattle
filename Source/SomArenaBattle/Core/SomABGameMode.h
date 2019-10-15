// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SomABGameMode.generated.h"

UCLASS(minimalapi)
class ASomABGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASomABGameMode();

	// Called after a successful login.
	virtual void PostLogin(class APlayerController* NewPlayer) override;
};