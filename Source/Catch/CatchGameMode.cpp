// Copyright Epic Games, Inc. All Rights Reserved.

#include "CatchGameMode.h"
#include "CatchCharacter.h"
#include "CatchPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ACatchGameMode::ACatchGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

AActor* ACatchGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if(!IncomingName.IsEmpty()) return Super::FindPlayerStart_Implementation(Player, IncomingName);

	ACatchPlayerController* PlayerController = Cast<ACatchPlayerController>(Player);
	FString PlayerStartTag = PlayerController->GetIsSeeker() ? FString("Seeker") : FString("Hider");
	return Super::FindPlayerStart_Implementation(Player, PlayerStartTag);
}

APlayerController* ACatchGameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	ACatchPlayerController* PlayerController = Cast<ACatchPlayerController>(Super::SpawnPlayerController(InRemoteRole, Options));
	if(Seekers.IsEmpty())
	{
		PlayerController->SetIsSeeker(true);
		Seekers.Add(PlayerController);
	}
	return PlayerController;
}


UClass* ACatchGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	ACatchPlayerController* PlayerController = Cast<ACatchPlayerController>(InController);
	if (PlayerController)
	{
		if(PlayerController->GetIsSeeker()) return SeekerPawnClass;
		else return HiderPawnClass;
	}
 
	/* If we don't get the right Controller, use the Default Pawn */
	return DefaultPawnClass;
}
