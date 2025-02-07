#include "PedestrianSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/World.h"

APedestrianSpawner::APedestrianSpawner()
{
    PrimaryActorTick.bCanEverTick = true;
    
    static ConstructorHelpers::FClassFinder<UAnimInstance> WalkingOnlyBP(TEXT("/Game/Core/AI/Animation/WalkingOnly"));
    if (WalkingOnlyBP.Succeeded())
    {
        WalkingOnlyAnimBlueprintClass = WalkingOnlyBP.Class;
    }
    
    MinSpawnTime = 10.0f;
    MaxSpawnTime = 15.0f;
}

void APedestrianSpawner::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("PedestrianSpawner BeginPlay called"));
    
    TArray<AActor*> PedestrianSpawnPointActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), PedestrianSpawnPointActors);

    for (AActor* Actor : PedestrianSpawnPointActors)
    {
        if (Actor->GetName().Contains("PedestrianSpawnPoint"))
        {
            PedestrianSpawnPoints.Add(Actor);
            SetNextPedestrianSpawnTimer(Actor); 
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Found %d PedestrianSpawnPoints"), PedestrianSpawnPoints.Num());
}

void APedestrianSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    for (int32 i = SpawnedPedestrians.Num() - 1; i >= 0; i--)
    {
        AActor* Pedestrian = SpawnedPedestrians[i];
        if (Pedestrian)
        {
            USkeletalMeshComponent* PedestrianMeshComponent = Pedestrian->FindComponentByClass<USkeletalMeshComponent>();
            if (PedestrianMeshComponent)
            {
                FVector CurrentLocation = Pedestrian->GetActorLocation();
                FVector ForwardVector = Pedestrian->GetActorForwardVector();
                FVector NewLocation = CurrentLocation + (ForwardVector * PedestrianSpeed * DeltaTime);
                Pedestrian->SetActorLocation(NewLocation);

                if (NewLocation.X > 10000.0f || NewLocation.X < -10000.0f || NewLocation.Y > 10000.0f || NewLocation.Y < -10000.0f)
                {
                    Pedestrian->Destroy();
                    SpawnedPedestrians.RemoveAt(i);
                }
            }
        }
    }
}

void APedestrianSpawner::SetNextPedestrianSpawnTimer(AActor* SpawnPoint)
{
    float RandomCooldown = FMath::RandRange(MinSpawnTime, MaxSpawnTime);
    FTimerHandle NewTimer;
    GetWorld()->GetTimerManager().SetTimer(NewTimer, [this, SpawnPoint]() { SpawnRandomPedestrian(SpawnPoint); }, RandomCooldown, false);
    PedestrianSpawnTimers.Add(NewTimer);
}

void APedestrianSpawner::SpawnRandomPedestrian(AActor* SpawnPoint)
{
    UE_LOG(LogTemp, Warning, TEXT("SpawnRandomPedestrian called"));

    if (PedestrianMeshes.Num() > 0)
    {
        int32 RandomMeshIndex = FMath::RandRange(0, PedestrianMeshes.Num() - 1);
        FVector SpawnLocation = SpawnPoint->GetActorLocation();
        FRotator SpawnRotation = SpawnPoint->GetActorRotation();

        FTransform SpawnTransform;
        SpawnTransform.SetLocation(SpawnLocation);
        SpawnTransform.SetRotation(SpawnRotation.Quaternion());

        AActor* SpawnedPedestrian = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), SpawnTransform);
        if (SpawnedPedestrian)
        {
            USceneComponent* RootSceneComponent = NewObject<USceneComponent>(SpawnedPedestrian);
            RootSceneComponent->RegisterComponent();
            SpawnedPedestrian->SetRootComponent(RootSceneComponent);

            USkeletalMeshComponent* PedestrianMeshComponent = NewObject<USkeletalMeshComponent>(SpawnedPedestrian);
            if (PedestrianMeshComponent)
            {
                PedestrianMeshComponent->RegisterComponent();
                PedestrianMeshComponent->SetSkeletalMesh(PedestrianMeshes[RandomMeshIndex]);
                PedestrianMeshComponent->AttachToComponent(RootSceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

                if (WalkingOnlyAnimBlueprintClass)
                {
                    PedestrianMeshComponent->SetAnimInstanceClass(WalkingOnlyAnimBlueprintClass);
                    PedestrianMeshComponent->SetAnimationMode(EAnimationMode::AnimationBlueprint);
                }

                FRotator MeshRotation = PedestrianMeshComponent->GetRelativeRotation();
                MeshRotation.Yaw += -90.0f;
                PedestrianMeshComponent->SetRelativeRotation(MeshRotation);

                SpawnedPedestrian->SetActorTransform(SpawnTransform);

                UE_LOG(LogTemp, Warning, TEXT("Final Pedestrian Forward Vector: %s"), *SpawnedPedestrian->GetActorForwardVector().ToString());

                SpawnedPedestrians.Add(SpawnedPedestrian);
            }
        }
        SetNextPedestrianSpawnTimer(SpawnPoint); 
    }
}
