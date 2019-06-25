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
	SetActorLocation(GetActorLocation() + GetActorRightVector() * speed * DeltaTime, true);

	destroyTimer += DeltaTime;
	if (destroyTimer >= 3)
		Destroy();
}

void AMyBullet::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		AMyBoss* boss = Cast<AMyBoss>(OtherActor);
		if (boss != NULL)
		{
			AActor* playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
			AMyTank* player = Cast<AMyTank>(playerActor);
			boss->life--;
			player->bossBarFill = boss->life / boss->maxLife;
			if (boss->life <= boss->maxLife / 2)
				if (boss->life <= 0)
					boss->Die();
				else
					if (!boss->isEnraged)
						boss->Enrage();
		}
		else if (Cast<AMyBossBullet>(OtherActor))
			Destroy(OtherActor);
		GetWorld()->SpawnActor<AActor>(explosion, GetActorLocation(), GetActorRotation(), FActorSpawnParameters());
		Destroy();
	}
}