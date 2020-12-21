#ifndef __GAMESTATEMANAGER_H__
#define __GAMESTATEMANAGER_H__

#include "simple_logger.h"

typedef enum
{
	LevelEdit, Game
}GameMode;

typedef enum
{
	MAINMENU, PLAYING, PAUSED, GAMEOVER
}GameState;

GameMode gameMode;
GameState gameState;

void InitGameStateManager();

GameState GetGameState();
GameMode GetGameMode();

void SetGameState(GameState gState);

void SwitchGameMode();

#endif