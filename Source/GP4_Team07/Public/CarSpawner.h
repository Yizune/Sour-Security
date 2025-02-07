#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CarSpawner.generated.h"

UCLASS()
class GP4_TEAM07_API ACarSpawner : public AActor
{
    GENERATED_BODY()

public:    
    ACarSpawner();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void Tick(float DeltaTime) override;

    // Array of skeletal meshes for the cars
    UPROPERTY(EditAnywhere, Category = "Car Config")
    TArray<USkeletalMesh*> CarMeshes;

    // Array of materials for the cars
    UPROPERTY(EditAnywhere, Category = "Car Config")
    TArray<UMaterialInterface*> CarMaterials;

    // Array of spawn points for cars
    UPROPERTY(EditAnywhere, Category = "Spawn Config")
    TArray<AActor*> CarSpawnPoints;

    // Array to keep track of spawned cars
    UPROPERTY()
    TArray<AActor*> SpawnedCars;

    // Speed of the cars
    UPROPERTY(EditAnywhere, Category = "Car Config")
    float CarSpeed = 700.0f;

    // Timer handles for car spawn points
    TArray<FTimerHandle> CarSpawnTimers;

    // Function to spawn a random car at a spawn point
    void SpawnRandomCar(AActor* SpawnPoint);

    // Function to set the next car spawn timer
    void SetNextCarSpawnTimer(AActor* SpawnPoint);

    // Function to find an animation blueprint starting with "CarWheelRotation"
    UAnimBlueprint* FindCarWheelRotationAnimBP();
};
