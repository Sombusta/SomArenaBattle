// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABPlayerState.h"
#include "SomArenaBattle.h"
#include "Core/SomABGameInstance.h"

ASomABPlayerState::ASomABPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
	Exp = 0;
}

void ASomABPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("Destiny"));
	SetCharacterLevel(5);
	GameScore = 0;
	Exp = 0;
}

bool ASomABPlayerState::AddExp(int32 IncomeExp)
{
	if (CurrentStatData->NextExp == -1) return false;

	bool bDidLevelUp = false;
	
	Exp = Exp + IncomeExp;

	if (Exp >= CurrentStatData->NextExp)
	{
		Exp -= CurrentStatData->NextExp;
		SetCharacterLevel(CharacterLevel + 1);
		bDidLevelUp = true;
	}

	OnPlayerStateChanged.Broadcast();
	   	 
	return bDidLevelUp;
}

float ASomABPlayerState::GetExpRatio() const
{
	if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER) return 0.0f;

	float Result = static_cast<float>(Exp) / static_cast<float>(CurrentStatData->NextExp);

	ABLOG(Warning, TEXT("Ratio : %f, Current : %d, Next : %d"), Result, Exp, CurrentStatData->NextExp);

	return Result;
}

void ASomABPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	USomABGameInstance* SomABGameInstance = Cast<USomABGameInstance>(GetGameInstance());

	ABCHECK(SomABGameInstance != nullptr);

	CurrentStatData = SomABGameInstance->GetABCharacterData(NewCharacterLevel);
	
	ABCHECK(CurrentStatData != nullptr);

	CharacterLevel = NewCharacterLevel;
}