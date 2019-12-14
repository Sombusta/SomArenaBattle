// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SomABPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

UCLASS()
class SOMARENABATTLE_API ASomABPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ASomABPlayerState();

	void InitPlayerData();

	void SavePlayerData();

	bool AddExp(int32 IncomeExp);

	float GetExpRatio() const;

	void AddGameScore();

private:
	void SetCharacterLevel(int32 NewCharacterLevel);

private:
	struct FSomABCharacterData* CurrentStatData;

protected:
	UPROPERTY(Transient)
	int32 GameScore;

	UPROPERTY(Transient)
	int32 GameHighScore;

	UPROPERTY(Transient)
	int32 CharacterLevel;

	UPROPERTY(Transient)
	int32 Exp;

	UPROPERTY(Transient)
	int32 CharacterIndex;

public:
	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

	FString SaveSlotName;

	FORCEINLINE int32 GetGameScore() const { return GameScore; }
	FORCEINLINE int32 GetGameHighScore() const { return GameHighScore; }
	FORCEINLINE int32 GetCharacterLevel() const { return CharacterLevel; }
	FORCEINLINE int32 GetCharacterIndex() const { return CharacterIndex; }
};
