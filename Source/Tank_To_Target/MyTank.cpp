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
	GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Blue, "SHOOT!");
	FActorSpawnParameters p;
	GetWorld()->SpawnActor<AMyBullet>(bullet, PH->GetComponentLocation(), PH->GetComponentRotation(), p);
}