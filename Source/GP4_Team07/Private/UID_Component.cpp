// Fill out your copyright notice in the Description page of Project Settings.


#include "UID_Component.h"

// Sets default values for this component's properties
UUID_Component::UUID_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUID_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FGuid NewGuid = FGuid::NewGuid();
	UniqueID = NewGuid.ToString();
	
}


// Called every frame
void UUID_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

