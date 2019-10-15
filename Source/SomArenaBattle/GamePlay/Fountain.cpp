// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "Fountain.h"
#include "SomArenaBattle.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AFountain::AFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_MainMesh(TEXT("StaticMesh'/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Ruins/StaticMesh/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Water(TEXT("StaticMesh'/Game/InfinityBladeGrassLands/Effects/FX_Meshes/Env/SM_Plains_Fountain_02.SM_Plains_Fountain_02'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_Splash(TEXT("ParticleSystem'/Game/InfinityBladeGrassLands/Effects/FX_Ambient/Water/P_Water_Fountain_Splash_Base_01.P_Water_Fountain_Splash_Base_01'"));

	RootArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("RootArrow"));
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	WaterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WaterMesh"));
	MainLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("MainLight"));
	SplashParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SplashParticle"));
	RotationMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationMovement"));

	RootComponent = RootArrow;

	MainMesh->SetupAttachment(RootComponent);	
	if (SM_MainMesh.Succeeded()) {
		MainMesh->SetStaticMesh(SM_MainMesh.Object);
	}	

	WaterMesh->SetupAttachment(MainMesh);
	WaterMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 135.f));
	if (SM_Water.Succeeded()) {
		WaterMesh->SetStaticMesh(SM_Water.Object);
	}

	MainLight->SetupAttachment(MainMesh);
	MainLight->SetRelativeLocation(FVector(0.0f, 0.0f, 195.f));

	SplashParticle->SetupAttachment(MainMesh);
	SplashParticle->SetRelativeLocation(FVector(0.0f, 0.0f, 195.f));
	if (P_Splash.Succeeded()) {
		SplashParticle->SetTemplate(P_Splash.Object);
	}

	ObjectID = 0;
	RotationSpeed = 30.0f;

	RotationMovement->RotationRate = FRotator(0.0f, RotationSpeed, 0.0f);
}

void AFountain::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ABLOG_S(Warning);
}

// Called when the game starts or when spawned
void AFountain::BeginPlay()
{
	Super::BeginPlay();
	
	// UE_LOG(SomArenaBattle, Warning, TEXT("Actor Name : %s, ID : %d, Location X : %.3f"), *GetName(), ObjectID, GetActorLocation().X);

	ABLOG_S(Warning);

	ABLOG(Warning, TEXT("Actor Name : %s, ID : %d, Location X : %.3f"), *GetName(), ObjectID, GetActorLocation().X);
}

void AFountain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ABLOG_S(Warning);
}

// Called every frame
void AFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));	
}

