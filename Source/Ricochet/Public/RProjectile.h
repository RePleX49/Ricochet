// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RProjectile.generated.h"

UCLASS()
class RICOCHET_API ARProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleDefaultsOnly, Category = "Colliders")
	class USphereComponent* SphereCollider;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	class UParticleSystem* ExplosionFX;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	int DamageStages;

	int CurrentDamageStage;
	float SpeedRange;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float BaseHitDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion Properties")
	float ExplosionDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion Properties")
	float ExplosionInnerRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion Properties")
	float ExplosionOuterRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion Properties")
	float ExplosionDamageFalloff;

	TSubclassOf<UDamageType> ExplosionDamageType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
