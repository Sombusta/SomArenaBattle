// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SomABVariables.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8 
{
	PreInit = 0,
	Loading,
	Ready,
	Dead
};