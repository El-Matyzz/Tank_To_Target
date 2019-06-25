// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBossBullet.h"

// Sets default values
AMyBossBullet::AMyBossBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMComp"));
	MyComp->SetSimulatePhysics(true);
	MyComp->SetEnableGravity(false);
	MyComp->SetNotifyRigidBodyCollision(true);
	MyComp->OnComponentHit.AddDynamic(this, &AMyBossBullet::OnCompHit);
}

// Called when the game starts or when spawned
void AMyBossBullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyBossBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * DeltaTime, true);
}

void AMyBossBullet::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		AMyTank* player = Cast<AMyTank>(OtherActor);
		if (player != NULL)
			player->armor--;
		GetWorld()->SpawnActor<AActor>(fire, GetActorLocation(), GetActorRotation(), FActorSpawnParameters());
		Destroy();
	}
}