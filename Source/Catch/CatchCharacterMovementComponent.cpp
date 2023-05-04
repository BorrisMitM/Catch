// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchCharacterMovementComponent.h"

#include "GameFramework/Character.h"

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
