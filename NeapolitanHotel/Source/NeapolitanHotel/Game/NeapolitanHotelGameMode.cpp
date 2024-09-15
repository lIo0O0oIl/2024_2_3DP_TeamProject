// Copyright Epic Games, Inc. All Rights Reserved.

#include "NeapolitanHotelGameMode.h"
#include "Character/NeapolitanHotelCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANeapolitanHotelGameMode::ANeapolitanHotelGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// SoundManager�� �����ϰ� Outer�� GameMode�� �����մϴ�.
	SoundManager = CreateDefaultSubobject<USoundManager>(TEXT("SoundManager"));
}


void ANeapolitanHotelGameMode::BeginPlay()
{
	Super::BeginPlay();

    // SoundManager�� ���������� �ʱ�ȭ�Ǿ����� Ȯ���մϴ�.
    if (SoundManager)
    {
        // SoundManager�� ����Ǿ����� �˸��� �α� ���
        UE_LOG(LogTemp, Log, TEXT("SoundManager has been initialized and attached to GameMode."));
    }
    else
    {
        // �ʱ�ȭ ���� �� �α� ���
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize SoundManager."));
    }
}