// Fill out your copyright notice in the Description page of Project Settings.


#include "HiderCharacter.h"

#include "CatchPlayerController.h"

void AHiderCharacter::Catch()
{
	ACatchPlayerController* PlayerController = Cast<ACatchPlayerController>(GetController());
	if(PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hider spawned on Seeker, not caught in this instance"));
		return;
	}
	PlayerController->Catch();
}
