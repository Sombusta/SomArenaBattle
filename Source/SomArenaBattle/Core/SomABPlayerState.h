// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SomABPlayerState.generated.h"

UCLASS()
class SOMARENABATTLE_API ASomABPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ASomABPlayerState();

	void InitPlayerData();

protected:
	UPROPERTY(Transient, Category = "SomABWorks|Variables", meta = (BlueprintProtected = "true"))
	int32 GameScore;

	UPROPERTY(Transient, Category = "SomABWorks|Variables", meta = (BlueprintProtected = "true"))
	int32 CharacterLevel;

public:
	FORCEINLINE int32 GetGameScore() const { return GameScore; }
	FORCEINLINE int32 GetCharacterLevel() const { return CharacterLevel; }
};
