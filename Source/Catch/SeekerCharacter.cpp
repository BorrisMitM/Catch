// Fill out your copyright notice in the Description page of Project Settings.


#include "SeekerCharacter.h"

#include "HiderCharacter.h"
#include "Components/CapsuleComponent.h"

void ASeekerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASeekerCharacter::BeginOverlap);
}


void ASeekerCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	if(!IsLocallyControlled()) return;
	
	AHiderCharacter* HiderCharacter = Cast<AHiderCharacter>(OtherActor);
	if(HiderCharacter == nullptr) return;
	HiderCharacter->Catch();
}