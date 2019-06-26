// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBoss.h"


// Sets default values
AMyBoss::AMyBoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMComp"));
	MyComp->SetSimulatePhysics(false);
	MyComp->SetEnableGravity(false);
	MyComp->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AMyBoss::BeginPlay()
{
	Super::BeginPlay();
	ChangeDirection();
	life = maxLife;
	baseSpeed *= 100;
	enragedSpeed *= 100;
}

// Called every frame
void AMyBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	directionTimer += DeltaTime;
	shootTimer += DeltaTime;

	if (isEnraged)
	{
		if (directionTimer >= enragedDirectionTime)
			ChangeDirection();
		if (shootTimer >= enragedShootTime)
			Shoot();
		Move(enragedSpeed, DeltaTime);
	}
	else
	{
		if (directionTimer >= baseDirectionTime)
			ChangeDirection();
		if (shootTimer >= baseShootTime)
			Shoot();
		Move(baseSpeed, DeltaTime);
	}
}

void AMyBoss::ChangeDirection()
{
	directionTimer = 0;
	targetPosition.X = FMath::RandRange(minBounds.X, maxBounds.X);
	targetPosition.Y = FMath::RandRange(minBounds.Y, maxBounds.Y);
	targetPosition.Z = FMath::RandRange(minBounds.Z, maxBounds.Z);
}

void AMyBoss::Move(float speed, float deltaTime)
{
	FVector dir = targetPosition - GetActorLocation();
	dir.Normalize();
	AddActorLocalOffset(dir * deltaTime * speed);
}

void AMyBoss::Shoot()
{
	shootTimer = 0;
	int i = isEnraged ? rand() % 8 : rand() % 4;
	AActor* playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	AMyTank* player = Cast<AMyTank>(playerActor);
	FRotator rot = (player->GetActorLocation() - allPHs[i]->GetComponentLocation()).Rotation();
	GetWorld()->SpawnActor<AMyBossBullet>(bullet, allPHs[i]->GetComponentLocation(), rot, FActorSpawnParameters());
}

void AMyBoss::Die()
{
	AActor* playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	AMyTank* player = Cast<AMyTank>(playerActor);
	player->Win();
}

void AMyBoss::Enrage()
{
	isEnraged = true;
	MyComp->SetStaticMesh(enragedMesh);
}