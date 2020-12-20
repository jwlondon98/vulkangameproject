#include "SpriteManager.h"


void InitSpriteManager()
{
	gf3d_sprite_manager_init(10, gf3d_swapchain_get_chain_length(), gf3d_vgraphics_get_default_logical_device());

	pistolIcon = gf3d_sprite_load("images/UI/pistol.png", -1, -1, 0);
	if (!pistolIcon)
		slog("no pistol found");
	else
		slog("pistol found");
}

void RenderSprites(Uint32 frame, Uint32 bufferFrame, VkCommandBuffer buffer)
{
	gf3d_sprite_draw(
		pistolIcon, vector2d(-410, 390), vector2d(.3, .3),
		frame, bufferFrame, buffer);
}