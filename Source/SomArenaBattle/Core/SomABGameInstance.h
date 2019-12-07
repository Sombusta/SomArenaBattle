// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Libraries/Variables/SomABData.h"
#include "Engine/StreamableManager.h"
#include "SomABGameInstance.generated.h"

UCLASS()
class SOMARENABATTLE_API USomABGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USomABGameInstance();

	// virtual function to allow custom GameInstances an opportunity to set up what it needs
	virtual void Init() override;
	
	FSomABCharacterData* GetABCharacterData(int32 Level);

private:
	class UDataTable* ABCharacterTable;

protected:

public:
	FStreamableManager StreamableManager;
	
};
