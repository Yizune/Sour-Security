#include "OverloadComponent.h"
#include "BoobytrapComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

UOverloadComponent::UOverloadComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->SetHiddenInGame(false);
    SphereComponent->SetSphereRadius(300.0f);
    SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UOverloadComponent::OnComponentBeginOverlap);
    SphereComponent->OnComponentEndOverlap.AddDynamic(this, &UOverloadComponent::OnComponentEndOverlap);

    OverloadState = E_OverloadState::NotOverloaded;
    OverloadDuration = 10.0f;
    CurrentCountdownTime = 0.0f;
}

void UOverloadComponent::BeginPlay()
{
    Super::BeginPlay();
	
    AActor* Owner = GetOwner();
    if (Owner)
    {
        BoobytrapComponent = Owner->FindComponentByClass<UBoobytrapComponent>();
        if (BoobytrapComponent)
        {
            UE_LOG(LogTemp, Warning, TEXT("BoobytrapComponent found and assigned."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("BoobytrapComponent not found!"));
        }
    }
}

void UOverloadComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UOverloadComponent::StateOverload()
{
    if (OverloadState == E_OverloadState::NotOverloaded)
    {
        OverloadState = E_OverloadState::Overloaded;
        OnOverloadStarted.Broadcast();
        CurrentCountdownTime = OverloadDuration;
    	
        GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &UOverloadComponent::UpdateCountdown, 1.0f, true);
        UE_LOG(LogTemp, Warning, TEXT("Overload started"));
    }
}

void UOverloadComponent::UpdateCountdown()
{
    if (CurrentCountdownTime > 0)
    {
        CurrentCountdownTime--;

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Overload Time Remaining: %.0f seconds"), CurrentCountdownTime));
        }
    }
    else
    {
        EndOverload();
    }
}

void UOverloadComponent::EndOverload()
{
    GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
    OnOverloadFinished.Broadcast();
    OverloadState = E_OverloadState::NotOverloaded;
    UE_LOG(LogTemp, Warning, TEXT("Overload finished"));
	
    if (BoobytrapComponent && BoobytrapComponent->GetBoobytrapState() == E_BoobytrapState::Boobytrapped)
    {
        BoobytrapComponent->EndBoobytrap(); 
    }
}

void UOverloadComponent::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Overlap detected with %s"), *OtherActor->GetName());

    if (BoobytrapComponent && BoobytrapComponent->GetBoobytrapState() == E_BoobytrapState::Boobytrapped)
    {
        UE_LOG(LogTemp, Warning, TEXT("Enemy entered boobytrapped zone!"));
        BoobytrapComponent->TriggerBoobytrap(); 
    }

    if (OverloadState == E_OverloadState::Overloaded && OtherActor && OtherActor != GetOwner())
    {
        if (OtherActor->ActorHasTag(TEXT("Enemy")))
        {
            UE_LOG(LogTemp, Warning, TEXT("Enemy entered Overload zone! Destroying enemy!"));
            OtherActor->Destroy();
        }
    }
}

void UOverloadComponent::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // No specific behavior for ending overlap
}
