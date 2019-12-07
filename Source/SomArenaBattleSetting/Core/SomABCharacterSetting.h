// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SomABCharacterSetting.generated.h"

UCLASS(config=SomArenaBattle)
class SOMARENABATTLESETTING_API USomABCharacterSetting : public UObject
{
	GENERATED_BODY()
	
public:
	USomABCharacterSetting();

	UPROPERTY(config)
	TArray<FSoftObjectPath> CharacterAssets;
	
};
