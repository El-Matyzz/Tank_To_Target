// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTank.h"
#include "MyPowerUp.h"
#include "GameFramework/Actor.h"
#include "MyTarget.generated.h"

UCLASS()
class TANK_TO_TARGET_API AMyTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AMyTank* player;

	UPROPERTY(EditAnywhere)
		UMaterial* mat1;
	UPROPERTY(EditAnywhere)
		UMaterial* mat2;
	UPROPERTY(EditAnywhere)
		UMaterial* mat3;
	UPROPERTY(EditAnywhere)
		UMaterial* mat4;
	int targetType;

	UPROPERTY(BlueprintReadWrite)
		UChildActorComponent* PH1;
	UPROPERTY(BlueprintReadWrite)
		UChildActorComponent* PH2;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AMyPowerUp> fireRate;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AMyPowerUp> shotgun;

	UPROPERTY(EditAnywhere)
		float maxScale;

	float disappearTimer;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* MyComp;

	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void SpawnPowerUps();
};
