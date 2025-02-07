// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"

#include "Math/UnitConversion.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	SetRootComponent(DefaultSceneRoot);
	camera = CreateDefaultSubobject<UCameraComponent>("CameraComponnent");
	camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void ACameraPawn::SetPitch(FRotator _cameraRotator)
{
	
}
void ACameraPawn::SetYaw(FRotator _cameraRotator)
{
	
}


