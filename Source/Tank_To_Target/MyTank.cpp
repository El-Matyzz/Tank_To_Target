// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTank.h"


// Sets default values
AMyTank::AMyTank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyTank::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetMapName() == "UEDPIE_0_Level_1") {
		totalTargets = 10;
		timeRemaining = 40;
	}
	else {
		totalTargets = 20;
		timeRemaining = 60;
	}
	armor = 5;
	fireTimer = fireDelay;
	shotgunMode = true;
}

// Called every frame
void AMyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!currentVelocity.IsZero())
	{
		FVector newLocation = GetActorLocation() + (currentVelocity * DeltaTime);
		SetActorLocation(newLocation);
	}

	if(destroyedTargets == totalTargets)
		GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Green, "WIN!");

	timeRemaining -= DeltaTime;
	fireTimer += DeltaTime;

	if(armor <= 0 || timeRemaining <= 0)
		GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Green, "LOSE!");
}

// Called to bind functionality to input
void AMyTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move X", this, &AMyTank::MoveX);
	PlayerInputComponent->BindAxis("Move Y", this, &AMyTank::MoveY);
	PlayerInputComponent->BindAxis("Rotate X", this, &AMyTank::RotateX);
	PlayerInputComponent->BindAxis("Rotate Y", this, &AMyTank::RotateY);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyTank::Shoot);
}

void AMyTank::MoveX(float val)
{
	isMovingX = val != 0;
	if (isMovingY)
		val *= 0.5f;

	currentVelocity.X = val * 100 * speed;
}

void AMyTank::MoveY(float val)
{
	isMovingY = val != 0;
	if (isMovingX)
		val *= 0.5f;

	currentVelocity.Y = -val * 100 * speed;
}

void AMyTank::RotateX(float val)
{
	FRotator rot = upperBody->RelativeRotation;
	rot.Yaw += rotationSpeed * val;
	upperBody->SetRelativeRotation(rot);
}

void AMyTank::RotateY(float val)
{
	FRotator rot = rotor->RelativeRotation;
	rot.Roll -= rotationSpeed * val * 0.5f;
	if (rot.Roll > 15) rot.Roll = 15;
	else if (rot.Roll < -20) rot.Roll = -20;

	rotor->SetRelativeRotation(rot);
}

void AMyTank::Shoot()
{
	if (fireTimer >= fireDelay || unlimitedFireRate)
	{
		if (shotgunMode)
		{
			for (int i = 0; i <= shotgunPellets; i++)
			{
				FRotator rot = PH->GetComponentRotation();
				rot.Yaw += FMath::FRandRange(-shotgunSpread, shotgunSpread);
				rot.Roll += FMath::FRandRange(-shotgunSpread, shotgunSpread);
				GetWorld()->SpawnActor<AMyBullet>(bullet, PH->GetComponentLocation(), rot, FActorSpawnParameters());
			}
		}
		else GetWorld()->SpawnActor<AMyBullet>(bullet, PH->GetComponentLocation(), PH->GetComponentRotation(), FActorSpawnParameters());
		fireTimer = 0;
	}
}

void AMyTank::UnlimitedFireRate()
{
	unlimitedFireRate = true;
	shotgunMode = false;
	powerUpTimer = powerUpTime;
}

void AMyTank::ShotgunMode()
{
	unlimitedFireRate = false;
	shotgunMode = true;
	powerUpTimer = powerUpTime;
}