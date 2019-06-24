// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTarget.h"
#include "MyTank.h"

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

	float val = rand() % 100 + 1;
	if (GetWorld()->GetMapName() == "UEDPIE_0_Level_1") {
		if (val <= 70) {
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
		if (val <= 20) {
			MyComp->SetMaterial(0, mat1);
			targetType = 1;
		}
		else if (val <= 65) {
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

	if (targetType == 3 || targetType == 4) {
		disappearTimer += DeltaTime;
		if (disappearTimer >= 4) {
			SetActorScale3D(FVector(currentScale.X - (DeltaTime * maxScale), currentScale.Y - (DeltaTime * maxScale), currentScale.Z - (DeltaTime * maxScale)));
			if (currentScale.X <= 0)
				Destroy();
		}
	}
}

void AMyTarget::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Purple, "OH NO!");

		if (targetType == 4) {
			player->destroyedTargets--;
			MyComp->SetEnableGravity(true);
		}
		else {
			player->destroyedTargets++;
			if (targetType == 3)
				GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Blue, "Releasing Power-ups!");
			Destroy();
		}
	}
}