// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameTimer.generated.h"

/**
 * 
 */
UCLASS()
class NEAPOLITANHOTEL_API UGameTimer : public UUserWidget
{
	GENERATED_BODY()
	
//public:
//	UGameTimer();

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimeText;

	UFUNCTION(BlueprintCallable)
	void UpdateTimerText(FString NewText);
};
