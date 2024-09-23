// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEAPOLITANHOTEL_API UGameTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UGameTextWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void StartTextSkip();

	UFUNCTION(BlueprintCallable)
	void GameOverText();

	UFUNCTION(BlueprintCallable)
	void GameClearText();

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GameText;

	UPROPERTY(EditAnywhere, Category = "GameText")
	float TextDelay = 3.0f;

	UPROPERTY(EditAnywhere, Category = "GameText")
	TArray<FString> TextArray;

	UPROPERTY(EditAnywhere, Category = "GameText")
	FString OverText;

	UPROPERTY(EditAnywhere, Category = "GameText")
	FString ClearText;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* TextFade;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* Fade;

private:
	float CurrentTextTime = 0.0f;
	float CurrentAnimTime = 0.0f;

	int CurrentTextIndex = 0;

	bool Is_StartTextEnd = false;
	bool Is_AnimStart = false;

	bool Is_GameOver = false;
	bool Is_GameClear = false;
};
