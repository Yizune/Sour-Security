#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableTarget.h"
#include "CollisionQueryParams.h"
#include "GameFramework/Pawn.h"
#include "InteractComponent.generated.h"

class USphereComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GP4_TEAM07_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void InteractableObjectCheck();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bCanInteract;

private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* InteractionSphere;
	
	UPROPERTY()
	FHitResult AimHit;
	
	UPROPERTY()
	UInteractableTarget* InteractableTarget;
	
	FCollisionQueryParams CollisionParams;
	
	UFUNCTION()
	void HandleInteract();
	
	UPROPERTY()
	APawn* OwningPawn;
	
	UPROPERTY()
	bool bIsMenuOpen;
};






/* 
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableTarget.h"
#include "CollisionQueryParams.h" 
#include "GameFramework/Pawn.h"
#include "InteractComponent.generated.h"

class USphereComponent;  

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GP4_TEAM07_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void InteractableObjectCheck();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bCanInteract;

private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* InteractionSphere;

	UPROPERTY()
	FHitResult AimHit;

	UPROPERTY()
	UInteractableTarget* InteractableTarget; 
		
	FCollisionQueryParams CollisionParams; 

	UFUNCTION()
	void HandleInteract();
	
	UPROPERTY()
	APawn* OwningPawn;
};
*/
