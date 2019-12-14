// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SomABWeapon.generated.h"

UCLASS()
class SOMARENABATTLE_API ASomABWeapon : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponMesh;
	
public:	
	// Sets default values for this actor's properties
	ASomABWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks", meta = (AllowPrivateAccess = "true"))
	float Damage;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks", meta = (BlueprintProtected = "true"))
	float AttackRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks", meta = (BlueprintProtected = "true"))
	float AttackDamageMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks", meta = (BlueprintProtected = "true"))
	float AttackDamageMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks", meta = (BlueprintProtected = "true"))
	float AttackModifierMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks", meta = (BlueprintProtected = "true"))
	float AttackModifierMax;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly ,Transient, Category = "SomABWorks", meta = (BlueprintProtected = "true"))
	float AttackDamage;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "SomABWorks", meta = (BlueprintProtected = "true"))
	float AttackModifier;
	
public:	
	FORCEINLINE float GetWeaponDamage() const { return Damage; }
	FORCEINLINE float GetAttackRange() const { return AttackRange; }
	FORCEINLINE float GetAttackDamage() const { return AttackDamage; }
	FORCEINLINE float GetAttackModifier() const { return AttackModifier; }
};