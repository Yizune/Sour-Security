#include "InteractableTarget.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "InteractableComponent.h"
#include "OverloadComponent.h"
#include "BoobytrapComponent.h"

bool UInteractableTarget::bIsGlobalInteracting = false;

UInteractableTarget::UInteractableTarget()
{
    PrimaryComponentTick.bCanEverTick = true;
    bIsInteracting = false;
}

void UInteractableTarget::BeginPlay()
{
    Super::BeginPlay();
	
    bIsGlobalInteracting = false;
	
    AActor* Owner = GetOwner();
    if (Owner)
    {
        InteractableComponent = Owner->FindComponentByClass<UInteractableComponent>();
        OverloadComponent = Owner->FindComponentByClass<UOverloadComponent>();
        BoobytrapComponent = Owner->FindComponentByClass<UBoobytrapComponent>();
    }
}

void UInteractableTarget::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
	
    bIsGlobalInteracting = false;
}

void UInteractableTarget::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractableTarget::OpenInteractionMenu()
{
    if (bIsGlobalInteracting) 
    {
        UE_LOG(LogTemp, Warning, TEXT("A menu is already open globally. Cannot open another."));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Menu Options:"));

    bool bHasOptions = false;

    if (InteractableComponent && InteractableComponent->IsActive())
    {
        UE_LOG(LogTemp, Warning, TEXT("[T] - Interact"));
        bHasOptions = true;
    }

    if (OverloadComponent && OverloadComponent->IsActive())
    {
        UE_LOG(LogTemp, Warning, TEXT("[Y] - Overload"));
        bHasOptions = true;
    }

    if (BoobytrapComponent && BoobytrapComponent->IsActive())
    {
        UE_LOG(LogTemp, Warning, TEXT("[R] - Boobytrap"));
        bHasOptions = true;
    }
	
    UE_LOG(LogTemp, Warning, TEXT("[C] - Cancel"));

    if (!bHasOptions)
    {
        UE_LOG(LogTemp, Warning, TEXT("No other actions available, showing only Cancel"));
    }

    ClearMenuBindings();

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC && !bIsInteracting)
    {
        if (InteractableComponent && InteractableComponent->IsActive())
        {
            PC->InputComponent->BindAction("InteractAction", IE_Pressed, this, &UInteractableTarget::HandleInteractAction);
        }
        if (OverloadComponent && OverloadComponent->IsActive())
        {
            PC->InputComponent->BindAction("OverloadAction", IE_Pressed, this, &UInteractableTarget::HandleOverloadAction);
        }
        if (BoobytrapComponent && BoobytrapComponent->IsActive())
        {
            PC->InputComponent->BindAction("BoobytrapAction", IE_Pressed, this, &UInteractableTarget::HandleBoobytrapAction);
        }
        PC->InputComponent->BindAction("CancelAction", IE_Pressed, this, &UInteractableTarget::HandleCancelAction);

        bIsInteracting = true;
        bIsGlobalInteracting = true; 
    }
}

void UInteractableTarget::HandleInteractAction()
{
    if (InteractableComponent)
    {
        InteractableComponent->StateInteract();
    }
    ClearMenuBindings(); 
}

void UInteractableTarget::HandleOverloadAction()
{
	if (OverloadComponent)
	{
		OverloadComponent->StateOverload(); 
	}
	ClearMenuBindings();
}


void UInteractableTarget::HandleBoobytrapAction()
{
	if (BoobytrapComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Boobytrap Activated!"));
		BoobytrapComponent->SetBoobytrap();
	}

	ClearMenuBindings();
}



void UInteractableTarget::HandleCancelAction()
{
    UE_LOG(LogTemp, Warning, TEXT("You chose to Cancel"));
    ClearMenuBindings(); 
}

void UInteractableTarget::ClearMenuBindings()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC && bIsInteracting)
    {
        PC->InputComponent->RemoveActionBinding("InteractAction", IE_Pressed);
        PC->InputComponent->RemoveActionBinding("OverloadAction", IE_Pressed);
        PC->InputComponent->RemoveActionBinding("BoobytrapAction", IE_Pressed);
        PC->InputComponent->RemoveActionBinding("CancelAction", IE_Pressed);

        bIsInteracting = false;
        bIsGlobalInteracting = false; 
    }
}