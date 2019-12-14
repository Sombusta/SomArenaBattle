// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SomABSaveGame.generated.h"

UCLASS()
class SOMARENABATTLE_API USomABSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	USomABSaveGame();

public:
	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 Exp;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	int32 HighScore;

	UPROPERTY()
	int32 CharacterIndex;
	
};
