// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CatchPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CATCH_API ACatchPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ACatchPlayerController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> SeekerPawn;
	void Catch();
	void ReplacePawn(TSubclassOf<APawn> NewPawnClass);
private:
	bool IsSeeker = false;
public:
	void SetIsSeeker(bool Value){IsSeeker = Value;}
	bool GetIsSeeker() const {return IsSeeker;}
};
