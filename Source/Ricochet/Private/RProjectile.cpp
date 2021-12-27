// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectile.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Gameframework/ProjectileMovementComponent.h"

// Sets default values
ARProjectile::ARProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereCollider->OnComponentHit.AddDynamic(this, &ARProjectile::OnCompHit);
	SphereCollider->SetSphereRadius(5.0f);
	SphereCollider->CanCharacterStepUpOn = ECB_No;
	
	RootComponent = SphereCollider;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	DamageStages = 5;
	CurrentDamageStage = 0;

	ExplosionDamage = 35.0f;
	ExplosionInnerRadius = 50.0f;
	ExplosionOuterRadius = 100.0f;
	ExplosionDamageFalloff = 2.0f;
}

// Called when the game starts or when spawned
void ARProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SpeedRange = (ProjectileMovement->MaxSpeed - ProjectileMovement->InitialSpeed);
}

void ARProjectile::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
	if (CurrentDamageStage >= DamageStages - 1)
	{
		if (ExplosionFX)
		{
			
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionFX, this->GetActorTransform());			
		}

		TArray<AActor*> IgnoredActors;
		UGameplayStatics::ApplyRadialDamageWithFalloff(this, ExplosionDamage, ExplosionDamage / 2, this->GetActorLocation(),
			ExplosionInnerRadius, ExplosionOuterRadius, ExplosionDamageFalloff, ExplosionDamageType, IgnoredActors, nullptr, nullptr);

		Destroy();
		return;
	}

	CurrentDamageStage++;
	float NewSpeed = ProjectileMovement->InitialSpeed + (SpeedRange * (CurrentDamageStage / DamageStages));

	ProjectileMovement->Velocity.Normalize();
	ProjectileMovement->Velocity *= NewSpeed;
}

// Called every frame
void ARProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

