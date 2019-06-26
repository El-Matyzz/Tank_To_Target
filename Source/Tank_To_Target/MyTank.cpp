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

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
	audioComponent = FindComponentByClass<UAudioComponent>();
	extraName = GetWorld()->WorldType == EWorldType::PIE ? "UEDPIE_0_" : "";

	if (GetWorld()->GetMapName() == extraName + "Level_1") {
		totalTargets = targetsLV1;
		timeRemaining = timeLV1;
	}
	else {
		totalTargets = targetsLV2;
		timeRemaining = timeLV2;
	}
	armor = maxArmor;
	fireTimer = fireDelay;
	bossBarFill = 1;
	armorBarFill = 1;
	isCountingDown = false;
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

	if (destroyedTargets == totalTargets)
		Win();

	if (GetWorld()->GetMapName() != extraName + "Level_1" || GetWorld()->GetMapName() != extraName + "Level_2")
		timeRemaining -= DeltaTime;

	armorBarFill = armor / maxArmor;
	fireTimer += DeltaTime;
	powerUpTimer -= DeltaTime;
	remainingTargets = totalTargets - destroyedTargets;

	if (powerUpTimer <= 0) {
		unlimitedFireRate = false;
		shotgunMode = false;
	}

	if (armor <= 0 || timeRemaining <= 0)
		Lose();

	if (timeRemaining <= 5 && !isCountingDown){
		audioComponent->Stop();
		audioComponent->Sound = countdown;
		audioComponent->Play();
		isCountingDown = true;
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
	PlayerInputComponent->BindAction("Continue", IE_Pressed, this, &AMyTank::Continue);
}

void AMyTank::MoveX(float val)
{
	if (won) return;

	isMovingX = val != 0;
	if (isMovingY)
		val *= 0.5f;

	currentVelocity.X = val * 100 * speed;
}

void AMyTank::MoveY(float val)
{
	if (won) return;

	isMovingY = val != 0;
	if (isMovingX)
		val *= 0.5f;

	currentVelocity.Y = -val * 100 * speed;
}

void AMyTank::RotateX(float val)
{
	if (won) return;

	FRotator rot = upperBody->RelativeRotation;
	rot.Yaw += rotationSpeed * val;
	upperBody->SetRelativeRotation(rot);
}

void AMyTank::RotateY(float val)
{
	if (won) return;

	FRotator rot = rotor->RelativeRotation;
	rot.Roll -= rotationSpeed * val * 0.5f;
	if (rot.Roll > 15) rot.Roll = 15;
	else if (rot.Roll < -20) rot.Roll = -20;

	rotor->SetRelativeRotation(rot);
}

void AMyTank::Shoot()
{
	if (won) return;

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

void AMyTank::Win()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0001f);
	won = true;
	audioComponent->Stop();
	audioComponent->Sound = complete;
	audioComponent->Play();

	if (GetWorld()->GetMapName() == extraName + "Level_3")
		UGameplayStatics::OpenLevel(GetWorld(), "Complete");
}

void AMyTank::Lose()
{
	if (GetWorld()->GetMapName() == extraName + "Level_1")
		UGameplayStatics::OpenLevel(GetWorld(), "Lose_1");
	else if (GetWorld()->GetMapName() == extraName + "Level_2")
		UGameplayStatics::OpenLevel(GetWorld(), "Lose_2");
	else if (GetWorld()->GetMapName() == extraName + "Level_3")
		UGameplayStatics::OpenLevel(GetWorld(), "Lose_3");
}

void AMyTank::Continue()
{
	if (!won) return;

	if (GetWorld()->GetMapName() == extraName + "Level_1")
		UGameplayStatics::OpenLevel(GetWorld(), "Victory_1");
	else
		UGameplayStatics::OpenLevel(GetWorld(), "Victory_2");
}

void AMyTank::SetGamePaused(bool isPaused)
{
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (MyPlayer != NULL)
		MyPlayer->SetPause(isPaused);
}