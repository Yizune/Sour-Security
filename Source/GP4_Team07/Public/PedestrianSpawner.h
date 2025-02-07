#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PedestrianSpawner.generated.h"

UCLASS()
class GP4_TEAM07_API APedestrianSpawner : public AActor
{
	GENERATED_BODY()
    
public:    
	// Sets default values for this actor's properties
	APedestrianSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<AActor*> PedestrianSpawnPoints;
	
	TArray<AActor*> SpawnedPedestrians;
	
	TArray<FTimerHandle> PedestrianSpawnTimers;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedestrian Spawner", meta = (AllowPrivateAccess = "true"))
	float MinSpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedestrian Spawner", meta = (AllowPrivateAccess = "true"))
	float MaxSpawnTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedestrian Movement", meta = (AllowPrivateAccess = "true"))
	float PedestrianSpeed = 150.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedestrian Spawner", meta = (AllowPrivateAccess = "true"))
	TArray<USkeletalMesh*> PedestrianMeshes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedestrian Animation", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UAnimInstance> WalkingOnlyAnimBlueprintClass;

	void SpawnRandomPedestrian(AActor* SpawnPoint);
	void SetNextPedestrianSpawnTimer(AActor* SpawnPoint);
};
