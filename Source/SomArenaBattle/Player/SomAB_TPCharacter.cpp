// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomAB_TPCharacter.h"
#include "SomArenaBattle.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimInstance.h"
#include "Animations/SomABAnimInstance.h"
#include "DrawDebugHelpers.h"

ASomAB_TPCharacter::ASomAB_TPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CardBoardMan(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP_Warrior(TEXT("AnimBlueprint'/Game/Book/Animations/AnimBP_Warrior.AnimBP_Warrior_C'"));

	MainCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MainCameraArm"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("SomABCharacter"));

	// Set mesh location and rotation
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	if (SK_CardBoardMan.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CardBoardMan.Object);
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		if (AnimBP_Warrior.Succeeded()) {
			GetMesh()->SetAnimInstanceClass(AnimBP_Warrior.Class);
		}
	}

	// Create a camera boom (pulls in towards the player if there is a collision)
	MainCameraArm->SetupAttachment(RootComponent);
	MainCameraArm->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	MainCameraArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera	
	MainCamera->SetupAttachment(MainCameraArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	MainCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 800.f; // 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	SetControlMode(EABControlType::GTA);

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;

	bIsAttacking = false;
	MaxCombo = 4;
	AttackEndComboState();

	AttackRange = 200.f;
	AttackRadius = 50.f;
}

void ASomAB_TPCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TargetAnimBP = Cast<USomABAnimInstance>(GetMesh()->GetAnimInstance());

	ABCHECK(TargetAnimBP != nullptr);

	if (TargetAnimBP != nullptr) 
	{
		TargetAnimBP->OnMontageEnded.AddDynamic(this, &ASomAB_TPCharacter::OnAttackMontageEnded);

		TargetAnimBP->OnAttackHitCheck.AddUObject(this, &ASomAB_TPCharacter::AttackCheck);

		TargetAnimBP->OnNextAttackCheck.AddLambda([this]() -> void 
			{
				ABLOG(Warning, TEXT("OnNextAttackCheck %d"), 0);
				bCanNextCombo = false;

				if (bIsComboInputOn)
				{
					AttackStartComboState();
					TargetAnimBP->JumpToAttackMontageSection(CurrentCombo);
				}
			});		
	}
}

void ASomAB_TPCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ASomAB_TPCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void ASomAB_TPCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CurrentControlType != EABControlType::None)
	{
		MainCameraArm->TargetArmLength = FMath::FInterpTo(MainCameraArm->TargetArmLength, ArmLengthTo, DeltaSeconds, ArmLengthSpeed);

		if (CurrentControlType == EABControlType::Diablo)
		{
			MainCameraArm->RelativeRotation = FMath::RInterpTo(MainCameraArm->RelativeRotation, ArmRotationTo, DeltaSeconds, ArmRotationSpeed);

			if (DirectionToMove.SizeSquared() > 0.0f)
			{
				GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
				AddMovementInput(DirectionToMove);
			}
		}
	}
}

void ASomAB_TPCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ASomAB_TPCharacter::Attack);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASomAB_TPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASomAB_TPCharacter::MoveRight);

	PlayerInputComponent->BindKey(EKeys::Tab, IE_Pressed, this, &ASomAB_TPCharacter::ViewChange);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	if (CurrentControlType != EABControlType::Diablo)
	{
		PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
		PlayerInputComponent->BindAxis("TurnRate", this, &ASomAB_TPCharacter::TurnAtRate);
		PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
		PlayerInputComponent->BindAxis("LookUpRate", this, &ASomAB_TPCharacter::LookUpAtRate);
	}
}

float ASomAB_TPCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Result = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	ABLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), Result);

	if (Result > 0.0f)
	{
		TargetAnimBP->SetDeadState();
		SetActorEnableCollision(false);
	}

	return Result;
}

void ASomAB_TPCharacter::MoveForward(float Value)
{
	if (CurrentControlType == EABControlType::Diablo)
	{
		DirectionToMove.X = Value;
	}
	else
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void ASomAB_TPCharacter::MoveRight(float Value)
{
	if (CurrentControlType == EABControlType::Diablo)
	{
		DirectionToMove.Y = Value;
	}
	else
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
}

void ASomAB_TPCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASomAB_TPCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASomAB_TPCharacter::SetControlMode(EABControlType NewControlMode)
{
	CurrentControlType = NewControlMode;

	switch (CurrentControlType)
	{
	case EABControlType::None:
		break;
	case EABControlType::GTA:
		// MainCameraArm->TargetArmLength = 450.0f;
		// MainCameraArm->SetRelativeRotation(FRotator::ZeroRotator);
		ArmLengthTo = 450.0f;
		MainCameraArm->bUsePawnControlRotation = true;
		MainCameraArm->bInheritPitch = true;
		MainCameraArm->bInheritRoll = true;
		MainCameraArm->bInheritYaw = true;
		MainCameraArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.f, 0.0f);
		break;
	case EABControlType::Diablo:
		// MainCameraArm->TargetArmLength = 800.0f;
		// MainCameraArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		ArmLengthTo = 800.0f;
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		MainCameraArm->bUsePawnControlRotation = false;
		MainCameraArm->bInheritPitch = false;
		MainCameraArm->bInheritRoll = false;
		MainCameraArm->bInheritYaw = false;
		MainCameraArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.f, 0.0f);
		break;
	}
}

void ASomAB_TPCharacter::ViewChange()
{
	switch (CurrentControlType)
	{
	case EABControlType::None:
		SetControlMode(EABControlType::GTA);
		break;
	case EABControlType::GTA:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EABControlType::Diablo);
		break;
	case EABControlType::Diablo:
		GetController()->SetControlRotation(MainCameraArm->RelativeRotation);
		SetControlMode(EABControlType::GTA);
		break;
	}
}

void ASomAB_TPCharacter::Attack()
{
	// USomABAnimInstance* TargetAnimBP = Cast<USomABAnimInstance>(GetMesh()->GetAnimInstance());

	if (TargetAnimBP == nullptr) return;

	if (bIsAttacking)
	{
		ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));

		if (bCanNextCombo) {
			bIsComboInputOn = true;
		}
	}
	else
	{
		ABCHECK(CurrentCombo == 0);
		AttackStartComboState();
		TargetAnimBP->PlayAttackMontage();
		TargetAnimBP->JumpToAttackMontageSection(CurrentCombo);
		bIsAttacking = true;
	}		
}

void ASomAB_TPCharacter::AttackCheck()
{
	FHitResult HitResult;
	
	FCollisionQueryParams Params(NAME_None, false, this);

	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.f),
		Params);
	
#if ENABLE_DRAW_DEBUG
	
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(
		GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);

#endif

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			ABLOG(Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());
			
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(50.0f, DamageEvent, GetController(), this);
		}
	}
}

void ASomAB_TPCharacter::AttackStartComboState()
{
	bCanNextCombo = true;
	bIsComboInputOn = false;

	ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void ASomAB_TPCharacter::AttackEndComboState()
{
	bIsComboInputOn = false;	
	bCanNextCombo = false;
	CurrentCombo = 0;
}

void ASomAB_TPCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	ABCHECK(bIsAttacking);
	ABCHECK(CurrentCombo > 0);

	bIsAttacking = false;
	AttackEndComboState();
}