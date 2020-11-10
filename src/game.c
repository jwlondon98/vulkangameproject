#include <SDL.h>            

#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"
#include "InputPoller.h"
#include "Entity.h"
#include "Gun.h";

void CreateEntities()
{
	InitEntity(3);

	CreateEntity("cube");
	//CreateEntity("cube");
	//CreateEntity("cube");
}

int main(int argc,char *argv[])
{
    int done = 0;
    int a;
    Uint8 validate = 0;
    const Uint8 * keys;
    Uint32 bufferFrame = 0;
    VkCommandBuffer commandBuffer;
    Model *model;
    Matrix4 modelMat;
    Model *model2;
    Matrix4 modelMat2;
    
	screenWidth = 1200;
	screenHeight = 700;

    for (a = 1; a < argc;a++)
    {
        if (strcmp(argv[a],"-disable_validate") == 0)
        {
            validate = 0;
        }
    }
    
    init_logger("gf3d.log");    
    slog("gf3d begin");
    gf3d_vgraphics_init(
        "gf3d",						//program name
        screenWidth,				//screen width
		screenHeight,				//screen height
        vector4d(0.51,0.75,1,1),	//background color
        0,							//fullscreen
        validate					//validation
    );
	slog_sync();

    // main game loop
    slog("gf3d main loop begin");

	InitRandom();

	CreateEntities();

	// do SDL stuff
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//Entity player;

	// create a gun for the player
	Gun* gun = CreateGun(10);
	Bullet* bulletList = GetBulletList();

    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        //update game things here
        
		Entity* entityList = GetEntityList();
		int entityCount = GetEntityCount();

		// Poll
		int lastXMousePos = xMousePos;
		int lastYMousePos = yMousePos;
		PollForInput();

		if (mouseBtn == PRESSED)
		{
			Shoot(gun, vector3d(0, 1000, 0));
			mouseBtn = RELEASED;
		}

		if (enterBtn == PRESSED)
		{
			slog("ENTER PRESESD");
			
		}


		// ROTATE CAMERA
		//slog("DELTA: %i", xMouseDelta);
		//gf3d_vgraphics_rotate_camera((xMousePos - lastXMousePos) * xMouseDelta, 'y', 0.00001);
		//gf3d_vgraphics_rotate_camera((yMousePos - lastYMousePos) * yMouseDelta, 'x', 0.00001);

	/*	else
			gf3d_vgraphics_rotate_camera(xMousePos + lastXMousePos, 'y', 0.0001);*/
		
		//gf3d_vgraphics_rotate_camera(yPos, 'x', 0.02);
		
		// ROTATE THE DINOS
        /*gfc_matrix_rotate(
            modelMat,
            modelMat,
            0.002,
            vector3d(1,0,0));*/
        /*gfc_matrix_rotate(
            modelMat2,
            modelMat2,
            0.002,
            vector3d(0,0,1));*/

		// MOVE PLAYER

        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        bufferFrame = gf3d_vgraphics_render_begin();
        gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_pipeline(),bufferFrame);
        commandBuffer = gf3d_command_rendering_begin(bufferFrame);

		// loop through all entities
		int i;
		for (i = 0; i < entityCount; i++)
		{
			// if current entity is set to render..
			if (entityList[i].renderOn == 1)
			{
				// update the entity's collider position
				//UpdateCollider(entityList[i].collider, entityList[i].lastPos);

				if (entityList[i].state == APPEAR)
				{
					Think(&entityList[i]);
					//Step(&entityList[i], vector3d(-1, 0, -1), 0.1);
				}

				// draw the entity
				gf3d_model_draw(entityList[i].model, bufferFrame, commandBuffer, entityList[i].modelMatrix);
			}
		}

		// render bullet and move it
		int j;
		for (j = 0; j < gun->ammoCount; j++)
		{
			if (bulletList[j]._inUse && bulletList[j].model != NULL)
			{
				BulletThink(&bulletList[j], entityList, entityCount);
				gf3d_model_draw(bulletList[j].model, bufferFrame, commandBuffer, bulletList[j].modelMatrix);
			}
		}
             
        gf3d_command_rendering_end(commandBuffer);
            
        gf3d_vgraphics_render_end(bufferFrame);

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }    
    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    slog("gf3d program end");
    slog_sync();
    return 0;
}

/*eol@eof*/
