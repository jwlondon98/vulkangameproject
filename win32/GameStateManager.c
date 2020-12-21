#include "GameStateManager.h"

void InitGameStateManager()
{
	gameState = MAINMENU;
	gameMode = Game;
}

GameState GetGameState()
{
	return gameState;
}

GameMode GetGameMode()
{
	return gameMode;
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

void SwitchGameMode()
{
	slog("game mode switched");

	if (gameMode == Game)
		gameMode = LevelEdit;
	else if (gameMode == LevelEdit)
		gameMode = Game;
}