// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Libraries/Variables/SomABData.h"
#include "SomABCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOMARENABATTLE_API USomABCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USomABCharacterStatComponent();

	virtual void InitializeComponent() override;

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetNewLevel(int32 NewLevel);
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
		
	float GetAttack();
	float GetHPRatio();

private:
	struct FSomABCharacterData* CurrentStatData;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SomABWorks|Variables", meta = (AllowPrivateAccess = "true"))
	int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "SomABWorks|Variables", meta = (AllowPrivateAccess = "true"))
	float CurrentHP;

protected:
	
public:	
	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;
		
};