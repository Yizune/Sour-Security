#include "Interactable_Distractable_Parent.h"
#include "InteractableComponent.h"
#include "OverloadComponent.h"
#include "BoobytrapComponent.h"

AInteractable_Distractable_Parent::AInteractable_Distractable_Parent()
{
    PrimaryActorTick.bCanEverTick = true;
    InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
    OverloadComponent = CreateDefaultSubobject<UOverloadComponent>(TEXT("OverloadComponent"));
    BoobytrapComponent = CreateDefaultSubobject<UBoobytrapComponent>(TEXT("BoobytrapComponent"));
    InteractableTarget = CreateDefaultSubobject<UInteractableTarget>(TEXT("InteractableTarget"));
}

void AInteractable_Distractable_Parent::BeginPlay()
{
    Super::BeginPlay();


    if (InteractableComponent)
    {
        InteractableComponent->SetActive(true); 
        InteractableComponent->OnInteractionStarted.AddDynamic(this, &AInteractable_Distractable_Parent::OnInteractionStarted_Event);
        InteractableComponent->OnInteractionFinished.AddDynamic(this, &AInteractable_Distractable_Parent::OnInteractionFinished_Event);
        UE_LOG(LogTemp, Warning, TEXT("InteractableComponent is active"));
    }

    if (OverloadComponent)
    {
        OverloadComponent->SetActive(true); 
        OverloadComponent->OnOverloadStarted.AddDynamic(this, &AInteractable_Distractable_Parent::OnOverloadStarted_Event);
        OverloadComponent->OnOverloadFinished.AddDynamic(this, &AInteractable_Distractable_Parent::OnOverloadFinished_Event);
        UE_LOG(LogTemp, Warning, TEXT("OverloadComponent is active"));
    }

    if (BoobytrapComponent)
    {
        BoobytrapComponent->SetActive(true); 
        UE_LOG(LogTemp, Warning, TEXT("BoobytrapComponent is active"));
    }
}

void AInteractable_Distractable_Parent::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AInteractable_Distractable_Parent::OnInteractionStarted_Event()
{
    UE_LOG(LogTemp, Display, TEXT("Interaction Started Event"));
}

void AInteractable_Distractable_Parent::OnInteractionFinished_Event()
{
    UE_LOG(LogTemp, Display, TEXT("Interaction Finished Event"));
}

void AInteractable_Distractable_Parent::OnOverloadStarted_Event()
{
    UE_LOG(LogTemp, Display, TEXT("Overload Started Event"));
}

void AInteractable_Distractable_Parent::OnOverloadFinished_Event()
{
    UE_LOG(LogTemp, Display, TEXT("Overload Finished Event"));
}
