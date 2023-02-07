// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RootPestControlGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ROOTPESTCONTROL_API ARootPestControlGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled);
	
};
