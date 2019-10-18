// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABAnimInstance.h"
#include "SomArenaBattle.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

USomABAnimInstance::USomABAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	bIsInAir = false;
}

void USomABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* TargetPawn = TryGetPawnOwner();

	if (::IsValid(TargetPawn))
	{
		CurrentPawnSpeed = TargetPawn->GetVelocity().Size();

		ACharacter* TargetCharacter = Cast<ACharacter>(TargetPawn);

		if (TargetCharacter != nullptr)
		{
			bIsInAir = TargetCharacter->GetCharacterMovement()->IsFalling();
		}
	}
}

void USomABAnimInstance::PlayAttackMontage()
{
	if (AttackMontage == nullptr) return;

	Montage_Play(AttackMontage, 1.0f);
}

void USomABAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	ABCHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void USomABAnimInstance::AnimNotify_AttackHitCheck()
{
	if (OnAttackHitCheck.IsBound()) {
		OnAttackHitCheck.Broadcast();
	}
}

void USomABAnimInstance::AnimNotify_NextAttackCheck()
{
	if (OnNextAttackCheck.IsBound()) {
		OnNextAttackCheck.Broadcast();
	}
}

FName USomABAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	ABCHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}