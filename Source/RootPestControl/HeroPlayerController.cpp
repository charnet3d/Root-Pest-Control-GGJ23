// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroPlayerController.h"

#include "Blueprint/UserWidget.h"

void AHeroPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDClass)
		HUD = CreateWidget(this, HUDClass);
	
	if (HUD)
		HUD->AddToViewport();
}

void AHeroPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	if (HUD)
		HUD->RemoveFromParent();
	
	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen != nullptr)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();
		}
	}
	
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
