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

void CreateEntities()
{
	InitEntity(1);

	CreateEntity("dino");
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

	CreateEntities();

	model = gf3d_model_load("dino");
	gfc_matrix_identity(modelMat);

    gfc_matrix_make_translation(
            modelMat,
            vector3d(10,0,0)
        );

	// do SDL stuff
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//Entity player;

    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        //update game things here
        
		// Poll
		int lastXMousePos = xMousePos;
		int lastYMousePos = yMousePos;
		PollForInput();

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

        gf3d_model_draw(model,bufferFrame,commandBuffer,modelMat);

		int i;
		Entity* entityList = GetEntityList();
		int entityCount = GetEntityCount();
		for (i = 0; i < entityCount; i++)
		{
			gf3d_model_draw(entityList[i].model, bufferFrame, commandBuffer, entityList[i].modelMatrix);
		}
                //gf3d_model_draw(model2,bufferFrame,commandBuffer,modelMat2);
                
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
