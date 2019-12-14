// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SomABUIPlayerController.generated.h"

UCLASS()
class SOMARENABATTLE_API ASomABUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASomABUIPlayerController();

	virtual void BeginPlay() override;

private:
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SomABWorks", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> UIWidgetClass;

	UPROPERTY()
	class UUserWidget* UIWidgetInstance;	
};
