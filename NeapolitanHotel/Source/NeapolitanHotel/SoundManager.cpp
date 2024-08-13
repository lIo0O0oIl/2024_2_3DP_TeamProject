#include "SoundManager.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USoundManager::USoundManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USoundManager::BeginPlay()
{
    Super::BeginPlay();
}

// Function to play the sound effect based on the name and location
void USoundManager::PlaySFX(FString Name, FVector Location)
{
    // Find the sound by name
    if (USoundBase** FoundSound = SoundMap.Find(Name))
    {
        if (FoundSound)
        {
            // Play the sound at the specified location
            //UGameplayStatics::PlaySoundAtLocation(this, FoundSound, Location);
        }
        else
        {
            // Sound was found in the map, but it's null
            //UE_LOG(LogTemp, Warning, TEXT("SoundBase for %s is null!"), Name);
        }
    }
    else
    {
        // Sound not found in the map
        //UE_LOG(LogTemp, Warning, TEXT("Sound %s not found in SoundMap!"), Name);
    }
}