// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABItemBox.h"
#include "Weapons/SomABWeapon.h"
#include "Player/SomAB_TPCharacter.h"
#include "SomArenaBattle.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASomABItemBox::ASomABItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Box(TEXT("StaticMesh'/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_Open(TEXT("ParticleSystem'/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));
	
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBoxTrigger"));
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OpenEffect"));

	RootComponent = BoxTrigger;

	BoxTrigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	BoxTrigger->SetCollisionProfileName(TEXT("SomABItemBox"));	

	BoxMesh->SetupAttachment(RootComponent);
	BoxMesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	BoxMesh->SetCollisionProfileName(TEXT("NoCollision"));
	if (SM_Box.Succeeded())
	{
		BoxMesh->SetStaticMesh(SM_Box.Object);
	}

	Effect->SetupAttachment(RootComponent);
	if (P_Open.Succeeded())
	{
		Effect->SetTemplate(P_Open.Object);
		Effect->bAutoActivate = false;
	}

	WeaponItemClass = ASomABWeapon::StaticClass();
}

void ASomABItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASomABItemBox::OnComponentBeginOverlap);
}

// Called when the game starts or when spawned
void ASomABItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASomABItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASomABItemBox::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABLOG_S(Warning);

	ASomAB_TPCharacter* ABCharacter = Cast<ASomAB_TPCharacter>(OtherActor);

	ABCHECK(ABCharacter != nullptr);

	if (ABCharacter != nullptr && WeaponItemClass != nullptr)
	{
		if (ABCharacter->CanSetWeapon())
		{
			ASomABWeapon* NewWeapon = GetWorld()->SpawnActor<ASomABWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			ABCharacter->SetWeapon(NewWeapon);

			Effect->Activate(true);
			Effect->OnSystemFinished.AddDynamic(this, &ASomABItemBox::OnSystemFinished);
			BoxMesh->SetHiddenInGame(true);
			SetActorEnableCollision(false);
		}
		else
		{
			ABLOG(Warning, TEXT("%s can't equip weapon currently."), *ABCharacter->GetName());
		}
	}
}

void ASomABItemBox::OnSystemFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}