// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetMapName() == "UEDPIE_0_Level_3")
		hud = CreateWidget<UUserWidget>(this, hudComponentLevel3);
	else if (GetWorld()->GetMapName() == "UEDPIE_0_Level_1" || GetWorld()->GetMapName() == "UEDPIE_0_Level_2")
		hud = CreateWidget<UUserWidget>(this, hudComponent);
	if (hud)
		hud->AddToViewport();
}