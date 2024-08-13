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
    void PlaySFX(FString Name, FVector Location);

private:
    // Map to hold the sound bases with their names
    UPROPERTY(EditAnywhere)
    TMap<FString, USoundBase*> SoundMap;
};
