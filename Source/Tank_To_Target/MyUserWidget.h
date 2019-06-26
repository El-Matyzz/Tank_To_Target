// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
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
	/*
	AMyTank* player;
	
	UPROPERTY(BlueprintReadOnly)
		FString timeRemaining;
	UPROPERTY(BlueprintReadOnly)
		FString targetsRemaining;
	UPROPERTY(BlueprintReadOnly)
		FString currentTime;
	UPROPERTY(BlueprintReadOnly)
		float armorBarFill;
	UPROPERTY(BlueprintReadOnly)
		float bossBarFill;
	UPROPERTY(BlueprintReadOnly)
		bool startText;
	float textTimer;
	UPROPERTY(BlueprintReadOnly)
		bool won;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void LoadLevel(FName levelName);
	UFUNCTION(BlueprintCallable)
		void Quit();
	*/
};
