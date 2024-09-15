// Copyright Epic Games, Inc. All Rights Reserved.

#include "NeapolitanHotelCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"

//////////////////////////////////////////////////////////////////////////
// ANeapolitanHotelCharacter

ANeapolitanHotelCharacter::ANeapolitanHotelCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	static ConstructorHelpers::FObjectFinder<USoundBase> FootstepSoundAsset(TEXT("/Game/Sound/Walk.Walk"));
	if (FootstepSoundAsset.Succeeded())
	{
		FootstepSound = FootstepSoundAsset.Object;
	}
	FootstepAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FootstepAudioComponent"));
	FootstepAudioComponent->SetupAttachment(RootComponent);
}

void ANeapolitanHotelCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (FootstepSound)
	{
		FootstepAudioComponent->SetSound(FootstepSound);
	}

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ANeapolitanHotelCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANeapolitanHotelCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ANeapolitanHotelCharacter::MoveEnd);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANeapolitanHotelCharacter::Look);

		// Crouching
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	}
}


void ANeapolitanHotelCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	CurrentMovementVector = MovementVector * Speed;

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), CurrentMovementVector.Y);
		AddMovementInput(GetActorRightVector(), CurrentMovementVector.X);

		if (!FootstepAudioComponent->IsPlaying() && (CurrentMovementVector.X != 0 || CurrentMovementVector.Y != 0))
		{
			FootstepAudioComponent->Play();
		}
	}
}

void ANeapolitanHotelCharacter::MoveEnd(const FInputActionValue& Value)
{
	CurrentMovementVector = FVector2D(0, 0);
	
	if (FootstepAudioComponent->IsPlaying())
	{
		FootstepAudioComponent->Stop();
	}
}

void ANeapolitanHotelCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>()  * Sensitivity;

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);

		if (FootstepAudioComponent->IsPlaying())
		{
			FootstepAudioComponent->Stop();
		}
	}
}