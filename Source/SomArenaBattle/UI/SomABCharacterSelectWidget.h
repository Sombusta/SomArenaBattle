// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SomABCharacterSelectWidget.generated.h"

UCLASS()
class SOMARENABATTLE_API USomABCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY()
	class UButton* PrevButton;

	UPROPERTY()
	class UButton* NextButton;

	UPROPERTY()
	class UEditableTextBox* TextBox;

	UPROPERTY()
	class UButton* ConfirmButton;
		
public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnPrevClicked();

	UFUNCTION()
	void OnNextClicked();

	UFUNCTION()
	void OnConfirmClicked();

protected:
	UFUNCTION(BlueprintCallable)
	void NextCharacter(bool bForward = true);

private:
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks", meta = (BlueprintProtected = "true"))
	int32 CurrentIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SomABWorks", meta = (BlueprintProtected = "true"))
	int32 MaxIndex;

	TWeakObjectPtr<class USkeletalMeshComponent> TargetComponent;

public:
};
