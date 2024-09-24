// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorClose.generated.h"

UCLASS()
class NEAPOLITANHOTEL_API ADoorClose : public AActor
{
	GENERATED_BODY()
	
public:
	ADoorClose();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* TriggerBox;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComponent;

    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintImplementableEvent, Category = "Custom")
    void GameOver();

    UFUNCTION(BlueprintCallable)
    void DoorOpen();

    UFUNCTION(BlueprintCallable)
    void DoorClose();

private:
    bool IsGimmickStart = false;

    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    float GameOverTime = 15.0f;

    float CurrentTime;
};
