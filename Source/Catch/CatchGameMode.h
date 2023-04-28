// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CatchGameMode.generated.h"

UCLASS(minimalapi)
class ACatchGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
public:
	ACatchGameMode();
	//virtual bool ReadyToStartMatch_Implementation() override;
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName = TEXT("")) override;
	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;
	
private:
	UPROPERTY()
	TArray<TObjectPtr<APlayerController>> Seekers;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerPawns")
	TSubclassOf<APawn> HiderPawnClass;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerPawns")
	TSubclassOf<APawn> SeekerPawnClass;


};



