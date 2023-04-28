// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchPlayerController.h"

#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"

ACatchPlayerController::ACatchPlayerController(const FObjectInitializer& ObjectInitializer)
{
	bReplicates = true;
}

void ACatchPlayerController::Catch()
{
	if(IsSeeker) return;
	IsSeeker = true;
	ReplacePawn(SeekerPawn);
}

void ACatchPlayerController::ReplacePawn(TSubclassOf<APawn> NewPawnClass)
{
	APawn* CurrentPawn = GetPawn();
	APawn* SpawnedNewPawn = GetWorld()->SpawnActor<APawn>(NewPawnClass, CurrentPawn->GetActorTransform());
	SetPawn(SpawnedNewPawn);
	CurrentPawn->Destroy();
}
