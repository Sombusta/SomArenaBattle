// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SomABAIController.generated.h"

UCLASS()
class SOMARENABATTLE_API ASomABAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASomABAIController();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;
	
private:
	void OnRepeatTimer();

	UPROPERTY()
	class UBehaviorTree* BT_Asset;

	UPROPERTY()
	class UBlackboardData* BB_Asset;

	FTimerHandle RepeatTimerHandle;

	float RepeatInterval;

protected:

public:
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

};
