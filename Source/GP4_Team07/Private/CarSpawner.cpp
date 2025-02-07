#include "CarSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimBlueprint.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/UObjectIterator.h"
#include "Engine/World.h"
#include "TimerManager.h"

ACarSpawner::ACarSpawner()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ACarSpawner::BeginPlay()
{
    Super::BeginPlay();
    
    TArray<AActor*> CarSpawnPointActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), CarSpawnPointActors);

    for (AActor* Actor : CarSpawnPointActors)
    {
        if (Actor->GetName().Contains("CarSpawnPoint"))
        {
            CarSpawnPoints.Add(Actor);
            SetNextCarSpawnTimer(Actor);
        }
    }
}

void ACarSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    for (int32 i = SpawnedCars.Num() - 1; i >= 0; i--)
    {
        AActor* Car = SpawnedCars[i];
        if (Car)
        {
            FVector ForwardVector = Car->GetActorForwardVector();
            FVector NewLocation = Car->GetActorLocation() + (ForwardVector * CarSpeed * DeltaTime);
            Car->SetActorLocation(NewLocation);
            
            if (NewLocation.X > 10000.0f || NewLocation.X < -10000.0f || NewLocation.Y > 10000.0f || NewLocation.Y < -10000.0f)
            {
                Car->Destroy();
                SpawnedCars.RemoveAt(i);
            }
        }
    }
}

void ACarSpawner::SetNextCarSpawnTimer(AActor* SpawnPoint)
{
    float RandomCooldown = FMath::RandRange(10.0f, 15.0f);
    FTimerHandle NewTimer;
    GetWorld()->GetTimerManager().SetTimer(NewTimer, [this, SpawnPoint]() { SpawnRandomCar(SpawnPoint); }, RandomCooldown, false);
    CarSpawnTimers.Add(NewTimer);
}

void ACarSpawner::SpawnRandomCar(AActor* SpawnPoint)
{
    if (CarMeshes.Num() > 0 && CarMaterials.Num() > 0)
    {
        int32 RandomMeshIndex = FMath::RandRange(0, CarMeshes.Num() - 1);
        int32 RandomMaterialIndex = FMath::RandRange(0, CarMaterials.Num() - 1);
        FVector SpawnLocation = SpawnPoint->GetActorLocation();
        FRotator SpawnRotation = SpawnPoint->GetActorRotation();

        FTransform SpawnTransform(SpawnRotation, SpawnLocation);
        AActor* SpawnedCar = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), SpawnTransform);

        if (SpawnedCar)
        {
            USkeletalMeshComponent* CarMeshComponent = NewObject<USkeletalMeshComponent>(SpawnedCar);
            CarMeshComponent->RegisterComponentWithWorld(GetWorld());
            CarMeshComponent->SetSkeletalMesh(CarMeshes[RandomMeshIndex]);
            CarMeshComponent->SetMaterial(0, CarMaterials[RandomMaterialIndex]);
            SpawnedCar->SetRootComponent(CarMeshComponent);
            SpawnedCar->SetActorTransform(SpawnTransform);

            // Hardcoded approach: statically load one animation per car based on index
            UAnimBlueprint* SelectedAnimBlueprint = nullptr;
            switch (RandomMeshIndex)
            {
                case 0:
                    SelectedAnimBlueprint = Cast<UAnimBlueprint>(StaticLoadObject(UAnimBlueprint::StaticClass(), nullptr, TEXT("/Game/Developers/stevanlikusic/CarWheelRotation1.CarWheelRotation1")));
                    break;
                case 1:
                    SelectedAnimBlueprint = Cast<UAnimBlueprint>(StaticLoadObject(UAnimBlueprint::StaticClass(), nullptr, TEXT("/Game/Developers/stevanlikusic/CarWheelRotation2.CarWheelRotation2")));
                    break;
                case 2:
                    SelectedAnimBlueprint = Cast<UAnimBlueprint>(StaticLoadObject(UAnimBlueprint::StaticClass(), nullptr, TEXT("/Game/Developers/stevanlikusic/CarWheelRotation3.CarWheelRotation3")));
                    break;
                case 3:
                    SelectedAnimBlueprint = Cast<UAnimBlueprint>(StaticLoadObject(UAnimBlueprint::StaticClass(), nullptr, TEXT("/Game/Developers/stevanlikusic/CarWheelRotation4.CarWheelRotation4")));
                    break;
                case 4:
                    SelectedAnimBlueprint = Cast<UAnimBlueprint>(StaticLoadObject(UAnimBlueprint::StaticClass(), nullptr, TEXT("/Game/Developers/stevanlikusic/CarWheelRotation5.CarWheelRotation5")));
                    break;
                default:
                    UE_LOG(LogTemp, Error, TEXT("Invalid RandomMeshIndex for car"));
                    break;
            }

            if (SelectedAnimBlueprint)
            {
                CarMeshComponent->SetAnimInstanceClass(SelectedAnimBlueprint->GeneratedClass);
                UE_LOG(LogTemp, Warning, TEXT("Assigned Animation Blueprint: %s to the car"), *SelectedAnimBlueprint->GetName());
                
                UAnimInstance* AnimInstance = CarMeshComponent->GetAnimInstance();
                if (AnimInstance)
                {
                    CarMeshComponent->Play(true);  
                    UE_LOG(LogTemp, Warning, TEXT("Animation is forced to play."));
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("AnimInstance is NULL. Animation not applied."));
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to assign animation blueprint to the car."));
            }

            SpawnedCars.Add(SpawnedCar);
        }
    }
    SetNextCarSpawnTimer(SpawnPoint);
}
