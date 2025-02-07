#include "BoobytrapComponent.h"
#include "OverloadComponent.h"
#include "TimerManager.h"

UBoobytrapComponent::UBoobytrapComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	BoobytrapState = E_BoobytrapState::NotBoobytrapped;
}

void UBoobytrapComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		OverloadComponent = Owner->FindComponentByClass<UOverloadComponent>();
	}
}

void UBoobytrapComponent::SetBoobytrap()
{
	if (BoobytrapState == E_BoobytrapState::NotBoobytrapped && OverloadComponent)
	{
		BoobytrapState = E_BoobytrapState::Boobytrapped;
		UE_LOG(LogTemp, Warning, TEXT("Boobytrap set! Waiting for enemy to trigger..."));
		
		OnBoobytrapStarted.Broadcast();
	}
}

void UBoobytrapComponent::TriggerBoobytrap()
{
	if (BoobytrapState == E_BoobytrapState::Boobytrapped && OverloadComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Boobytrap triggered! Starting overload..."));

		OverloadComponent->StateOverload();  
		
	}
}

void UBoobytrapComponent::EndBoobytrap()
{
	BoobytrapState = E_BoobytrapState::NotBoobytrapped;
	OnBoobytrapFinished.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Boobytrap deactivated!"));
}
