#ifndef __GAMESTATEMANAGER_H__
#define __GAMESTATEMANAGER_H__

typedef enum
{
	LevelEdit, Game
}GameMode;

typedef enum
{
	MAINMENU, PLAYING, PAUSED
}GameState;

GameMode gameMode;
GameState gameState;

void InitGameStateManager();

GameState GetGameState();

void SetGameState(GameState gState);

#endif