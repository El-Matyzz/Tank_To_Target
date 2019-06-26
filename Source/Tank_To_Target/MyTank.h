// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "MyBullet.h"
#include "GameFramework/Pawn.h"
#include "MyTank.generated.h"

UCLASS()
class TANK_TO_TARGET_API AMyTank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
		float bossBarFill;

	void MoveX(float val);
	void MoveY(float val);
	void RotateX(float val);
	void RotateY(float val);
	void Shoot();

	void SetGamePaused(bool isPaused);

	FVector currentVelocity;
	bool isMovingX;
	bool isMovingY;

	UPROPERTY(EditAnywhere)
		float speed;
	UPROPERTY(EditAnywhere)
		float rotationSpeed;

	UPROPERTY(EditAnywhere)
		float timeLV1;
	UPROPERTY(EditAnywhere)
		float targetsLV1;
	UPROPERTY(EditAnywhere)
		float timeLV2;
	UPROPERTY(EditAnywhere)
		float targetsLV2;

	UPROPERTY(BlueprintReadWrite)
		UChildActorComponent* rotor;
	UPROPERTY(BlueprintReadWrite)
		UChildActorComponent* upperBody;

	UPROPERTY(BlueprintReadWrite)
		UChildActorComponent* PH;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AMyBullet> bullet;

	int destroyedTargets;
	int totalTargets;

	UPROPERTY(BlueprintReadOnly)
		int remainingTargets;

	int armor;
	UPROPERTY(EditAnywhere)
		int maxArmor;
	UPROPERTY(BlueprintReadOnly)
		float armorBarFill;
	UPROPERTY(BlueprintReadOnly)
		float timeRemaining;
	
	bool unlimitedFireRate;
	UPROPERTY(EditAnywhere)
		float fireDelay;
	float fireTimer;
	bool shotgunMode;
	UPROPERTY(EditAnywhere)
		float shotgunSpread;
	UPROPERTY(EditAnywhere)
		int shotgunPellets;
	UPROPERTY(EditAnywhere)
		float powerUpTime;
	float powerUpTimer;

	void UnlimitedFireRate();
	void ShotgunMode();

	void Lose();
	void Win();
	void Continue();

	UPROPERTY(BlueprintReadOnly)
	bool won;
};
