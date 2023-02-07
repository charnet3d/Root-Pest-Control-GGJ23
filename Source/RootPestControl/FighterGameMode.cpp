// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterGameMode.h"

#include "EngineUtils.h"
#include "FighterAIController.h"

void AFighterGameMode::PawnKilled(APawn* KilledPawn)
{
	Super::PawnKilled(KilledPawn);

	if (!KilledPawn)
		return;

	// Was the killed pawn the player?
	APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());
	if (PlayerController)
		PlayerController->GameHasEnded(nullptr, false);

	// Check for win condition, are all enemies dead ?
	for (AFighterAIController* Controller : TActorRange<AFighterAIController>(GetWorld()))
	{
		if (!Controller->IsDead())
			return;
	}
    
	// All AI is dead, game is won
	EndGame(true);
}

void AFighterGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bWon = (bIsPlayerWinner == Controller->IsPlayerController());
		Controller->GameHasEnded(Controller->GetPawn(), bWon);
	}
}

