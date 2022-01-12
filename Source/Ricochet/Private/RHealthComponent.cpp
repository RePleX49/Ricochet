// Fill out your copyright notice in the Description page of Project Settings.


#include "RHealthComponent.h"
#include "Net/UnrealNetwork.h"

URHealthComponent::URHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxHealth = 100.0f;
	bIsDead = false;

	SetIsReplicatedByDefault(true);
}

// Called when the game starts
void URHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Only allow the owning player to handle damage on this component
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

void URHealthComponent::OnRep_Health(float OldHealth)
{
	float Damage = Health - OldHealth;

	// Allows us to tell the client to do damage handling
	OnHealthChanged.Broadcast(this, Health, Damage, nullptr, nullptr, nullptr);
}

void URHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, 
	class AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Took Damage"));
	if (Damage <= 0.0f || bIsDead)
	{
		return;
	}

	// TODO check friendly fire

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	bIsDead = Health <= 0;

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);

	// TODO is player is dead tell Server to respawn them
}

void URHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URHealthComponent, Health);
}
