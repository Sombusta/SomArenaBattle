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

	// Called when initialize complete Session
	virtual void PostInitializeComponents() override;

	// Called after a successful login.
	virtual void PostLogin(class APlayerController* NewPlayer) override;

	void AddScore(class ASomABPlayerController* ScoredPlayer);

private:
	UPROPERTY()
	class ASomABGameState* SomABGameState;

public:
	int32 GetScore() const;
};