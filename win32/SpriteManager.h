#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__

#include "gf3d_vgraphics.h"
#include "gf3d_swapchain.h"

Sprite *pistolIcon;

void InitSpriteManager();
void RenderSprites(Uint32 frame, Uint32 bufferFrame, VkCommandBuffer buffer);

#endif