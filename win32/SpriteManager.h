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

// menus
int showMainMenu;
int showDeathMenu;
int showGameIcons;
SpriteIcon mainMenu;
SpriteIcon deathMenu;

// gun icons
SpriteIcon pistolIcon;
SpriteIcon machinegunIcon;
SpriteIcon currentGunIcon;

// health bar
int health;
SpriteIcon healthBar1;
SpriteIcon healthBar2;
SpriteIcon healthBar3;
SpriteIcon healthBar4;
SpriteIcon healthBar5;
SpriteIcon healthBar6;
SpriteIcon healthBar7;
SpriteIcon healthBar8;
SpriteIcon healthBar9;
SpriteIcon healthBar10;


void InitSpriteManager();
void RenderSprites(Uint32 frame, Uint32 bufferFrame, VkCommandBuffer buffer);

void ChangeGunSprite(int gunNum);

void CloseMainMenu();

#endif