// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
/*
void UMyUserWidget::NativeConstruct()
{
	AActor* playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	player = Cast<AMyTank>(playerActor);
}

void UMyUserWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	AMyTank* doge = Cast<AMyTank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	timeRemaining = FString::SanitizeFloat(floor(doge->timeRemaining * 100) / 100);
	currentTime = FString::SanitizeFloat(floor(GetWorld()->TimeSeconds * 100) / 100);
	targetsRemaining = "AAADSDA";
	armorBarFill = doge->armorBarFill;
	bossBarFill = doge->bossBarFill;
	won = doge->won;
	
	textTimer += InDeltaTime;
	if (textTimer >= 1) {
		startText = !startText;
		textTimer = 0;
	}
}

void UMyUserWidget::LoadLevel(FName levelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), levelName);
}

void UMyUserWidget::Quit()
{
	FGenericPlatformMisc::RequestExit(false);
}
*/
