// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameTimeWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEAPOLITANHOTEL_API UGameTimeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UGameTimeWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateTimeText();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimeText;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Custom")
	void GameClear();

private:
	float Second = 0.0f;

protected:
	UPROPERTY(EditAnywhere)
	int Minutes = 0;

	UPROPERTY(EditAnywhere)
	int Hours = 11;
};
