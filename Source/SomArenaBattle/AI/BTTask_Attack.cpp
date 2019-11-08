// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "BTTask_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/SomABAIController.h"
#include "Player/SomAB_TPCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");

	bNotifyTick = true;

	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	ASomAB_TPCharacter* ABCharacter = Cast<ASomAB_TPCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (ABCharacter == nullptr) return EBTNodeResult::Failed;

	ABCharacter->Attack();

	bIsAttacking = true;

	ABCharacter->OnAttackEnd.AddLambda([this]() -> void
		{
			bIsAttacking = false;
		}
	);

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(!bIsAttacking) FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}