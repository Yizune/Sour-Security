#pragma once

#include "CoreMinimal.h"
#include "Interactable_Distractable_Parent.h"
#include "MyTestChild.generated.h"

UCLASS()
class GP4_TEAM07_API AMyTestChild : public AInteractable_Distractable_Parent
{
	GENERATED_BODY()

public:
	// Constructor declaration
	AMyTestChild();



protected:
	virtual void BeginPlay() override;

	virtual void OnInteractionStarted_Event() override;
	virtual void OnInteractionFinished_Event() override;
	virtual void OnOverloadStarted_Event() override;
	virtual void OnOverloadFinished_Event() override;
};
