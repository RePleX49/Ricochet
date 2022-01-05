// Fill out your copyright notice in the Description page of Project Settings.


#include "RHealthComponent.h"
#include "Net/UnrealNetwork.h"

URHealthComponent::URHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxHealth = 100;
	bIsDead = false;

	SetIsReplicatedByDefault(true);
}

// Called when the game starts
void URHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority)
	{
		AActor* MyOwner = GetOwner();
		if (MyOwner)
		{
			MyOwner->OnTakeAnyDamage.AddDynamic(this, &URHealthComponent::HandleTakeAnyDamage);
		}
	}
	
	Health = MaxHealth;
}

void URHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, 
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || bIsDead)
	{
		return;
	}

	// TODO check friendly fire

	Health = FMath::Clamp(Health - (int)Damage, 0, MaxHealth);

	bIsDead = Health <= 0;

	// TODO is player is dead tell Server to respawn them
}

void URHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URHealthComponent, Health);
}
