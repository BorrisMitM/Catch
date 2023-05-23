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
	UPROPERTY(EditAnywhere, Category="Dash", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DashVerticalSmoothing = 0.9;

	//Value between -1 and 1, reflects the amount of vertical direction in the dash
	UPROPERTY(VisibleAnywhere, Category="Dash")
	float UpDash = 0;
};
