// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SomABData.generated.h"

USTRUCT(BlueprintType)
struct FSomABCharacterData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks|Variables")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks|Variables")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks|Variables")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks|Variables")
	int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks|Variables")
	int32 NextExp;
		
public:
	FSomABCharacterData() : Level(1), MaxHP(100.f), Attack(10.f), DropExp(10), NextExp(30) {}
	
};