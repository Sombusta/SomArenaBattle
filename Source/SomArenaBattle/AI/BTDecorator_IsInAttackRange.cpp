// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "BTDecorator_IsInAttackRange.h"
#include "AI/SomABAIController.h"
#include "Player/SomAB_TPCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (ControllingPawn == nullptr) return false;

	auto Target = Cast<ASomAB_TPCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASomABAIController::TargetKey));
	
	if (Target == nullptr) return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.f);
	
	return bResult;
}
