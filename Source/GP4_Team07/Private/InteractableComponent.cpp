#include "InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    ActivityState = E_ActivityState::Inactive;  
}

void UInteractableComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UInteractableComponent::StateInteract()
{
    UE_LOG(LogTemp, Warning, TEXT("Interact() called!"));
    
    if (ActivityState == E_ActivityState::Inactive)
    {
        ActivityState = E_ActivityState::Active;
        OnInteractionStarted.Broadcast(); 
        UE_LOG(LogTemp, Warning, TEXT("Current State: Active")); 
    }
    else
    {
        ActivityState = E_ActivityState::Inactive;
        OnInteractionFinished.Broadcast(); 
        UE_LOG(LogTemp, Warning, TEXT("Current State: Inactive")); 
    }
}

void UInteractableComponent::ToggleState()
{
    StateInteract(); 
}
