#include "DistractableComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"


UDistractableComponent::UDistractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetHiddenInGame(false);
	SphereComponent->SetSphereRadius(300.0f);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UDistractableComponent::OnComponentBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &UDistractableComponent::OnComponentEndOverlap);

	RootComponent = SphereComponent;
}

// Called when the game starts
void UDistractableComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UDistractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDistractableComponent::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != GetOwner())
	{
		if (OtherActor->ActorHasTag(TEXT("Enemy")))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Started overlapping with the actor that has the 'Enemy' tag!"));
		}
	}
	OnDistractionStarted.Broadcast();
}

void UDistractableComponent::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherActor != GetOwner())
	{
		if (OtherActor->ActorHasTag(TEXT("Enemy")))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Ended overlapping with the actor that has the 'Enemy' tag!"));
		}
	}
	OnDistractionFinished.Broadcast();
}
