// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"
#include "Components/RectLightComponent.h"
#include "Telephone.generated.h"

UCLASS()
class NEAPOLITANHOTEL_API ATelephone : public AActor
{
	GENERATED_BODY()
	
public:	
	ATelephone();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void TurnOnTheAllLight();

	UFUNCTION(BlueprintCallable)
	void TurnOffTheLight();

	UFUNCTION(BlueprintImplementableEvent, Category = "Custom")
	void GameOver();

	UFUNCTION(BlueprintImplementableEvent, Category = "Custom")
	void GimmickClear();

public:
	UPROPERTY(EditAnywhere, Category = "Lights")
	TArray<AActor*> SpotLightActors;

	UPROPERTY(VisibleAnywhere, Category = "Lights")
	TArray<USpotLightComponent*> SpotLights;

	UPROPERTY(EditAnywhere, Category = "Lights")
	TArray<AActor*> TurnOffLightActors;			// Rect Light Only

	UPROPERTY(VisibleAnywhere, Category = "Lights")
	TArray<URectLightComponent*> RectLights;

private:
	int CurrentLightIndex = 0;

	bool IsStart = false;
};
