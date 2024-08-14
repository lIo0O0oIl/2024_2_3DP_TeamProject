#include "SoundManager.h"
#include "Sound/SoundCue.h"
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

// Function to play the sound effect based on the name
void USoundManager::PlaySFX(FString Name)
{
    // find to name
    if (USoundCue** FoundSound = SoundMap.Find(Name))
    {
        if (FoundSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, FoundSound, GetOwner()->GetActorLocation());
        }
        else
        {
            // don't find
            UE_LOG(LogTemp, Warning, TEXT("SoundCue for %s is null!"), Name);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Sound %s not found in SoundMap!"), Name);
    }
}