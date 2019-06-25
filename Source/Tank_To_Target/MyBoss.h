// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTank.h"
#include "MyBossBullet.h"
#include "MyBullet.h"
#include "GameFramework/Actor.h"
#include "MyBoss.generated.h"

UCLASS()
class TANK_TO_TARGET_API AMyBoss : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeDirection();
	FVector targetPosition;
	UPROPERTY(EditAnywhere)
		FVector minBounds;
	UPROPERTY(EditAnywhere)
		FVector maxBounds;
	UPROPERTY(EditAnywhere)
		float baseDirectionTime;
	UPROPERTY(EditAnywhere)
		float enragedDirectionTime;
	float directionTimer;

	bool isEnraged;
	UPROPERTY(EditAnywhere)
		UStaticMesh* enragedMesh;

	UPROPERTY(EditAnywhere)
		float baseSpeed;
	UPROPERTY(EditAnywhere)
		float enragedSpeed;

	UPROPERTY(EditAnywhere)
		int maxLife;
	int life;

	UPROPERTY(BlueprintReadWrite)
		TArray<UChildActorComponent*> allPHs;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AMyBossBullet> bullet;
	UPROPERTY(EditAnywhere)
		float baseShootTime;
	UPROPERTY(EditAnywhere)
		float enragedShootTime;
	float shootTimer;

	void Move(float speed, float deltaTime);
	void Shoot();
	void Die();
	void Enrage();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* MyComp;
};
