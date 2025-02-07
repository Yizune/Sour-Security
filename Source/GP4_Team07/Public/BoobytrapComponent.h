#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoobytrapComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBoobytrapStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBoobytrapFinished);

UENUM(BlueprintType)
enum class E_BoobytrapState : uint8
{
	NotBoobytrapped UMETA(DisplayName = "NotBoobytrapped"),
	Boobytrapped UMETA(DisplayName = "Boobytrapped")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GP4_TEAM07_API UBoobytrapComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBoobytrapComponent();
	
	UPROPERTY()
	class UOverloadComponent* OverloadComponent;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBoobytrapStarted OnBoobytrapStarted;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBoobytrapFinished OnBoobytrapFinished;

	UFUNCTION(BlueprintCallable)
	void SetBoobytrap();

	UFUNCTION()
	void TriggerBoobytrap();

	E_BoobytrapState GetBoobytrapState() const { return BoobytrapState; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	E_BoobytrapState BoobytrapState;

	UFUNCTION()
	void EndBoobytrap();
protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle BoobytrapTimerHandle;
};
