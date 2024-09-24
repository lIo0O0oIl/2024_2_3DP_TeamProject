// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameTimeWidget.h"
#include "Components/TextBlock.h"

UGameTimeWidget::UGameTimeWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UGameTimeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (TimeText)
	{
		FString StartTimeText = FString::Printf(TEXT("%02d:%02d"), Hours, Minutes);
		TimeText->SetText(FText::FromString(StartTimeText));
	}
}

void UGameTimeWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	Second += InDeltaTime;
	if (Second >= 1.5f)			// 분이 지나는 시간. 우리 게임 총 플레이 타임은 9분. 6으로 설정하면 36분됨.
	{
		UpdateTimeText();
		Second = 0;
	}
}

void UGameTimeWidget::UpdateTimeText()
{
	if (TimeText)
	{
		Minutes++;

		if (Minutes >= 60)
		{
			Hours++;
			Minutes = 0;
			if (Hours >= 13)
			{
				Hours = 1;
			}
			if (Hours == 5)			// 5시가 되면 게임 클리어
			{
				GameClear();
			}
		}

		// 초를 텍스트로 변환하여 TimeText에 설정
		FString NewTimeText = FString::Printf(TEXT("%02d:%02d"), Hours, Minutes);
		TimeText->SetText(FText::FromString(NewTimeText));
	}
}
