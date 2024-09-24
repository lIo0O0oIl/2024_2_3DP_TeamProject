// Fill out your copyright notice in the Description page of Project Settings.


#include "Telephone.h"

ATelephone::ATelephone()
{
}

void ATelephone::BeginPlay()
{
	Super::BeginPlay();

	SpotLights.Empty();
	RectLights.Empty();

	for (AActor* Actor : SpotLightActors)
	{
		if (Actor)
		{
			USpotLightComponent* SpotLightComponent = Actor->FindComponentByClass<USpotLightComponent>();
			if (SpotLightComponent)
			{
				SpotLights.Add(SpotLightComponent);
			}
		}
	}

	for (AActor* Actor : TurnOffLightActors)
	{
		if (Actor)
		{
			URectLightComponent* RectLightComponent = Actor->FindComponentByClass<URectLightComponent>();
			if (RectLightComponent)
			{
				RectLights.Add(RectLightComponent);
			}
		}
	}
}

void ATelephone::TurnOnTheAllLight()
{
	for (USpotLightComponent* SpotLight : SpotLights)
	{
		if (SpotLight)
		{
			SpotLight->SetIntensity(2.0f);
		}
	}

	for (URectLightComponent* RectLight : RectLights)
	{
		if (RectLight)
		{
			RectLight->SetIntensity(0.1f);
		}
	}

	CurrentLightIndex = 0;
	IsStart = false;
}

void ATelephone::TurnOffTheLight()
{
	if (IsStart == false)
	{
		for (URectLightComponent* RectLight : RectLights)
		{
			if (RectLight)
			{
				RectLight->SetIntensity(0.0f);
			}
		}
		IsStart = true;
	}

	if (CurrentLightIndex == SpotLights.Num())
	{
		GimmickClear();
		TurnOnTheAllLight();
		return;
	}
	SpotLights[CurrentLightIndex]->SetIntensity(0.0f);
	CurrentLightIndex++;
}

