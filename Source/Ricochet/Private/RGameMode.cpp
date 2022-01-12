// Fill out your copyright notice in the Description page of Project Settings.


#include "RGameState.h"
#include "RGameMode.h"

ARGameMode::ARGameMode()
{
	 
}

void ARGameMode::PlayerReadyUp()
{
	PlayersReady++;

	UpdateReadyPlayerCount();

	if (PlayersReady >= GetNumPlayers())
	{
		//TODO update match ready state in GameState
		ARGameState* MyGameState = Cast<ARGameState>(GameState);

		if (MyGameState)
		{
			MyGameState->IsMatchReady = true;
			MyGameState->OnRep_MatchReady();
		}

		StartGame();
	}
}

void ARGameMode::PlayerUnready()
{
	PlayersReady--;

	//TODO may need to cancel match start timer
	UpdateReadyPlayerCount();
}

void ARGameMode::RespawnPlayer(APlayerController* PC)
{
	if (PC && PC->GetPawn() == nullptr)
	{
		RestartPlayer(PC);
		UE_LOG(LogTemp, Warning, TEXT("Restarting Player"));
	}
}

void ARGameMode::UpdateReadyPlayerCount()
{
	ARGameState* MyGameState = Cast<ARGameState>(GameState);

	if (MyGameState)
	{
		MyGameState->NumPlayersReady = PlayersReady;
	}
}

void ARGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UpdatePlayersInMatch();
}

void ARGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	UpdatePlayersInMatch();
}

void ARGameMode::UpdatePlayersInMatch()
{
	ARGameState* MyGameState = Cast<ARGameState>(GameState);

	if (MyGameState)
	{
		MyGameState->PlayersInMatch = GetNumPlayers();
	}
}

void ARGameMode::StartGame()
{

}

