// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "SomABCharacterWidget.h"
#include "SomArenaBattle.h"
#include "Libraries/Components/SomABCharacterStatComponent.h"
#include "Components/ProgressBar.h"

void USomABCharacterWidget::BindCharacterStat(USomABCharacterStatComponent* NewCharacterStat)
{
	ABCHECK(NewCharacterStat != nullptr);

	CurrentCharacterStat = NewCharacterStat;

	/*NewCharacterStat->OnHPChanged.AddLambda([this]() -> void
		{
			if (CurrentCharacterStat.IsValid())
			{
				ABLOG(Warning, TEXT("HPRatio : %f"), CurrentCharacterStat->GetHPRatio());
			}
		}
	);*/

	NewCharacterStat->OnHPChanged.AddUObject(this, &USomABCharacterWidget::UpdateHPWidget);
}

void USomABCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));

	ABCHECK(HPProgressBar != nullptr);

	UpdateHPWidget();
}

void USomABCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		ABLOG(Warning, TEXT("HPRatio : %f"), CurrentCharacterStat->GetHPRatio());

		if (HPProgressBar != nullptr)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}