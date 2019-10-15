// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SomABTestPawn.generated.h"

UCLASS()
class SOMARENABATTLE_API ASomABTestPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* RootCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* MainMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* MainCameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* MainCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* PawnMovement;
	
public:
	// Sets default values for this pawn's properties
	ASomABTestPawn();

	// Called when initialize complete Session
	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when this Pawn is possessed.
	virtual void PossessedBy(AController* NewController) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

private:

protected:
	
public:	


};
