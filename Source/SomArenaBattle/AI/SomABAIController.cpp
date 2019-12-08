// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABAIController.h"
#include "SomArenaBattle.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Player/SomAB_TPCharacter.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ASomABAIController::HomePosKey(TEXT("HomePos"));
const FName ASomABAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ASomABAIController::TargetKey(TEXT("Target"));

ASomABAIController::ASomABAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_Object(TEXT("BehaviorTree'/Game/Book/AI/BT_SomABCharacter.BT_SomABCharacter'"));
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB_Object(TEXT("BlackboardData'/Game/Book/AI/BB_SomABCharacter.BB_SomABCharacter'"));

	if (BT_Object.Succeeded()) {
		BT_Asset = BT_Object.Object;
	}

	if (BB_Object.Succeeded()) {
		BB_Asset = BB_Object.Object;
	}

	RepeatInterval = 3.0f;
}

void ASomABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &ASomABAIController::OnRepeatTimer, true);

	
}

void ASomABAIController::OnUnPossess()
{
	Super::OnUnPossess();

	// GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);

}

void ASomABAIController::RunAI()
{
	if (UseBlackboard(BB_Asset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());

		if (!RunBehaviorTree(BT_Asset))
		{
			ABLOG(Error, TEXT("AIController couldn't run behavior tree!! %d"), 0);
		}
	}
}

void ASomABAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	
	if (BehaviorTreeComponent != nullptr)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

void ASomABAIController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();

	ABCHECK(CurrentPawn != nullptr);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (NavSystem != nullptr) return;

	FNavLocation NextLocation;

	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, NextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
		ABLOG(Warning, TEXT("Next Location : %s"), *NextLocation.Location.ToString());
	}
}