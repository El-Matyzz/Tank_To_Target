// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TANK_TO_TARGET_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isWalking;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isRunning;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isDead;
};
