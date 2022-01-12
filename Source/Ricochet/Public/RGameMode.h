// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RICOCHET_API ARGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ARGameMode();

	UFUNCTION(BlueprintCallable)
	void PlayerReadyUp();

	UFUNCTION(BlueprintCallable)
	void PlayerUnready();

	void RespawnPlayer(APlayerController* PC);

protected:
	int PlayersReady;

	void StartGame();

	void UpdateReadyPlayerCount(); // called to update player ready count through the network on GameState

	void UpdatePlayersInMatch();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;
};
