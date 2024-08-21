// Copyright Epic Games, Inc. All Rights Reserved.

#include "NeapolitanHotelGameMode.h"
#include "NeapolitanHotelCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANeapolitanHotelGameMode::ANeapolitanHotelGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// SoundManager를 생성하고 Outer를 GameMode로 설정합니다.
	SoundManager = CreateDefaultSubobject<USoundManager>(TEXT("SoundManager"));
}


void ANeapolitanHotelGameMode::BeginPlay()
{
	Super::BeginPlay();

    // SoundManager가 정상적으로 초기화되었는지 확인합니다.
    if (SoundManager)
    {
        // SoundManager가 연결되었음을 알리는 로그 출력
        UE_LOG(LogTemp, Log, TEXT("SoundManager has been initialized and attached to GameMode."));
    }
    else
    {
        // 초기화 실패 시 로그 출력
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize SoundManager."));
    }
}