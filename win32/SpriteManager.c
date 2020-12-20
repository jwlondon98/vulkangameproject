#include "SpriteManager.h"


void InitSpriteManager()
{
	gf3d_sprite_manager_init(10, gf3d_swapchain_get_chain_length(), gf3d_vgraphics_get_default_logical_device());

	mainMenu.sprite = gf3d_sprite_load("images/UI/mm.png", -1, -1, 0);
	mainMenu.pos = vector2d(590, 390);
	mainMenu.scale = vector2d(2.2, 2.2);

	pistolIcon.sprite = gf3d_sprite_load("images/UI/pistol.png", -1, -1, 0);
	pistolIcon.pos = vector2d(-410, 390);
	pistolIcon.scale = vector2d(.3, .3);

	machinegunIcon.sprite = gf3d_sprite_load("images/UI/machinegun.png", -1, -1, 0);
	machinegunIcon.pos = vector2d(-220, 490);
	machinegunIcon.scale = vector2d(.6, .6);

	currentGunIcon = pistolIcon;

	showGunIcons = 0;
	showMainMenu = 1;
}

void RenderSprites(Uint32 frame, Uint32 bufferFrame, VkCommandBuffer buffer)
{
	gameState = GetGameState();

	if (gameState == PLAYING)
	{
		showMainMenu = 0;
		showGunIcons = 1;
	}

	if (showMainMenu == 1)
	{
		gf3d_sprite_draw(
			mainMenu.sprite, mainMenu.pos, mainMenu.scale,
			frame, bufferFrame, buffer);
	}

	if (showGunIcons == 1)
	{
		gf3d_sprite_draw(
			currentGunIcon.sprite, currentGunIcon.pos, currentGunIcon.scale,
			frame, bufferFrame, buffer);
	}
}

void ChangeGunSprite(int gunNum)
{
	switch (gunNum)
	{
		case 1:
			currentGunIcon = pistolIcon;
			break;
		case 2:
			currentGunIcon = machinegunIcon;
			break;
	}
}

void CloseMainMenu()
{
	showMainMenu = 0;
	showGunIcons = 1;
}