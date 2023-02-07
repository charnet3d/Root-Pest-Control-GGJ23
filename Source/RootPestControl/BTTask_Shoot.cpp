// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"


#include "AIController.h"
#include "FighterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* OwnController = OwnerComp.GetAIOwner();
	if (!OwnController)
	{
		return EBTNodeResult::Failed;
	}
	
	AFighterCharacter* OwnCharacter = Cast<AFighterCharacter>(OwnController->GetPawn());
	if (!OwnCharacter)
	{
		return EBTNodeResult::Failed;
	}
	
	OwnCharacter->Shoot();
	
	return EBTNodeResult::Succeeded;
}
