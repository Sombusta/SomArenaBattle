// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABPlayerState.h"
#include "SomArenaBattle.h"
#include "Core/SomABGameInstance.h"
#include "Libraries/Managers/SaveSystem/SomABSaveGame.h"
#include "Kismet/GameplayStatics.h"

ASomABPlayerState::ASomABPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
	GameHighScore = 0;
	Exp = 0;
	SaveSlotName = TEXT("Player1");
}

void ASomABPlayerState::InitPlayerData()
{
	USomABSaveGame* SomABSaveGame = Cast<USomABSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	if (SomABSaveGame == nullptr)
	{
		SomABSaveGame = GetMutableDefault<USomABSaveGame>();
	}
	
	SetPlayerName(SomABSaveGame->PlayerName);
	SetCharacterLevel(SomABSaveGame->Level);
	GameScore = 0;
	GameHighScore = SomABSaveGame->HighScore;
	Exp = SomABSaveGame->Exp;
	CharacterIndex = SomABSaveGame->CharacterIndex;

	SavePlayerData();
}

void ASomABPlayerState::SavePlayerData()
{
	USomABSaveGame* NewPlayerData = NewObject<USomABSaveGame>();
	NewPlayerData->PlayerName = GetPlayerName();
	NewPlayerData->Level = CharacterLevel;
	NewPlayerData->Exp = Exp;
	NewPlayerData->HighScore = GameHighScore;
	NewPlayerData->CharacterIndex = CharacterIndex;

	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
	{
		ABLOG(Error, TEXT("SaveGame Error!"), 0);
	}
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
	   	 
	SavePlayerData();

	return bDidLevelUp;
}

float ASomABPlayerState::GetExpRatio() const
{
	if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER) return 0.0f;

	float Result = static_cast<float>(Exp) / static_cast<float>(CurrentStatData->NextExp);

	ABLOG(Warning, TEXT("Ratio : %f, Current : %d, Next : %d"), Result, Exp, CurrentStatData->NextExp);

	return Result;
}

void ASomABPlayerState::AddGameScore()
{
	GameScore++;

	if (GameScore >= GameHighScore) GameHighScore = GameScore;

	OnPlayerStateChanged.Broadcast();

	SavePlayerData();
}

void ASomABPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	USomABGameInstance* SomABGameInstance = Cast<USomABGameInstance>(GetGameInstance());

	ABCHECK(SomABGameInstance != nullptr);

	CurrentStatData = SomABGameInstance->GetABCharacterData(NewCharacterLevel);
	
	ABCHECK(CurrentStatData != nullptr);

	CharacterLevel = NewCharacterLevel;
}