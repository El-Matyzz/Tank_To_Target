// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTank.h"
#include "GameFramework/Actor.h"
#include "MyPowerUp.generated.h"

UCLASS()
class TANK_TO_TARGET_API AMyPowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AMyTank* player;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* MyComp;

	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
		float force;
	float destroyTimer;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> effect;

	TArray<UMaterialInterface*> mats;
};
