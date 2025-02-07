// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class GP4_TEAM07_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	ACameraPawn();
	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultSceneRoot = nullptr;
	bool isStartingCamera = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UCameraComponent* camera;
	UPROPERTY(EditAnywhere)
	FRotator cameraRotator = GetControlRotation()-GetActorRotation();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	virtual void SetPitch(FRotator _cameraRotator);
	UFUNCTION(BlueprintCallable)
	virtual void SetYaw(FRotator _cameraRotator);
	

};
