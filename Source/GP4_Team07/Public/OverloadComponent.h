#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "OverloadComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOverloadStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOverloadFinished);

UENUM(BlueprintType)
enum class E_OverloadState : uint8
{
	NotOverloaded UMETA(DisplayName = "NotOverloaded"),
	Overloaded UMETA(DisplayName = "Overloaded")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GP4_TEAM07_API UOverloadComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOverloadComponent();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnOverloadStarted OnOverloadStarted;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnOverloadFinished OnOverloadFinished;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overload")
	float OverloadDuration;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	E_OverloadState OverloadState;

	float CurrentCountdownTime;
	FTimerHandle CountdownTimerHandle;

	UPROPERTY()
	class UBoobytrapComponent* BoobytrapComponent;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Overload")
	void StateOverload();

	void UpdateCountdown();

private:
	void EndOverload();

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};




/*#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "OverloadComponent.generated.h"

// Declare event dispatcher
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOverloadStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOverloadFinished);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GP4_TEAM07_API UOverloadComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOverloadComponent();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnOverloadStarted OnOverloadStarted;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnOverloadFinished OnOverloadFinished;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	USphereComponent* SphereComponent;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UShapeComponent* RootComponent;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};*/
