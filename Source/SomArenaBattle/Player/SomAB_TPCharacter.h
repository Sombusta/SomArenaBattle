// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Libraries/Variables/SomABVariables.h"
#include "SomAB_TPCharacter.generated.h"

UENUM(BlueprintType)
enum class EABControlType : uint8
{
	None = 0,
	GTA,
	Diablo,
	NPC
};

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS(config=Game)
class ASomAB_TPCharacter : public ACharacter
{
	GENERATED_BODY()

	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* MainCameraArm;

	// Follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* MainCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USomABCharacterStatComponent* CharacterStat;

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

	virtual void PossessedBy(AController* NewController) override;

	// Apply damage to this actor.
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Called for forwards/backward input
	void MoveForward(float Value);

	// Called for side to side input
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

	void SetControlMode(EABControlType NewControlMode);
	void ViewChange();

	void Attack();
	void AttackCheck();
	void AttackStartComboState();	
	void AttackEndComboState();

	UFUNCTION()
	void OnAttackMontageEnded(class UAnimMontage* Montage, bool bInterrupted);

	void SetWeapon(class ASomABWeapon* NewWeapon);

	void SetCharacterState(ECharacterState NewState);
	
private:
	void OnAssetsLoadCompleted();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	class USomABAnimInstance* TargetAnimBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	class ASomABWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* HPBarWidget;
		
	// SomWorks :D // Movement
	// Base turn rate, in deg/sec. Other scaling may affect final turn rate.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	// Base look up/down rate, in deg/sec. Other scaling may affect final rate.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;
		
	EABControlType CurrentControlType = EABControlType::None;
	FVector DirectionToMove = FVector::ZeroVector;

	bool bIsDead;

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

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	float AttackRadius;

	int32 AssetIndex = 0;
	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;
		
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "SomABWorks|Variables", meta = (AllowPrivateAccess = "true"))
	ECharacterState CurrentState;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "SomABWorks|Variables", meta = (AllowPrivateAccess = "true"))
	bool bIsPlayer;

	UPROPERTY()
	class ASomABAIController* SomAIController;

	UPROPERTY()
	class ASomABPlayerController* SomABPlayerController;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks|Variables", meta = (AllowPrivateAccess = "true"))
	float DeadTimer;

	FTimerHandle DeadTimerHandle;

public:
	FOnAttackEndDelegate OnAttackEnd;

	int32 GetExp() const;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetMainCameraArm() const { return MainCameraArm; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetMainCamera() const { return MainCamera; }

	FORCEINLINE bool CanSetWeapon() const { return CurrentWeapon == nullptr; }

	FORCEINLINE bool IsDead() const { return bIsDead; }

	FORCEINLINE ECharacterState GetCharacterState() const { return CurrentState; }
};