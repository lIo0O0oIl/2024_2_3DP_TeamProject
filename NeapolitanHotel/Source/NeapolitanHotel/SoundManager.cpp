#include "SoundManager.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundAttenuation.h"
#include "NeapolitanHotel/NeapolitanHotelGameMode.h"

// Sets default values for this component's properties
USoundManager::USoundManager()
{
    PrimaryComponentTick.bCanEverTick = false;

    // 감쇠 설정 함수
    InitializeAttenuationSettings();
}

// Called when the game starts
void USoundManager::BeginPlay()
{
    Super::BeginPlay();
}

// 사운드 감쇠 함수
void USoundManager::InitializeAttenuationSettings()
{
    // 사운드 감쇠 생성
    ANeapolitanHotelGameMode* GameMode = Cast<ANeapolitanHotelGameMode>(GetOwner());
    if (GameMode)
    {
        AttenuationSettings = NewObject<USoundAttenuation>(GameMode, USoundAttenuation::StaticClass());
    }
    
    // 사운드 감쇠 설정
    if (AttenuationSettings)
    {
        // 감쇠 거리 알고리즘 설정
        AttenuationSettings->Attenuation.bAttenuate = true;
        AttenuationSettings->Attenuation.DistanceAlgorithm = EAttenuationDistanceModel::Linear;

        // 감쇠 모양 설정
        AttenuationSettings->Attenuation.AttenuationShape = EAttenuationShape::Sphere;

        // 반지름 최소 거리 설정
        AttenuationSettings->Attenuation.AttenuationShapeExtents = FVector(MinDistance);
        // 반지름 최대 거리 설정
        AttenuationSettings->Attenuation.AttenuationShapeExtents = FVector(MaxDistance);

        // 완전 감쇠 거리 설정
        AttenuationSettings->Attenuation.FalloffDistance = FalloffDistance;

    }
}

// 사운드 실행 함수
void USoundManager::PlaySFX(FString Name, FVector Location, bool bUseAttenuation)
{
    // 존재하는 사운드인지 찾는다
    if (USoundBase** FoundSound = SoundMap.Find(Name))
    {
        if (*FoundSound)
        {
            // 감쇠 사용 여부
            if (bUseAttenuation && AttenuationSettings)
            {
                UGameplayStatics::PlaySoundAtLocation(this, *FoundSound, Location, 1.0f, 1.0f, 0.0f, AttenuationSettings);
            }
            else
            {
                UGameplayStatics::PlaySoundAtLocation(this, *FoundSound, Location);
            }
        }
        else
        {
            // 맵에 사운드가 존재하지만 null일 때
            UE_LOG(LogTemp, Warning, TEXT("SoundBase for %s is null!"), *Name);
        }
    }
    else
    {
        // 맵에 사운드가 존재하지 않을 때
        UE_LOG(LogTemp, Warning, TEXT("Sound %s not found in SoundMap!"), *Name);
    }
}
