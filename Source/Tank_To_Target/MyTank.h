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


	void MoveX(float val);
	void MoveY(float val);
	void RotateX(float val);
	void RotateY(float val);
	void Shoot();

	FVector currentVelocity;
	bool isMovingX;
	bool isMovingY;

	UPROPERTY(EditAnywhere)
		float speed;
	UPROPERTY(EditAnywhere)
		float rotationSpeed;

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

	int armor;
	float timeRemaining;
};
