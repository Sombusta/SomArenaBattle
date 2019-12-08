// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABPlayerState.h"

ASomABPlayerState::ASomABPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
}

void ASomABPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("Destiny"));
	CharacterLevel = 5;
	GameScore = 0;
}