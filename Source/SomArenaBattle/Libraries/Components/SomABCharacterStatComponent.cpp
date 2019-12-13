// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABCharacterStatComponent.h"
#include "SomArenaBattle.h"
#include "Core/SomABGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USomABCharacterStatComponent::USomABCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	bWantsInitializeComponent = true;

	Level = 1;

	// ...
}

void USomABCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetNewLevel(Level);
}

// Called when the game starts
void USomABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void USomABCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USomABCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	USomABGameInstance* ABGameInstance = Cast<USomABGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ABCHECK(ABGameInstance != nullptr);

	CurrentStatData = ABGameInstance->GetABCharacterData(NewLevel);

	if (CurrentStatData != nullptr)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);		
	}
	else
	{
		ABLOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void USomABCharacterStatComponent::SetDamage(float NewDamage)
{
	ABCHECK(CurrentStatData != nullptr);

	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

void USomABCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();

	if (CurrentHP < KINDA_SMALL_NUMBER) // if (CurrentHP <= 0)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

float USomABCharacterStatComponent::GetAttack() const
{
	ABCHECK(CurrentStatData != nullptr, 0.0f);
		
	return CurrentStatData->Attack;
}

float USomABCharacterStatComponent::GetHPRatio() const
{
	ABCHECK(CurrentStatData != nullptr, 0.0f);

	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}

int32 USomABCharacterStatComponent::GetDropExp() const
{
	return CurrentStatData->DropExp;
}
