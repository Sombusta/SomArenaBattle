// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "SomABCharacterSelectWidget.h"
#include "SomArenaBattle.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "Core/SomABCharacterSetting.h"
#include "Core/SomABGameInstance.h"
#include "EngineUtils.h"
#include "Animation/SkeletalMeshActor.h"
#include "Engine/World.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Libraries/Managers/SaveSystem/SomABSaveGame.h"
#include "Core/SomABPlayerState.h"
#include "Kismet/GameplayStatics.h"

void USomABCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CurrentIndex = 0;
	auto CharacterSetting = GetDefault<USomABCharacterSetting>();
	MaxIndex = CharacterSetting->CharacterAssets.Num();

	for (TActorIterator<ASkeletalMeshActor> it(GetWorld()); it; ++it)
	{
		TargetComponent = it->GetSkeletalMeshComponent();
		break;
	}

	PrevButton = Cast<UButton>(GetWidgetFromName(TEXT("btnPrev")));
	ABCHECK(nullptr != PrevButton);

	NextButton = Cast<UButton>(GetWidgetFromName(TEXT("btnNext")));
	ABCHECK(nullptr != NextButton);

	TextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("edtPlayerName")));
	ABCHECK(nullptr != TextBox);

	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("btnConfirm")));
	ABCHECK(nullptr != ConfirmButton);

	PrevButton->OnClicked.AddDynamic(this, &USomABCharacterSelectWidget::OnPrevClicked);
	NextButton->OnClicked.AddDynamic(this, &USomABCharacterSelectWidget::OnNextClicked);
	ConfirmButton->OnClicked.AddDynamic(this, &USomABCharacterSelectWidget::OnConfirmClicked);
}

void USomABCharacterSelectWidget::OnPrevClicked()
{
	NextCharacter(false);
}

void USomABCharacterSelectWidget::OnNextClicked()
{
	NextCharacter(true);
}

void USomABCharacterSelectWidget::OnConfirmClicked()
{
	FString CharacterName = TextBox->GetText().ToString();
	if (CharacterName.Len() <= 0 || CharacterName.Len() > 10) return;

	USomABSaveGame* NewPlayerData = NewObject<USomABSaveGame>();
	NewPlayerData->PlayerName = CharacterName;
	NewPlayerData->Level = 1;
	NewPlayerData->Exp = 0;
	NewPlayerData->HighScore = 0;
	NewPlayerData->CharacterIndex = CurrentIndex;

	auto ABPlayerState = GetDefault<ASomABPlayerState>();

	if (UGameplayStatics::SaveGameToSlot(NewPlayerData, ABPlayerState->SaveSlotName, 0))
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("GamePlay"));
	}
	else
	{
		ABLOG(Error, TEXT("SaveGame Error!"), 0);
	}
}

void USomABCharacterSelectWidget::NextCharacter(bool bForward)
{
	bForward ? CurrentIndex++ : CurrentIndex--;

	if (CurrentIndex == -1) CurrentIndex = MaxIndex - 1;
	if (CurrentIndex == MaxIndex) CurrentIndex = 0;

	auto CharacterSetting = GetDefault<USomABCharacterSetting>();
	auto AssetRef = CharacterSetting->CharacterAssets[CurrentIndex];

	USomABGameInstance* SomABGameInstance = GetWorld()->GetGameInstance<USomABGameInstance>();
	ABCHECK(SomABGameInstance != nullptr);
	ABCHECK(TargetComponent.IsValid());

	USkeletalMesh* Asset = SomABGameInstance->StreamableManager.LoadSynchronous<USkeletalMesh>(AssetRef);

	if (Asset != nullptr)
	{
		TargetComponent->SetSkeletalMesh(Asset);
	}
}