// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABGameMode.h"
#include "SomArenaBattle.h"
#include "Player/SomAB_TPCharacter.h"
#include "Core/SomABPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ASomABGameMode::ASomABGameMode()
{
	//DefaultPawnClass = ASomAB_TPCharacter::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/SomBattleArena/Blueprints/Player/BP_SomABCharacter.BP_SomABCharacter_C'"));

	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = ASomABPlayerController::StaticClass();
}

void ASomABGameMode::PostLogin(APlayerController* NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin %s"), *FString(TEXT("Begin")));
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("PostLogin %s"), *FString(TEXT("End")));
}
