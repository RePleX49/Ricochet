// Fill out your copyright notice in the Description page of Project Settings.


#include "RGameState.h"
#include "Net/UnrealNetwork.h"

void ARGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARGameState, NumPlayersReady);
	DOREPLIFETIME(ARGameState, PlayersInMatch);
	DOREPLIFETIME(ARGameState, IsMatchReady);
}