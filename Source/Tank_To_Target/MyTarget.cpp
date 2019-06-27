// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTarget.h"

// Sets default values
AMyTarget::AMyTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMComp"));
	MyComp->SetSimulatePhysics(true);
	MyComp->SetEnableGravity(false);
	MyComp->SetNotifyRigidBodyCollision(true);
	MyComp->OnComponentHit.AddDynamic(this, &AMyTarget::OnCompHit);
}

// Called when the game starts or when spawned
void AMyTarget::BeginPlay()
{
	Super::BeginPlay();
	AActor* playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	player = Cast<AMyTank>(playerActor);

	SetActorScale3D(FVector(0, 0, 0));
	FString extraName = GetWorld()->WorldType == EWorldType::PIE ? "UEDPIE_0_" : "";

	float val = rand() % 100 + 1;
	if (GetWorld()->GetMapName() == extraName + "Level_1") {
		if (val <= 60) {
			MyComp->SetMaterial(0, mat1);
			targetType = 1;
		}
		else if (val <= 90) {
			MyComp->SetMaterial(0, mat3);
			targetType = 3;
		}
		else {
			MyComp->SetMaterial(0, mat4);
			targetType = 4;
		}
	}
	else {
		if (val <= 10) {
			MyComp->SetMaterial(0, mat1);
			targetType = 1;
		}
		else if (val <= 55) {
			MyComp->SetMaterial(0, mat2);
			targetType = 2;
		}
		else if (val <= 85) {
			MyComp->SetMaterial(0, mat3);
			targetType = 3;
		}
		else {
			MyComp->SetMaterial(0, mat4);
			targetType = 4;
		}
	}
}

// Called every frame
void AMyTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorRotation((player->GetActorLocation() - GetActorLocation()).Rotation());

	FVector currentScale = GetActorScale3D();
	if (currentScale.X < maxScale)
		SetActorScale3D(FVector(currentScale.X + (DeltaTime * maxScale), currentScale.Y + (DeltaTime * maxScale), currentScale.Z + (DeltaTime * maxScale)));

	disappearTimer += DeltaTime;
	if (((targetType == 3 || targetType == 4) && disappearTimer >= 4) ||
		((targetType == 1 || targetType == 2) && disappearTimer >= 9)) {
		SetActorScale3D(FVector(currentScale.X - (DeltaTime * maxScale), currentScale.Y - (DeltaTime * maxScale), currentScale.Z - (DeltaTime * maxScale)));
		if (currentScale.X <= 0)
			Destroy();
	}

	if (targetType == 2)
		AddActorLocalOffset(GetActorRightVector() * movementSpeed * DeltaTime * FMath::Sin(GetGameTimeSinceCreation()));
}

void AMyTarget::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (Cast<AMyBullet>(OtherActor) != NULL) {
			if (targetType == 4) {
				player->destroyedTargets--;
				MyComp->SetEnableGravity(true);
				MyComp->AddForceAtLocation(GetActorForwardVector() * -10000, OtherActor->GetActorLocation());
			}
			else {
				player->destroyedTargets++;
				if (targetType == 3)
					SpawnPowerUps();
				Destroy();
			}
		}
		else Destroy();
	}
}

void AMyTarget::SpawnPowerUps()
{
	FActorSpawnParameters p;
	GetWorld()->SpawnActor<AMyPowerUp>(fireRate, PH1->GetComponentLocation(), (PH1->GetComponentLocation() - GetActorLocation()).Rotation(), p);
	GetWorld()->SpawnActor<AMyPowerUp>(shotgun, PH2->GetComponentLocation(), (PH2->GetComponentLocation() - GetActorLocation()).Rotation(), p);
}