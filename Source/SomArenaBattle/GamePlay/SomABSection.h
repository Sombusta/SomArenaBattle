// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SomABSection.generated.h"

UENUM(BlueprintType)
enum class ESectionState : uint8
{
	Ready = 0,
	Battle,
	Complete
};

UCLASS()
class SOMARENABATTLE_API ASomABSection : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* RootMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	TArray<class UStaticMeshComponent*> GateMeshes;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SectionTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SomABWorks|Components", meta = (AllowPrivateAccess = "true"))
	TArray<class UBoxComponent*> GateTriggers;

public:	
	ASomABSection();

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	void SetState(ESectionState NewState);

	void OperateGates(bool bOpen = true);
	   
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void OnNPCSpawn();

protected:

private:
	ESectionState CurrentState = ESectionState::Ready;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks|Variables", meta = (AllowPrivateAccess = "true"))
	bool bNoBattle;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks|Variables", meta = (AllowPrivateAccess = "true"))
	float EnemySpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks|Variables", meta = (AllowPrivateAccess = "true"))
	float ItemBoxSpawnTime;

	FTimerHandle SpawnNPCTimerHandle = {};
	FTimerHandle SpawnItemBoxTimerHandle = {};

public:	
	
};