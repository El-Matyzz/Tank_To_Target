// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyTank.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANK_TO_TARGET_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	AMyTank* player;
	
	UPROPERTY(BlueprintReadOnly)
		float timeRemaining;
	UPROPERTY(BlueprintReadOnly)
		float armorBarFill;
	UPROPERTY(BlueprintReadOnly)
		float bossBarFill;

	virtual void NativeTick(const FGeometry& geometry, float deltaTime) override;
	virtual void NativeConstruct() override;
};
