// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABGameInstance.h"
#include "SomArenaBattle.h"
#include "UObject/ConstructorHelpers.h"
// #include "Engine/DataTable.h"

USomABGameInstance::USomABGameInstance()
{
	FString CharacterDataPath = TEXT("DataTable'/Game/Book/GameData/ABCharacterData.ABCharacterData'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABCharacter(*CharacterDataPath);

	ABCHECK(DT_ABCharacter.Succeeded());

	if (DT_ABCharacter.Succeeded())
	{
		ABCharacterTable = DT_ABCharacter.Object;
		ABCHECK(ABCharacterTable->GetRowMap().Num() > 0);
	}
}

void USomABGameInstance::Init()
{
	Super::Init();
	
	ABLOG(Warning, TEXT("DropExp of Level 20 ABCharacter : %d"), GetABCharacterData(20)->DropExp);
}

FSomABCharacterData* USomABGameInstance::GetABCharacterData(int32 Level)
{
	return ABCharacterTable->FindRow<FSomABCharacterData>(*FString::FromInt(Level), TEXT(""));
}
