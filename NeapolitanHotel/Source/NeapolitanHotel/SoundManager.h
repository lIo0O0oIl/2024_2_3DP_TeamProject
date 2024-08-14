#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SoundManager.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEAPOLITANHOTEL_API USoundManager : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    USoundManager();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Function to play sound effects based on the given name and location
    void PlaySFX(FString Name, FVector Location, bool bUseAttenuation = true);

private:
    // Map to hold the sound bases with their names
    UPROPERTY(EditAnywhere, Category = "Sound")
    TMap<FString, USoundBase*> SoundMap;

    // Attenuation settings
    UPROPERTY(EditAnywhere, Category = "Attenuation")
    float MinDistance = 100.0f;

    UPROPERTY(EditAnywhere, Category = "Attenuation")
    float MaxDistance = 1000.0f;

    UPROPERTY(EditAnywhere, Category = "Attenuation")
    float FalloffDistance = 500.0f;

    UPROPERTY(EditAnywhere, Category = "Attenuation")
    USoundAttenuation* AttenuationSettings;

    // Function to initialize the attenuation settings
    void InitializeAttenuationSettings();
};
