#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__

#include "gf3d_vgraphics.h"
#include "gf3d_swapchain.h"

#include "GameStateManager.h"

typedef struct SpriteIcon_S
{
	Sprite *sprite;
	Vector2D pos;
	Vector2D scale;
} SpriteIcon;

GameState gameState;

int showMainMenu;
SpriteIcon mainMenu;

int showGunIcons;
SpriteIcon pistolIcon;
SpriteIcon machinegunIcon;
SpriteIcon currentGunIcon;

void InitSpriteManager();
void RenderSprites(Uint32 frame, Uint32 bufferFrame, VkCommandBuffer buffer);

void ChangeGunSprite(int gunNum);

void CloseMainMenu();

#endif