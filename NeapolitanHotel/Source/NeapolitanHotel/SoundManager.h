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
    // ���� �̸� / ���� �� ������ �� �ִ� map
    UPROPERTY(EditAnywhere, Category = "Sound")
    TMap<FString, USoundBase*> SoundMap;

    // ���� ���� ������
    // �ּ� �Ÿ�
    UPROPERTY(EditAnywhere, Category = "Attenuation")
    float MinDistance = 100.0f;

    // �ִ� �Ÿ�
    UPROPERTY(EditAnywhere, Category = "Attenuation")
    float MaxDistance = 1000.0f;

    // �ִ� �Ÿ�
    UPROPERTY(EditAnywhere, Category = "Attenuation")
    float FalloffDistance = 500.0f;

    // ���� ����
    UPROPERTY(EditAnywhere, Category = "Attenuation")
    USoundAttenuation* AttenuationSettings;

    // ���� ���� ���� �Լ�
    void InitializeAttenuationSettings();
};
