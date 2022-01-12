// Fill out your copyright notice in the Description page of Project Settings.


#include "Ricochet/Public/RGameMode.h"
#include "RPlayerController.h"

void ARPlayerController::StartRespawnTimer()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Respawn, this, &ARPlayerController::ServerRequestRespawn, 5.0f, false);
}

void ARPlayerController::ServerRequestRespawn_Implementation()
{
	ARGameMode* GM = Cast<ARGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->RespawnPlayer(this);
		UE_LOG(LogTemp, Warning, TEXT("Called GameMode Respawn Player"));
	}
}

bool ARPlayerController::ServerRequestRespawn_Validate()
{
	return true;
}
