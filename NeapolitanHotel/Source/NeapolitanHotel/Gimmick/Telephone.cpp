// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/Telephone.h"
#include "Telephone.h"

ATelephone::ATelephone()
{
}

void ATelephone::BeginPlay()
{
	Super::BeginPlay();

	SpotLights.Empty();

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
	CurrentLightIndex = 0;
}

void ATelephone::TurnOffTheLight()
{
	if (IsEnd == false)
	{
		SpotLights[CurrentLightIndex]->SetIntensity(0.0f);
		CurrentLightIndex++;
		if (CurrentLightIndex == SpotLights.Num())
		{
			IsEnd = true;
			GameOver();
		}
	}
}

