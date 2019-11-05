// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABWeapon.h"
#include "SomArenaBattle.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"

// Sets default values
ASomABWeapon::ASomABWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Weapon(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight'"));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RootMesh"));

	RootComponent = WeaponMesh;

	WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));
	if(SK_Weapon.Succeeded()) {
		WeaponMesh->SetSkeletalMesh(SK_Weapon.Object);
	}
}

// Called when the game starts or when spawned
void ASomABWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASomABWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

