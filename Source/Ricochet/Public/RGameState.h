// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RGameState.generated.h"

/**
 * 
 */
UCLASS()
class RICOCHET_API ARGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated, BlueprintReadOnly)
	int NumPlayersReady;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int PlayersInMatch;

	UPROPERTY(ReplicatedUsing = OnRep_MatchReady, BlueprintReadOnly)
	bool IsMatchReady;

	// Need to manually call for host/listen server
	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_MatchReady();
};
