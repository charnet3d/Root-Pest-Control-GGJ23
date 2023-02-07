// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterAIController.h"


#include "FighterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AFighterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AFighterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool AFighterAIController::IsDead() const
{
	AFighterCharacter* ControlledCharacter = Cast<AFighterCharacter>(GetPawn());
	if (ControlledCharacter)
		return ControlledCharacter->IsDead();
    
	return true;
}
