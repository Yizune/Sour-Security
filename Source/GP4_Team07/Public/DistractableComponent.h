// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "DistractableComponent.generated.h"

// Declare event dispatcher
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDistractionStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDistractionFinished);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GP4_TEAM07_API UDistractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDistractableComponent();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDistractionStarted OnDistractionStarted;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDistractionFinished OnDistractionFinished;

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
};
