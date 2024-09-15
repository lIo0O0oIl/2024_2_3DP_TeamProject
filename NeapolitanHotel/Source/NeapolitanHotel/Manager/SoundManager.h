#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SoundManager.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEAPOLITANHOTEL_API USoundManager : public UActorComponent
{
    GENERATED_BODY()

public:
    USoundManager();

protected:
    virtual void BeginPlay() override;

public:
    void PlaySFX(FString Name, FVector Location, bool bUseAttenuation = true);

private:
    // 사운드 이름 / 사운드 로 저장할 수 있는 map
    UPROPERTY(EditAnywhere, Category = "Sound")
    TMap<FString, USoundBase*> SoundMap;

    // 사운드 감쇠 설정값
    // 최소 거리
    UPROPERTY(EditAnywhere, Category = "Attenuation")
    float MinDistance = 100.0f;

    // 최대 거리
    UPROPERTY(EditAnywhere, Category = "Attenuation")
    float MaxDistance = 1000.0f;

    // 최대 거리
    UPROPERTY(EditAnywhere, Category = "Attenuation")
    float FalloffDistance = 500.0f;

    // 사운드 감쇠
    UPROPERTY(EditAnywhere, Category = "Attenuation")
    USoundAttenuation* AttenuationSettings;

    // 사운드 감쇠 설정 함수
    void InitializeAttenuationSettings();
};
