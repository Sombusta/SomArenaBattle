// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fountain.generated.h"

UCLASS()
class SOMARENABATTLE_API AFountain : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* RootArrow;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MainMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WaterMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent* MainLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* SplashParticle;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class URotatingMovementComponent* RotationMovement;

public:	
	// Sets default values for this actor's properties
	AFountain();

	// Called when initialize complete Session
	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game ends or when quit
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks|Variables", meta = (AllowPrivateAccess = "true"))
	int32 ObjectID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks|Variables", meta = (AllowPrivateAccess = "true"))
	float RotationSpeed;

protected:

public:	

	FORCEINLINE class UArrowComponent* GetRootArrow() const { return RootArrow; }
	FORCEINLINE class UStaticMeshComponent* GetMainMesh() const { return MainMesh; }
	FORCEINLINE class UStaticMeshComponent* GetWaterMesh() const { return WaterMesh; }
};
