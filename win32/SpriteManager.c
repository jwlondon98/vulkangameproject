#include "SpriteManager.h"


void InitSpriteManager()
{
	gf3d_sprite_manager_init(50, gf3d_swapchain_get_chain_length(), gf3d_vgraphics_get_default_logical_device());

	// menus
	mainMenu.sprite = gf3d_sprite_load("images/UI/mm.png", -1, -1, 0);
	mainMenu.pos = vector2d(590, 390);
	mainMenu.scale = vector2d(2.2, 2.2);
	deathMenu.sprite = gf3d_sprite_load("images/UI/deathscreen.png", -1, -1, 0);
	deathMenu.pos = vector2d(650, 390);
	deathMenu.scale = vector2d(2.2, 2.2);

	// gun icons
	pistolIcon.sprite = gf3d_sprite_load("images/UI/pistol.png", -1, -1, 0);
	pistolIcon.pos = vector2d(-410, 390);
	pistolIcon.scale = vector2d(.3, .3);
	machinegunIcon.sprite = gf3d_sprite_load("images/UI/machinegun.png", -1, -1, 0);
	machinegunIcon.pos = vector2d(-220, 490);
	machinegunIcon.scale = vector2d(.6, .6);
	currentGunIcon = pistolIcon;

	// health bars
	healthBar10.sprite = gf3d_sprite_load("images/UI/healthbar10.png", -1, -1, 0);
	healthBar10.pos = vector2d(180, 575);
	healthBar10.scale = vector2d(1, .8);
	healthBar9.sprite = gf3d_sprite_load("images/UI/healthbar9.png", -1, -1, 0);
	healthBar9.pos = vector2d(180, 575);
	healthBar9.scale = vector2d(1, .8);
	healthBar8.sprite = gf3d_sprite_load("images/UI/healthbar8.png", -1, -1, 0);
	healthBar8.pos = vector2d(180, 575);
	healthBar8.scale = vector2d(1, .8);
	healthBar7.sprite = gf3d_sprite_load("images/UI/healthbar7.png", -1, -1, 0);
	healthBar7.pos = vector2d(180, 575);
	healthBar7.scale = vector2d(1, .8);
	healthBar6.sprite = gf3d_sprite_load("images/UI/healthbar6.png", -1, -1, 0);
	healthBar6.pos = vector2d(180, 575);
	healthBar6.scale = vector2d(1, .8);
	healthBar5.sprite = gf3d_sprite_load("images/UI/healthbar5.png", -1, -1, 0);
	healthBar5.pos = vector2d(180, 575);
	healthBar5.scale = vector2d(1, .8);
	healthBar4.sprite = gf3d_sprite_load("images/UI/healthbar4.png", -1, -1, 0);
	healthBar4.pos = vector2d(180, 575);
	healthBar4.scale = vector2d(1, .8);
	healthBar3.sprite = gf3d_sprite_load("images/UI/healthbar3.png", -1, -1, 0);
	healthBar3.pos = vector2d(180, 575);
	healthBar3.scale = vector2d(1, .8);
	healthBar2.sprite = gf3d_sprite_load("images/UI/healthbar2.png", -1, -1, 0);
	healthBar2.pos = vector2d(180, 575);
	healthBar2.scale = vector2d(1, .8);
	healthBar1.sprite = gf3d_sprite_load("images/UI/healthbar1.png", -1, -1, 0);
	healthBar1.pos = vector2d(180, 575);
	healthBar1.scale = vector2d(1, .8);

	showGameIcons = 0;
	showMainMenu = 1;
	showDeathMenu = 1;

	health = 10;
}

void RenderSprites(Uint32 frame, Uint32 bufferFrame, VkCommandBuffer buffer)
{
	gameState = GetGameState();

	if (gameState == PLAYING)
	{
		showMainMenu = 0;
		showGameIcons = 1;
	}

	if (showMainMenu == 1)
	{
		gf3d_sprite_draw(
			mainMenu.sprite, mainMenu.pos, mainMenu.scale,
			frame, bufferFrame, buffer);
	}

	if (showGameIcons == 1)
	{
		// gun icons
		gf3d_sprite_draw(
			currentGunIcon.sprite, currentGunIcon.pos, currentGunIcon.scale,
			frame, bufferFrame, buffer);

		// health bars
		switch (health)
		{
			case 10:
				gf3d_sprite_draw(
					healthBar10.sprite, healthBar10.pos, healthBar10.scale,
					frame, bufferFrame, buffer);
				break;
			case 9:
				gf3d_sprite_draw(
					healthBar9.sprite, healthBar9.pos, healthBar9.scale,
					frame, bufferFrame, buffer);
				break;
			case 8:
				gf3d_sprite_draw(
					healthBar8.sprite, healthBar8.pos, healthBar8.scale,
					frame, bufferFrame, buffer);
				break;
			case 7:
				gf3d_sprite_draw(
					healthBar7.sprite, healthBar7.pos, healthBar7.scale,
					frame, bufferFrame, buffer);
				break;
			case 6:
				gf3d_sprite_draw(
					healthBar6.sprite, healthBar6.pos, healthBar6.scale,
					frame, bufferFrame, buffer);
				break;
			case 5:
				gf3d_sprite_draw(
					healthBar5.sprite, healthBar5.pos, healthBar5.scale,
					frame, bufferFrame, buffer);
				break;
			case 4:
				gf3d_sprite_draw(
					healthBar4.sprite, healthBar4.pos, healthBar4.scale,
					frame, bufferFrame, buffer);
				break;
			case 3:
				gf3d_sprite_draw(
					healthBar3.sprite, healthBar3.pos, healthBar3.scale,
					frame, bufferFrame, buffer);
				break;
			case 2:
				gf3d_sprite_draw(
					healthBar2.sprite, healthBar2.pos, healthBar2.scale,
					frame, bufferFrame, buffer);
				break;
			case 1:
				gf3d_sprite_draw(
					healthBar1.sprite, healthBar1.pos, healthBar1.scale,
					frame, bufferFrame, buffer);
				break;
			case 0:
				gf3d_sprite_draw(
					deathMenu.sprite, deathMenu.pos, deathMenu.scale,
					frame, bufferFrame, buffer);

				SetGameState(GAMEOVER);

				break;
		}
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
	showGameIcons = 1;
}