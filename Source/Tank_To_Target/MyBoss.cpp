// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBoss.h"


// Sets default values
AMyBoss::AMyBoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyBoss::BeginPlay()
{
	Super::BeginPlay();
	ChangeDirection();
	life = maxLife;
	baseSpeed *= 100;
	enragedSpeed *= 100;

	anim = Cast<UMyAnimInstance>(FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance());
}

// Called every frame
void AMyBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!anim->isDead) {
		directionTimer += DeltaTime;
		shootTimer += DeltaTime;

		if (isEnraged)
		{
			if (directionTimer >= enragedDirectionTime)
				ChangeDirection();
			if (shootTimer >= enragedShootTime) {
				anim->isAttacking = true;
				justShot = false;
			}
			Move(enragedSpeed, DeltaTime);
		}
		else
		{
			if (directionTimer >= baseDirectionTime)
				ChangeDirection();
			if (shootTimer >= baseShootTime) {
				anim->isAttacking = true;
				justShot = false;
			}
			Move(baseSpeed, DeltaTime);
		}

		if (anim->isAttacking) {
			attackEndTimer += DeltaTime;
			LookAtPlayer();
			anim->isRunning = false;
			anim->isWalking = false;
			if (attackEndTimer >= shootTime)
				if (attackEndTimer >= 2.3f) {
					anim->isAttacking = false;
					attackEndTimer = 0;
				}
				else if (!justShot)
					Shoot();
		}
	}
	else
	{
		dieEndTimer += DeltaTime;
		if (dieEndTimer >= dieTime) {
			AActor* playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
			AMyTank* player = Cast<AMyTank>(playerActor);
			player->Win();
		}
	}
}

void AMyBoss::ChangeDirection()
{
	directionTimer = 0;
	targetPosition.X = FMath::RandRange(minBounds.X, maxBounds.X);
	targetPosition.Y = FMath::RandRange(minBounds.Y, maxBounds.Y);
	targetPosition.Z = GetActorLocation().Z;
}

void AMyBoss::Move(float speed, float deltaTime)
{
	if (anim->isAttacking || anim->isDead) return;
	else if (isEnraged) {
		anim->isRunning = true;
		anim->isWalking = false;
	}
	else {
		anim->isRunning = false;
		anim->isWalking = true;
	}

	FVector dir = targetPosition - GetActorLocation();
	dir.Normalize();
	SetActorRotation(dir.Rotation());
	AddActorLocalOffset(GetActorForwardVector() * deltaTime * speed);
}

void AMyBoss::LookAtPlayer()
{
	FVector playerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	playerPos.Z = GetActorLocation().Z;
	FVector dir = playerPos - GetActorLocation();
	SetActorRotation(dir.Rotation() + FRotator(0, -90, 0));
}

void AMyBoss::Shoot()
{
	shootTimer = 0;
	justShot = true;
	AActor* playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	FRotator rot = (playerActor->GetActorLocation() - PH->GetComponentLocation()).Rotation();
	GetWorld()->SpawnActor<AMyBossBullet>(bullet, PH->GetComponentLocation(), rot, FActorSpawnParameters());
}

void AMyBoss::Die()
{
	anim->isDead = true;
}

void AMyBoss::Enrage()
{
	isEnraged = true;
}