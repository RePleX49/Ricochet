// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RICOCHET_API ARPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UFUNCTION(Client, Unreliable)
	void StartRespawnTimer();

protected:

	UFUNCTION(Server, WithValidation, Reliable)
	void ServerRequestRespawn();

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle TimerHandle_Respawn;
	
};
