// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchCharacterMovementComponent.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"


void UCatchCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	if (!CharacterOwner)
	{
		return;
	}

	const bool bWasPressingJump = CharacterOwner->bPressedJump;

	CharacterOwner->bPressedJump = ((Flags & FSavedMove_Character::FLAG_JumpPressed) != 0);
	bWantsToCrouch = ((Flags & FSavedMove_Character::FLAG_WantsToCrouch) != 0);

	// Detect change in jump press on the server
	if (CharacterOwner->GetLocalRole() == ROLE_Authority) 
	{
		const bool bIsPressingJump = CharacterOwner->bPressedJump;
		if (bIsPressingJump && !bWasPressingJump)
		{
			CharacterOwner->Jump();
		}
		else if (!bIsPressingJump && bWasPressingJump)
		{
			CharacterOwner->StopJumping();
		}
	}
}

void UCatchCharacterMovementComponent::EndDash()
{
	MovementMode = MOVE_Falling;
}

void UCatchCharacterMovementComponent::PhysFlying(float deltaTime, int32 Iterations)
{
	if (deltaTime < MIN_TICK_TIME)
	{
		return;
	}

	RestorePreAdditiveRootMotionVelocity();

	// if( !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity() )
	// {
	// 	if( bCheatFlying && Acceleration.IsZero() )
	// 	{
	// 		Velocity = FVector::ZeroVector;
	// 	}
	// 	const float Friction = 0.5f;// * GetPhysicsVolume()->FluidFriction;
	// 	CalcVelocity(deltaTime, Friction, true, GetMaxBrakingDeceleration());
	// }
	//
	// ApplyRootMotionToVelocity(deltaTime);

	Iterations++;
	bJustTeleported = false;

	FVector OldLocation = UpdatedComponent->GetComponentLocation();
	FVector MoveDir = GetOwner()->GetActorForwardVector();

	const float VerticalInput = UKismetMathLibrary::InverseTransformDirection(GetOwner()->GetTransform(), GetLastInputVector()).X;
	UpDash = FMath::Lerp(UpDash, -VerticalInput, DashVerticalSmoothing);
	UE_LOG(LogTemp, Warning, TEXT("%f"), UpDash);
	MoveDir.Z = UpDash;
	Velocity = MoveDir * DashVelocity;
	const FVector Adjusted = Velocity * deltaTime; //Velocity * deltaTime;
	FHitResult Hit(1.f);
	SafeMoveUpdatedComponent(Adjusted, UpdatedComponent->GetComponentQuat(), true, Hit);

	if (Hit.Time < 1.f)
	{
		const FVector GravDir = FVector(0.f, 0.f, -1.f);
		const FVector VelDir = Velocity.GetSafeNormal();
		const float UpDown = GravDir | VelDir;

		bool bSteppedUp = false;
		if ((FMath::Abs(Hit.ImpactNormal.Z) < 0.2f) && (UpDown < 0.5f) && (UpDown > -0.2f) && CanStepUp(Hit))
		{
			float stepZ = UpdatedComponent->GetComponentLocation().Z;
			bSteppedUp = StepUp(GravDir, Adjusted * (1.f - Hit.Time), Hit);
			if (bSteppedUp)
			{
				OldLocation.Z = UpdatedComponent->GetComponentLocation().Z + (OldLocation.Z - stepZ);
			}
		}

		if (!bSteppedUp)
		{
			//adjust and try again
			HandleImpact(Hit, deltaTime, Adjusted);
			SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);
		}
	}

	if (!bJustTeleported && !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
	{
		Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / deltaTime;
	}
}


void UCatchCharacterMovementComponent::DoDash()
{
	if(!IsFalling()) return;
	MovementMode = MOVE_Flying;
	UpDash = 0;
	FTimerHandle DashTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DashTimerHandle, this, &UCatchCharacterMovementComponent::EndDash, DashDuration);
}
