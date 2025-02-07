#pragma once

#include "CoreMinimal.h"
#include "OverloadComponent.h"
#include "BoobytrapComponent.h"
#include "InteractableTarget.h"
#include "GameFramework/Actor.h"
#include "Interactable_Distractable_Parent.generated.h"

class UInteractableComponent;

UCLASS()
class GP4_TEAM07_API AInteractable_Distractable_Parent : public AActor
{
    GENERATED_BODY()

public:
    AInteractable_Distractable_Parent();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    UInteractableComponent* InteractableComponent;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    UOverloadComponent* OverloadComponent;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    UBoobytrapComponent* BoobytrapComponent;

    UPROPERTY()
    UInteractableTarget* InteractableTarget;

    UFUNCTION()
    virtual void OnInteractionStarted_Event();

    UFUNCTION()
    virtual void OnInteractionFinished_Event();

    UFUNCTION()
    virtual void OnOverloadStarted_Event();

    UFUNCTION()
    virtual void OnOverloadFinished_Event();

public:
    virtual void Tick(float DeltaTime) override;
};
