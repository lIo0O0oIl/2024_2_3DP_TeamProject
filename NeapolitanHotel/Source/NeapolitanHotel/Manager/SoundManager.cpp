#include "SoundManager.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundAttenuation.h"
#include "Game/NeapolitanHotelGameMode.h"

// Sets default values for this component's properties
USoundManager::USoundManager()
{
    PrimaryComponentTick.bCanEverTick = false;

    // ���� ���� �Լ�
    InitializeAttenuationSettings();
}

// Called when the game starts
void USoundManager::BeginPlay()
{
    Super::BeginPlay();
}

// ���� ���� �Լ�
void USoundManager::InitializeAttenuationSettings()
{
    // ���� ���� ����
    ANeapolitanHotelGameMode* GameMode = Cast<ANeapolitanHotelGameMode>(GetOwner());
    if (GameMode)
    {
        AttenuationSettings = NewObject<USoundAttenuation>(GameMode, USoundAttenuation::StaticClass());
    }
    
    // ���� ���� ����
    if (AttenuationSettings)
    {
        // ���� �Ÿ� �˰���� ����
        AttenuationSettings->Attenuation.bAttenuate = true;
        AttenuationSettings->Attenuation.DistanceAlgorithm = EAttenuationDistanceModel::Linear;

        // ���� ��� ����
        AttenuationSettings->Attenuation.AttenuationShape = EAttenuationShape::Sphere;

        // ������ �ּ� �Ÿ� ����
        AttenuationSettings->Attenuation.AttenuationShapeExtents = FVector(MinDistance);
        // ������ �ִ� �Ÿ� ����
        AttenuationSettings->Attenuation.AttenuationShapeExtents = FVector(MaxDistance);

        // ���� ���� �Ÿ� ����
        AttenuationSettings->Attenuation.FalloffDistance = FalloffDistance;

    }
}

// ���� ���� �Լ�
void USoundManager::PlaySFX(FString Name, FVector Location, bool bUseAttenuation)
{
    // �����ϴ� �������� ã�´�
    if (USoundBase** FoundSound = SoundMap.Find(Name))
    {
        if (*FoundSound)
        {
            // ���� ��� ����
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
            // �ʿ� ���尡 ���������� null�� ��
            UE_LOG(LogTemp, Warning, TEXT("SoundBase for %s is null!"), *Name);
        }
    }
    else
    {
        // �ʿ� ���尡 �������� ���� ��
        UE_LOG(LogTemp, Warning, TEXT("Sound %s not found in SoundMap!"), *Name);
    }
}
