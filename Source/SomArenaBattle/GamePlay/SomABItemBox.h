// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SomABItemBox.generated.h"

UCLASS()
class SOMARENABATTLE_API ASomABItemBox : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxTrigger;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BoxMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* Effect;

public:	
	// Sets default values for this actor's properties
	ASomABItemBox();

	// Called when initialize complete Session
	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSystemFinished(class UParticleSystemComponent* PSystem);

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SomABWorks|Variables", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASomABWeapon> WeaponItemClass;

protected:

public:	

};
