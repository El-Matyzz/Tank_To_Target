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
	AActor* playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	player = Cast<AMyTank>(playerActor);
	SetActorRotation((player->GetActorLocation() - GetActorLocation()).Rotation());
}

// Called every frame
void AMyBossBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + GetActorRightVector() * speed * DeltaTime, true);
}

void AMyBossBullet::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (Cast<AMyTank>(OtherActor))
			player->armor--;
		GetWorld()->SpawnActor<AActor>(explosion, GetActorLocation(), GetActorRotation(), FActorSpawnParameters());
		Destroy();
	}
}