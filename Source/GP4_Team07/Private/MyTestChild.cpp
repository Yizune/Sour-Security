#include "MyTestChild.h"
#include "InteractableComponent.h"
#include "OverloadComponent.h"
#include "BoobytrapComponent.h"

AMyTestChild::AMyTestChild()
{

}

void AMyTestChild::BeginPlay()
{
	Super::BeginPlay();
	
	if (OverloadComponent)
	{
		OverloadComponent->SetActive(false); 
	}

	if (BoobytrapComponent)
	{
		BoobytrapComponent->SetActive(false); 
	}

	// Can also completely destroy components if they're not needed at all
	// OverloadComponent->DestroyComponent();
	// BoobytrapComponent->DestroyComponent();
}

void AMyTestChild::OnInteractionStarted_Event()
{
	UE_LOG(LogTemp, Display, TEXT("MyTestChild: Interaction Started"));
}

void AMyTestChild::OnInteractionFinished_Event()
{
	UE_LOG(LogTemp, Display, TEXT("MyTestChild: Interaction Finished"));
}

void AMyTestChild::OnOverloadStarted_Event()
{
	UE_LOG(LogTemp, Display, TEXT("MyTestChild: Distraction Started"));
}

void AMyTestChild::OnOverloadFinished_Event()
{
	UE_LOG(LogTemp, Display, TEXT("MyTestChild: Distraction Finished"));
}
