// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBullet.h"


// Sets default values
AMyBullet::AMyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMComp"));
	MyComp->SetSimulatePhysics(true);
	MyComp->SetEnableGravity(false);
	MyComp->SetNotifyRigidBodyCollision(true);
	MyComp->OnComponentHit.AddDynamic(this, &AMyBullet::OnCompHit);
}

// Called when the game starts or when spawned
void AMyBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + GetActorRightVector() * 10000 * DeltaTime, true);
}

void AMyBullet::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Red, "ALLAHU AKBAR");
		Destroy();
	}
}