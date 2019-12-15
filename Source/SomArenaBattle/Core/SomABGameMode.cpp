// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "SomArenaBattle.h"
#include "Player/SomAB_TPCharacter.h"
#include "Core/SomABPlayerController.h"
#include "Core/SomABPlayerState.h"
#include "Core/SomABGameState.h"
#include "Engine/World.h"

ASomABGameMode::ASomABGameMode()
{
	// set default pawn class to our Blueprinted character
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/SomBattleArena/Blueprints/Player/ThirdPersonCharacter.ThirdPersonCharacter_C'"));

	/*if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/

	DefaultPawnClass = ASomAB_TPCharacter::StaticClass();
	PlayerControllerClass = ASomABPlayerController::StaticClass();
	PlayerStateClass = ASomABPlayerState::StaticClass();
	GameStateClass = ASomABGameState::StaticClass();

	ScoreToClear = 2;
}

void ASomABGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SomABGameState = Cast<ASomABGameState>(GameState);
}

void ASomABGameMode::PostLogin(APlayerController* NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin %s"), *FString(TEXT("Begin")));
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("PostLogin %s"), *FString(TEXT("End")));

	ASomABPlayerState* SomABPlayerState = Cast<ASomABPlayerState>(NewPlayer->PlayerState);
	ABCHECK(SomABPlayerState != nullptr);

	SomABPlayerState->InitPlayerData();
}

void ASomABGameMode::AddScore(ASomABPlayerController* ScoredPlayer)
{
	for (FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it; ++it)
	{
		const ASomABPlayerController* SomABPlayerController = Cast<ASomABPlayerController>(it->Get());
		
		if ((SomABPlayerController != nullptr) && (ScoredPlayer == SomABPlayerController))
		{
			SomABPlayerController->AddGameScore();
			break;
		}
	}

	SomABGameState->AddGameScore();

	if (GetScore() >= ScoreToClear)
	{
		SomABGameState->SetGameCleared();

		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			(*It)->TurnOff();
		}

		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			const auto ABPlayerController = Cast<ASomABPlayerController>(It->Get());
			if (ABPlayerController != nullptr)
			{
				ABPlayerController->ShowResultUI();
			}
		}
	}
}

int32 ASomABGameMode::GetScore() const
{
	return SomABGameState->GetTotalGameScore();
}