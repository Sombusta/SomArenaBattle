// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABTestPawn.h"
#include "SomArenaBattle.h"
#include "Components/InputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimInstance.h"

// Sets default values
ASomABTestPawn::ASomABTestPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CardBoardMan(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP_Warrior(TEXT("AnimBlueprint'/Game/Book/Animations/AnimBP_Warrior.AnimBP_Warrior_C'"));

	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootCapsule"));
	MainMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainMesh"));
	MainCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MainCameraArm"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));

	RootComponent = RootCapsule;
	
	RootCapsule->SetCapsuleHalfHeight(88.0f);
	RootCapsule->SetCapsuleRadius(34.0f);
	
	MainMesh->SetupAttachment(RootCapsule);
	MainMesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	if (SK_CardBoardMan.Succeeded())
	{
		MainMesh->SetSkeletalMesh(SK_CardBoardMan.Object);
		MainMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);		
		if (AnimBP_Warrior.Succeeded()) {
			MainMesh->SetAnimInstanceClass(AnimBP_Warrior.Class);
		}
	}
	
	MainCameraArm->SetupAttachment(RootCapsule);
	MainCameraArm->TargetArmLength = 400.0f;
	MainCameraArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	MainCamera->SetupAttachment(MainCameraArm);

}

void ASomABTestPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);

}

// Called when the game starts or when spawned
void ASomABTestPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASomABTestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASomABTestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASomABTestPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASomABTestPawn::MoveRight);
}

void ASomABTestPawn::PossessedBy(AController* NewController)
{
	ABLOG_S(Warning);
	Super::PossessedBy(NewController);
}

void ASomABTestPawn::MoveForward(float Value)
{
	ABLOG(Warning, TEXT("%f"), Value);
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASomABTestPawn::MoveRight(float Value)
{
	ABLOG(Warning, TEXT("%f"), Value);
	AddMovementInput(GetActorRightVector(), Value);
}