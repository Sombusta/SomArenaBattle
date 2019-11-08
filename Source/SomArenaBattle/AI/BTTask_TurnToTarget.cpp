// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "BTTask_TurnToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/SomABAIController.h"
#include "Player/SomAB_TPCharacter.h"
#include "Engine/World.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("TurnToTarget");

}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ASomAB_TPCharacter* ABCharacter = Cast<ASomAB_TPCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (ABCharacter == nullptr) return EBTNodeResult::Failed;

	ASomAB_TPCharacter* Target = Cast<ASomAB_TPCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASomABAIController::TargetKey));

	if (Target == nullptr) return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - ABCharacter->GetActorLocation();

	LookVector.Z = 0.f;

	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	ABCharacter->SetActorRotation(FMath::RInterpTo(ABCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));
	
	return EBTNodeResult::Succeeded;
}
