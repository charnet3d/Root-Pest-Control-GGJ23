// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RootPestControlGameModeBase.h"
#include "FighterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ROOTPESTCONTROL_API AFighterGameMode : public ARootPestControlGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

	void EndGame(bool bIsPlayerWinner);
	
};
