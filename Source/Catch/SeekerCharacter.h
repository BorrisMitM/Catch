// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CatchCharacter.h"
#include "SeekerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CATCH_API ASeekerCharacter : public ACatchCharacter
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);
	virtual void BeginPlay() override;
};
