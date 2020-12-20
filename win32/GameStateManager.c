#include "GameStateManager.h"

void InitGameStateManager()
{
	gameState = MAINMENU;
}

GameState GetGameState()
{
	return gameState;
}

void SetGameState(GameState gState)
{
	gameState = gState;

	if (gameState == PLAYING)
	{
		//showMainMenu = 0;
		//showGunIcons = 1;
	}
}