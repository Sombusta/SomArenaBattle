// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABSection.h"
#include "SomArenaBattle.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Player/SomAB_TPCharacter.h"
#include "GamePlay/SomABItemBox.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Core/SomABPlayerController.h"
#include "Core/SomABGameMode.h"

// Sets default values
ASomABSection::ASomABSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FString AssetPath = TEXT("StaticMesh'/Game/Book/StaticMesh/SM_SQUARE.SM_SQUARE'");
	FString GateAssetPath = TEXT("StaticMesh'/Game/Book/StaticMesh/SM_GATE.SM_GATE'");

	static FName GateSockets[] = { {TEXT("+XGate")}, {TEXT("-XGate")}, {TEXT("+YGate")}, {TEXT("-YGate")} };

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SQUARE(*AssetPath);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_GATE(*GateAssetPath);
	
	if (!SM_GATE.Succeeded()) ABLOG(Error, TEXT("Failed to load staticmesh asset : %s"), *AssetPath);
	
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	SectionTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SectionTrigger"));

	RootComponent = RootMesh;

	if (SM_SQUARE.Succeeded())
	{
		RootMesh->SetStaticMesh(SM_SQUARE.Object);
	}
	else
	{
		ABLOG(Error, TEXT("Failed to load staticmesh asset : %s"), *AssetPath);
	}

	for (FName GateSocket : GateSockets)
	{
		ABCHECK(RootMesh->DoesSocketExist(GateSocket));
		UStaticMeshComponent* NewGate = CreateDefaultSubobject<UStaticMeshComponent>(*GateSocket.ToString());
		NewGate->SetupAttachment(RootComponent, GateSocket);
		NewGate->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
		NewGate->SetStaticMesh(SM_GATE.Object);

		GateMeshes.Add(NewGate);
	}

	SectionTrigger->SetupAttachment(RootComponent);
	SectionTrigger->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	SectionTrigger->SetBoxExtent(FVector(775.0f, 775.0f, 300.0f));
	SectionTrigger->SetCollisionProfileName(TEXT("SomABTrigger"));
	SectionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASomABSection::OnTriggerBeginOverlap);

	for (FName GateSocket : GateSockets)
	{
		UBoxComponent* NewGateTrigger = CreateDefaultSubobject<UBoxComponent>(*GateSocket.ToString().Append(TEXT("Trigger")));
		NewGateTrigger->SetupAttachment(RootComponent, GateSocket);
		NewGateTrigger->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		NewGateTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		NewGateTrigger->SetCollisionProfileName(TEXT("SomABTrigger"));
		NewGateTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASomABSection::OnGateTriggerBeginOverlap);
		NewGateTrigger->ComponentTags.Add(GateSocket);
	
		GateTriggers.Add(NewGateTrigger);
	}

	bNoBattle = false;
	EnemySpawnTime = 2.0f;
	ItemBoxSpawnTime = 5.0f;
}

void ASomABSection::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetState(bNoBattle ? ESectionState::Complete : ESectionState::Ready);
}

// Called when the game starts or when spawned
void ASomABSection::BeginPlay()
{
	Super::BeginPlay();
	
	SetState(bNoBattle ? ESectionState::Complete : ESectionState::Ready);
}

// Called every frame
void ASomABSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASomABSection::SetState(ESectionState NewState)
{
	switch (NewState)
	{
	case ESectionState::Ready:
		SectionTrigger->SetCollisionProfileName(TEXT("SomABTrigger"));

		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}

		OperateGates(true);

		break;

	case ESectionState::Battle:
		SectionTrigger->SetCollisionProfileName(TEXT("NoCollision"));

		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}

		OperateGates(false);
		
		GetWorld()->GetTimerManager().SetTimer(SpawnNPCTimerHandle, FTimerDelegate::CreateUObject(this, &ASomABSection::OnNPCSpawn), EnemySpawnTime, false);

		GetWorld()->GetTimerManager().SetTimer(SpawnItemBoxTimerHandle, FTimerDelegate::CreateLambda([this]() -> void 
			{
			FVector2D RandXY = FMath::RandPointInCircle(600.0f);
			GetWorld()->SpawnActor<ASomABItemBox>(GetActorLocation() + FVector(RandXY, 30.0f), FRotator::ZeroRotator);
			}
		), ItemBoxSpawnTime, false);

		break;

	case ESectionState::Complete:
		SectionTrigger->SetCollisionProfileName(TEXT("NoCollision"));

		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("SomABTrigger"));
		}

		OperateGates(true);

		break;

	default:
		break;
	}

	CurrentState = NewState;
}

void ASomABSection::OperateGates(bool bOpen)
{
	for (UStaticMeshComponent* Gate : GateMeshes)
	{
		Gate->SetRelativeRotation(bOpen ? FRotator(0.0f, -90.0f, 0.0f) : FRotator::ZeroRotator);
	}
}

void ASomABSection::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CurrentState == ESectionState::Ready)
	{
		SetState(ESectionState::Battle);
	}
}

void ASomABSection::OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABCHECK(OverlappedComponent->ComponentTags.Num() == 1);

	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	FName SocketName = FName(*ComponentTag.ToString().Left(2));

	if (!RootMesh->DoesSocketExist(SocketName))	return;

	FVector NewLocation = RootMesh->GetSocketLocation(SocketName);

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FCollisionObjectQueryParams ObjectQueryParam(FCollisionObjectQueryParams::InitType::AllObjects);

	bool bResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		NewLocation,
		FQuat::Identity,
		ObjectQueryParam,
		FCollisionShape::MakeSphere(775.0f),
		CollisionQueryParam
	);

	if (!bResult)
	{
		auto NewSection = GetWorld()->SpawnActor<ASomABSection>(NewLocation, FRotator::ZeroRotator);
	}
	else
	{
		ABLOG(Warning, TEXT("New section area is not empty."), "");
	}
}

void ASomABSection::OnNPCSpawn()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnNPCTimerHandle);

	ASomAB_TPCharacter* KeyNPC = GetWorld()->SpawnActor<ASomAB_TPCharacter>(GetActorLocation() + FVector::UpVector * 88.f, FRotator::ZeroRotator);

	if (KeyNPC != nullptr)
	{
		KeyNPC->OnDestroyed.AddDynamic(this, &ASomABSection::OnKeyNPCDestroyed);
	}
}

void ASomABSection::OnKeyNPCDestroyed(AActor* DestroyedActor)
{
	ASomAB_TPCharacter* SomABCharacter = Cast<ASomAB_TPCharacter>(DestroyedActor);
	ABCHECK(SomABCharacter != nullptr);

	ASomABPlayerController* SomABPlayerController = Cast<ASomABPlayerController>(SomABCharacter->LastHitBy);
	ABCHECK(SomABPlayerController != nullptr);

	ASomABGameMode* SomABGameMode = Cast<ASomABGameMode>(GetWorld()->GetAuthGameMode());
	ABCHECK(SomABGameMode != nullptr);

	SomABGameMode->AddScore(SomABPlayerController);

	SetState(ESectionState::Complete);
}
