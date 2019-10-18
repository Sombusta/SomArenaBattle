// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SomAB_TPCharacter.generated.h"

UENUM(BlueprintType)
enum class EABControlType : uint8
{
	None = 0,
	GTA,
	Diablo
};

UCLASS(config=Game)
class ASomAB_TPCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* MainCameraArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* MainCamera;

public:
	ASomAB_TPCharacter();

	// Called when initialize complete Session
	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called when the game ends or when quit
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	void SetControlMode(EABControlType NewControlMode);

	void ViewChange();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void Attack();

	void AttackStartComboState();
	
	void AttackEndComboState();

	UFUNCTION()
	void OnAttackMontageEnded(class UAnimMontage* Montage, bool bInterrupted);	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	class USomABAnimInstance* TargetAnimBP;

	// SomWorks :D // Movement
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;
		
	EABControlType CurrentControlType = EABControlType::None;

	FVector DirectionToMove = FVector::ZeroVector;

	// SomWorks :D // CameraArm Setting
	float ArmLengthTo = 0.0f;

	FRotator ArmRotationTo = FRotator::ZeroRotator;

	float ArmLengthSpeed = 0.0f;

	float ArmRotationSpeed = 0.0f;
	
	// SomWorks :D // Attack
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	bool bCanNextCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	bool bIsComboInputOn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	int32 CurrentCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	int32 MaxCombo;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetMainCameraArm() const { return MainCameraArm; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetMainCamera() const { return MainCamera; }
};