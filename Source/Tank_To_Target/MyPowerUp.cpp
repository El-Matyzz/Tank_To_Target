// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPowerUp.h"


// Sets default values
AMyPowerUp::AMyPowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMComp"));
	MyComp->SetSimulatePhysics(true);
	MyComp->SetEnableGravity(true);
	MyComp->SetNotifyRigidBodyCollision(true);
	MyComp->OnComponentHit.AddDynamic(this, &AMyPowerUp::OnCompHit);
}

// Called when the game starts or when spawned
void AMyPowerUp::BeginPlay()
{
	Super::BeginPlay();

	AActor* playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	player = Cast<AMyTank>(playerActor);

	MyComp->AddForce(GetActorForwardVector() * 1000000000 * force);
}

// Called every frame
void AMyPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	destroyTimer += DeltaTime;
	if (destroyTimer >= 3)
		Destroy();
}

void AMyPowerUp::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (Cast<AMyBullet>(OtherActor) != NULL) {
			TArray<UMaterialInterface*> mats;
			MyComp->GetUsedMaterials(mats);

			if (mats[0]->GetName() == "Fire_Rate")
				player->UnlimitedFireRate();
			else
				player->ShotgunMode();
			GetWorld()->SpawnActor<AActor>(effect, GetActorLocation(), GetActorRotation(), FActorSpawnParameters());
		}
		Destroy();
	}
}