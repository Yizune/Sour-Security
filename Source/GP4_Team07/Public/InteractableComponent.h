#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

UENUM(BlueprintType)
enum class E_ActivityState : uint8
{
    Inactive UMETA(DisplayName = "Inactive"),
    Active UMETA(DisplayName = "Active")
};

// Declare event dispatcher
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionFinished);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GP4_TEAM07_API UInteractableComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInteractableComponent();
    
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnInteractionStarted OnInteractionStarted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnInteractionFinished OnInteractionFinished;

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "Interactable")
    void StateInteract();

    UFUNCTION(BlueprintCallable, Category = "Interactable")
    void ToggleState(); 

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
    E_ActivityState ActivityState; 
};
