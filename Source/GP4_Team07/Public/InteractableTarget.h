#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.h"
#include "OverloadComponent.h"
#include "BoobytrapComponent.h"
#include "InteractableTarget.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GP4_TEAM07_API UInteractableTarget : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractableTarget();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; 

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void OpenInteractionMenu();

private:
	bool bIsInteracting;

	static bool bIsGlobalInteracting;
	
	void HandleInteractAction();
	void HandleOverloadAction();
	void HandleBoobytrapAction();
	void HandleCancelAction();
	
	void ClearMenuBindings();

	UPROPERTY()
	UInteractableComponent* InteractableComponent;

	UPROPERTY()
	UOverloadComponent* OverloadComponent;

	UPROPERTY()
	UBoobytrapComponent* BoobytrapComponent;
};






// Hardcoded version
/*#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableTarget.generated.h"

class UInteractableComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GP4_TEAM07_API UInteractableTarget : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractableTarget();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Function to open the interaction menu
	void OpenInteractionMenu();

	// Handle menu actions
	void HandleInteractAction();
	void HandleOverloadAction();
	void HandleBoobytrapAction();
	void HandleCancelAction();

	// Clear input bindings after menu selection
	void ClearMenuBindings();

private:
	UPROPERTY()
	UInteractableComponent* InteractableComponent;

	// Track whether a menu is currently open (global for all interactable objects)
	static bool bIsGlobalInteracting;

	// Menu state for this specific object
	bool bIsInteracting;
};*/




/*#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableTarget.generated.h"

class UInteractableComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GP4_TEAM07_API UInteractableTarget : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractableTarget();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractableTarget")
	void Interact();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableTarget")
	UInteractableComponent* InteractableComponent;
};
	*/