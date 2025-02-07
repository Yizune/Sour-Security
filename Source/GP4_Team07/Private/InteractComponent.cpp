#include "InteractComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Pawn.h"

UInteractComponent::UInteractComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bCanInteract = true;  
    CollisionParams.AddIgnoredActor(GetOwner());
}

void UInteractComponent::BeginPlay()
{
    Super::BeginPlay();

    OwningPawn = Cast<APawn>(GetOwner());
    if (OwningPawn && GetWorld())
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC && PC->InputComponent)
        {
            PC->InputComponent->BindAction("Interact", IE_Pressed, this, &UInteractComponent::HandleInteract);
        }
    }

    bCanInteract = OwningPawn->IsValidLowLevel();
}

void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (OwningPawn)
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC)
        {
            bCanInteract = (PC->GetPawn() == OwningPawn);
        }
    }
}

void UInteractComponent::InteractableObjectCheck()
{
    if (!bCanInteract)
    {
        UE_LOG(LogTemp, Warning, TEXT("bCanInteract is false, returning"));
        return;
    }

    const AActor* MyActor = GetOwner();
    if (!MyActor || !GetWorld())
    {
        UE_LOG(LogTemp, Warning, TEXT("Actor or World not valid"));
        return;
    }

    FVector ViewForward = MyActor->GetActorForwardVector();
    FVector ViewStart = MyActor->GetActorLocation();
    FVector TraceEnd = ViewStart + ViewForward * 1000.0f; 

    FHitResult HitResult;
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewStart, TraceEnd, ECC_Visibility, CollisionParams);

    DrawDebugLine(GetWorld(), ViewStart, TraceEnd, FColor::Green, false, 5.0f, 0.0f, 0.5f);

    if (bHit)
    {
        AActor* HitActor = HitResult.GetActor();
        UE_LOG(LogTemp, Warning, TEXT("Line trace hit %s"), *HitActor->GetName());

        InteractableTarget = Cast<UInteractableTarget>(HitActor->GetComponentByClass(UInteractableTarget::StaticClass()));
        if (InteractableTarget)
        {
            UE_LOG(LogTemp, Warning, TEXT("Interactable target found, opening menu"));
            InteractableTarget->OpenInteractionMenu();
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Line trace did not hit any interactable target"));
    }
}

void UInteractComponent::HandleInteract()
{
    if (bCanInteract)
    {
        InteractableObjectCheck();
    }
}




/* 
#include "InteractComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Pawn.h"

UInteractComponent::UInteractComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bCanInteract = false;  // Initialize the bCanInteract flag to false
    CollisionParams.AddIgnoredActor(GetOwner());  // Ensure the line trace ignores the actor that owns this component
}

void UInteractComponent::BeginPlay()
{
    Super::BeginPlay();
    
    // Cast the owning actor to an APawn and store it
    OwningPawn = Cast<APawn>(GetOwner());
    
    // Bind the interaction input (E by default) to the HandleInteract function
    GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Interact", IE_Pressed, this, &UInteractComponent::HandleInteract);

    // Check if OwningPawn is valid
    bCanInteract = OwningPawn->IsValidLowLevel();
}

void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // Ensure that the bCanInteract flag is set only if the pawn is currently possessed
    if (OwningPawn)
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC)
        {
            bCanInteract = (PC->GetPawn() == OwningPawn);  // Only allow interaction for the owning pawn
        }
    }
}

void UInteractComponent::InteractableObjectCheck()
{
    UE_LOG(LogTemp, Warning, TEXT("begin"));
    if (!bCanInteract) return;  // If interaction is not allowed, exit early
    UE_LOG(LogTemp, Warning, TEXT("bCanInteract return"));
    
    const AActor* MyActor = GetOwner();
    if (!MyActor || !GetWorld()) return;  // Validate that the actor and world exist
    UE_LOG(LogTemp, Warning, TEXT("second return"));

    // Setup the forward vector and start point of the trace
    FVector ViewForward = MyActor->GetActorForwardVector();
    FVector ViewStart = MyActor->GetActorLocation();
    FVector TraceEnd = ViewStart + ViewForward * 1000.0f;  // Define the trace length

    FHitResult HitResult;
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewStart, TraceEnd, ECC_Visibility, CollisionParams);  // Perform the line trace

    // Draw the debug line to visualize the trace
    DrawDebugLine(GetWorld(), ViewStart, TraceEnd, FColor::Green, false, 5.0f, 0.0f, 0.5f);

    // Check if the trace hit an actor
    if (bHit)
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor)
        {
            // If the hit actor has an InteractableTarget component, interact with it
            InteractableTarget = Cast<UInteractableTarget>(HitActor->GetComponentByClass(UInteractableTarget::StaticClass()));
            if (InteractableTarget)
            {
                InteractableTarget->Interact();
            }
        }
    }
}

void UInteractComponent::HandleInteract()
{
    if (bCanInteract)
    {
        InteractableObjectCheck();  // Check for interactable objects when the interaction input is pressed
    }
}
*/
