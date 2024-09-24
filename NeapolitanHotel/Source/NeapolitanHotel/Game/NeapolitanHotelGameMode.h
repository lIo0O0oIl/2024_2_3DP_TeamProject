// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Manager/SoundManager.h"
#include "NeapolitanHotelGameMode.generated.h"

UCLASS(minimalapi)
class ANeapolitanHotelGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANeapolitanHotelGameMode();

	UFUNCTION(BlueprintCallable, Category = "Sound")
	USoundManager* GetSoundManager() const { return SoundManager; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	USoundManager* SoundManager;
};



