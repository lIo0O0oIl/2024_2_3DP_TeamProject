


#include "DoorClose.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoorClose::ADoorClose()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f)); // 박스 크기 설정
	TriggerBox->SetCollisionProfileName(TEXT("Trigger")); // 충돌 설정

	// OnComponentBeginOverlap 델리게이트에 함수 바인딩
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADoorClose::OnOverlapBegin);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
}

void ADoorClose::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorClose::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsGimmickStart)
	{
		CurrentTime += DeltaTime;
		if (CurrentTime >= GameOverTime)
		{
			GameOver();
		}
	}
}

void ADoorClose::DoorOpen()
{
	IsGimmickStart = true;
}

void ADoorClose::DoorClose()
{
	IsGimmickStart = false;
	CurrentTime = 0;
}

void ADoorClose::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		GameOver();
	}
}


