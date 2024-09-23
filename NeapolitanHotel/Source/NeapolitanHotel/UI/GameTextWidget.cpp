// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameTextWidget.h"
#include "Components/TextBlock.h"
#include <Kismet/GameplayStatics.h>

UGameTextWidget::UGameTextWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UGameTextWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameText->SetText(FText::FromString(TextArray[CurrentTextIndex]));
	CurrentTextIndex++;

	CurrentTextTime = -1;

	PlayAnimation(TextFade, 1.0f, 1, EUMGSequencePlayMode::Forward, 1);
}

void UGameTextWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Is_StartTextEnd == false)
	{
		if (CurrentTextIndex < TextArray.Num())
		{
			CurrentTextTime += InDeltaTime;

			if (CurrentTextTime >= TextDelay)
			{
				if (Is_AnimStart == false)
				{
					PlayAnimation(TextFade, 0.0f, 1, EUMGSequencePlayMode::Forward, 1);
					Is_AnimStart = true;
				}

				if (CurrentTextTime >= TextDelay + 1)
				{
					GameText->SetText(FText::FromString(TextArray[CurrentTextIndex]));

					Is_AnimStart = false;
					CurrentTextIndex++;
					CurrentTextTime = 0;
				}
			}
		}
		else
		{
			Is_StartTextEnd = true;

			PlayAnimation(TextFade, 1.0f, 1, EUMGSequencePlayMode::Reverse, 1);
			PlayAnimation(Fade, 0.0f, 1, EUMGSequencePlayMode::Forward, 1);
		}
	}

	if (Is_GameOver || Is_GameClear)
	{
		CurrentTextTime += InDeltaTime;
		if (CurrentTextTime >= TextDelay && Is_AnimStart == false)
		{
			PlayAnimation(TextFade, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1);
			Is_AnimStart = true;
		}

		if (CurrentTextTime >= TextDelay + 1)
		{
			FName LevelName = TEXT("Intro"); // 레벨 이름
			UGameplayStatics::OpenLevel(GetWorld(), LevelName);
		}
	}
}

void UGameTextWidget::StartTextSkip()
{
	Is_StartTextEnd = true;

	GameText->SetVisibility(ESlateVisibility::Hidden);
	PlayAnimation(Fade, 0.0f, 1, EUMGSequencePlayMode::Forward, 1);
}

void UGameTextWidget::GameOverText()
{
	PlayAnimation(Fade, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1);
	PlayAnimation(TextFade, 1.0f, 1, EUMGSequencePlayMode::Forward, 1);

	GameText->SetText(FText::FromString(OverText));
	CurrentTextTime = 0;
	Is_GameOver = true;
}

void UGameTextWidget::GameClearText()
{
	PlayAnimation(Fade, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1);
	PlayAnimation(TextFade, 1.0f, 1, EUMGSequencePlayMode::Forward, 1);

	GameText->SetText(FText::FromString(ClearText));
	CurrentTextTime = 0;
	Is_GameClear = true;
}
