// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABGameState.h"

ASomABGameState::ASomABGameState()
{
	TotalGameScore = 0;
}

void ASomABGameState::AddGameScore()
{
	TotalGameScore++;
}

void ASomABGameState::SetGameCleared()
{
	bGameCleared = true;
}
