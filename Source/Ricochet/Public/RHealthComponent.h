// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RICOCHET_API URHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Properties")
	int Health;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	int MaxHealth;

	bool bIsDead;

public:

	int GetHealth() const { return Health; };
};
