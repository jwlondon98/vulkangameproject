#include "SpriteManager.h"


void InitSpriteManager()
{
	gf3d_sprite_manager_init(10, gf3d_swapchain_get_chain_length(), gf3d_vgraphics_get_default_logical_device());

	pistolIcon.sprite = gf3d_sprite_load("images/UI/pistol.png", -1, -1, 0);
	pistolIcon.pos = vector2d(-410, 390);
	pistolIcon.scale = vector2d(.3, .3);

	machinegunIcon.sprite = gf3d_sprite_load("images/UI/machinegun.png", -1, -1, 0);
	machinegunIcon.pos = vector2d(-220, 490);
	machinegunIcon.scale = vector2d(.6, .6);

	currentGunIcon = pistolIcon;
}

void RenderSprites(Uint32 frame, Uint32 bufferFrame, VkCommandBuffer buffer)
{
	gf3d_sprite_draw(
		currentGunIcon.sprite, currentGunIcon.pos, currentGunIcon.scale,
		frame, bufferFrame, buffer);
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