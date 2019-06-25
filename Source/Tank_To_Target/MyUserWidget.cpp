// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"

void UMyUserWidget::NativeConstruct()
{
	AActor* playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	player = Cast<AMyTank>(playerActor);
}

void UMyUserWidget::NativeTick(const FGeometry & geometry, float deltaTime)
{
	timeRemaining = player->timeRemaining;
	armorBarFill = player->armorBarFill;
	bossBarFill = player->bossBarFill;
}