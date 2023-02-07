// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FighterAIController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class ROOTPESTCONTROL_API AFighterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick( float DeltaSeconds ) override;

	bool IsDead() const;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;
};
