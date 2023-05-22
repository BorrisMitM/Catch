// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CatchCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class CATCH_API UCatchCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

protected:
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	void EndDash();
	virtual void PhysFlying(float deltaTime, int32 Iterations) override;
public:
	void DoDash();
	UPROPERTY(EditAnywhere, Category="Dash")
	float DashDuration = 0.5;
	UPROPERTY(EditAnywhere, Category="Dash")
	float DashVelocity = 1500;
};
