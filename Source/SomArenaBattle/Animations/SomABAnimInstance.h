// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SomABAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

UCLASS()
class SOMARENABATTLE_API USomABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USomABAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "SomABWorks")
	void SetDeadState() { bIsDead = true; }

	UFUNCTION(BlueprintCallable, Category = "SomABWorks")
	void PlayAttackMontage();

	UFUNCTION(BlueprintCallable, Category = "SomABWorks")
	void JumpToAttackMontageSection(int32 NewSection);

	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	bool bIsDead;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AttackMontage;

public:
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnNextAttackCheckDelegate OnNextAttackCheck;

	FName GetAttackMontageSectionName(int32 Section);

	UFUNCTION(BlueprintPure, Category = "SomABWorks|AnimInstance")
	FORCEINLINE float GetCurrentPawnSpeed() const { return CurrentPawnSpeed; }
};