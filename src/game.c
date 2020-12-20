#include <SDL.h>   
#include <SDL_ttf.h>

#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"
#include "gf3d_sprite.h"

#include "InputPoller.h"
#include "Entity.h"
#include "Gun.h"
#include "PositionRecorder.h"
#include "CameraSequenceController.h"
#include "AudioPlayer.h"
#include "SpriteManager.h"

void CreateEntities()
{
	InitEntity(20, Game);

	// invisible walls to destroy passed bullets
	CreateEntity("player", 0, vector3d(0, -1000, 0), vector3d(0, 0, 0));
	CreateEntity("cube", 0, vector3d(10,-100,0), vector3d(0, 0, 0));
	CreateEntity("cube", 0, vector3d(0,-100,0), vector3d(0, 0, 0));
	CreateEntity("cube", 0, vector3d(-10,-100,0), vector3d(0, 0, 0));

	CreateEntity("enemy1", 1, vector3d(10,-50,0), vector3d(0, 0, 0));
	CreateEntity("enemy2", 1, vector3d(0,-50,0), vector3d(0, 0, 0));
	CreateEntity("enemy1", 1, vector3d(-10,-50,0), vector3d(0, 0, 0));
}

int main(int argc,char *argv[])
{
	// CHANGE THIS IF CREATING LEVELS OR PLAYING THE GAME
	GameMode gameMode = LevelEdit; //Game

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
        "CUBISM",						//program name
        screenWidth,				//screen width
		screenHeight,				//screen height
        vector4d(0.51,0.75,1,1),	//background color
        0,							//fullscreen
        validate					//validation
    );
	slog_sync();

	// move camera to origin
	gf3d_vgraphics_translate_camera(vector3d(0, 0, 0), 1);

	InitRandom();
	
	InitAudio();

	//PlayMusic(bgMusic);

	InitGameStateManager();

	InitSpriteManager();

	Bullet* bulletList;

	if (gameMode == LevelEdit)
	{
		// Create PositionRecorder
		CreatePR();

		// Init Entity Manager
		InitEntity(100, LevelEdit);
	}
	else
	{
		// Init Entity Manager
		InitEntity(100, Game);

		// this will be loaded from json file instead
		//CreateEntities();

		//Entity player;

		// create a gun for the player
		CreateGun(Pistol, 300);
		bulletList = GetBulletList();
	}
	
	// Init camera controller
	InitCameraController(100);

	// Load entities from level JSON file
	LoadJSON();

	// do SDL stuff
	SDL_SetRelativeMouseMode(SDL_TRUE);

	// main game loop
	slog("gf3d main loop begin");

	GameState gameState;

	//Entity *cubeAnim = CreateAnimatedEntity("CubeShrink", 1, vector3d(0,0,0), vector3d(0, 0, 0), 1, 30, 0.05);

    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        //update game things here
        
		Entity* entityList = GetEntityList();
		int entityCount = GetEntityCount();

		Entity* triggerList = GetTriggerList();
		int triggerCount =  GetTriggerCount();

		// Poll
		int lastXMousePos = xMousePos;
		int lastYMousePos = yMousePos;
		PollForInput();

		gameState = GetGameState();

		if (gameMode == Game)
		{
			// Detect shooting
			if (mouseBtn == PRESSED)
			{
				if (gun.gunType != Shotgun)
				{
					if (gunPos == -1)
						Shoot(vector3d(10, 50, 0));
					else if (gunPos == 0)
						Shoot(vector3d(0, 50, 0));
					else if (gunPos == 1)
						Shoot(vector3d(-10, 50, 0));
				}
				else
				{
					Shoot(vector3d(10, 50, 0));
					Shoot(vector3d(0, 50, 0));
					Shoot(vector3d(-10, 50, 0));
				}

				if (gun.gunType != Machinegun)
					mouseBtn = RELEASED;
			}

			// Detect hostage pull
			if (spaceBtn == PRESSED)
			{
				int k;
				for (k = 0; k < entityCount; k++)
				{
					if (entityList[k].entityType != Hostage)
						continue;

					entityList[k].speed = 2;
				}
				SaveHostage(entityList, entityCount);
				//spaceBtn = RELEASED;
			}
			else if (spaceBtn == RELEASED)
		{
			int k;
			for (k = 0; k < entityCount; k++)
			{
				if (entityList[k].entityType != Hostage)
					continue;

				entityList[k].speed = 0.5;
			}
		}
		}


        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        bufferFrame = gf3d_vgraphics_render_begin();
        gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_pipeline(),bufferFrame);
        gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_overlay_pipeline(),bufferFrame);
        commandBuffer = gf3d_command_rendering_begin(bufferFrame, gf3d_vgraphics_get_graphics_pipeline());

		// render bullet and move it
		if (gameMode == Game)
		{
			int j;
			for (j = 0; j < gun.ammoCount; j++)
			{
				if (bulletList[j]._inUse == 1)
				{
					BulletThink(&bulletList[j], entityList, entityCount);

					if (bulletList[j].lastPos.y > 50)
					{
						//slog("enemy bullet passed player. destroying");
						AddScore(&entityList[0], -20);
						FreeBullet(&bulletList[j]);
					}

					if (bulletList[j].model)
						gf3d_model_draw(bulletList[j].model, bufferFrame, commandBuffer, bulletList[j].modelMatrix, 0);
				}
			}
		}

		// loop through all entities of the entity manager
		int i;
		for (i = 0; i < entityCount; i++)
		{
			// if current entity is set to render..
			if (entityList[i]._inUse == 1 && entityList[i].renderOn == 1)
			{
				// update the entity's collider position
				//UpdateCollider(entityList[i].collider, entityList[i].lastPos);

				// handle entity thinking if the gameMode is a Game
				if (gameMode == Game)
				{
					if (entityList[i].state != NONE ||
						entityList[i].state != WAIT)
					{
						if (entityList[i].canThink == 1)
						{
							slog("entity %s is thinking", entityList[i].entityName);
							Think(&entityList[i]);
						}
					}

					if (entityList[i].state == ATTACK)
					{
						if (entityList[i].entityType == EnemyAdvanced)
						{
							EnemyShoot(entityList[i].lastPos);
							entityList[i].state = NONE;
						}
						else
							entityList[i].state = MOVE;
					}
				}

				// draw model
				if (entityList[i].model)
				{
					if (entityList[i].isAnimated == 0)
						gf3d_model_draw(
							entityList[i].model, bufferFrame, commandBuffer, entityList[i].modelMatrix, 0);
					else
					{
						//slog("rendering animated model: %s at frame %i", entityList[i].entityName, entityList[i].currFrame);

						if (entityList[i].currAnimState != AnimPlay)
							continue;

						// reset frame to start
						if (entityList[i].currFrame >= entityList[i].endFrame)
						{
							entityList[i].currAnimState = entityList[i].endAnimState;
							entityList[i].currFrame = entityList[i].startFrame;
						}
						else
						{
							// draw model based on current frame
							gf3d_model_draw(
								entityList[i].model, bufferFrame, commandBuffer,
								entityList[i].modelMatrix, entityList[i].currFrame - 1);

							entityList[i].frameInc += entityList[i].frameIncStart;
							slog("FRAME INC: %f", entityList[i].frameInc);
							entityList[i].currFrame = entityList[i].currFrame + (int)entityList[i].frameInc;
							if (entityList[i].frameInc >= 1)
								entityList[i].frameInc = entityList[i].frameIncStart;
						}
					}
				}
			}
		}

		// loop through all triggers and move camera to next trigger
		// if the current trigger is able to think
		for (i = 0; i < triggerCount; i++)
		{
			// if current entity is being used
			if (triggerList[i]._inUse == 1)
			{
				// update the entity's collider position
				//UpdateCollider(entityList[i].collider, entityList[i].lastPos);

				if (triggerList[i].canThink == 1)
					TriggerThink(&triggerList[i]);

				if (triggerList[i].renderOn == 1 && triggerList[i].model)
					gf3d_model_draw(triggerList[i].model, bufferFrame, commandBuffer, triggerList[i].modelMatrix, 0);
			}
		}

        gf3d_command_rendering_end(commandBuffer);

		// 2d rendering 
		commandBuffer = gf3d_command_rendering_begin(bufferFrame, gf3d_vgraphics_get_graphics_overlay_pipeline());
		RenderSprites(0, bufferFrame, commandBuffer);
        gf3d_command_rendering_end(commandBuffer);
            
        int rendEnd = gf3d_vgraphics_render_end(bufferFrame);
		if (rendEnd == 1)
		{
			slog("failed to end render. force quitting to save computer from dying");
			CloseEntity();
			CloseGun();
			done = 1;
		}

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }    
    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    slog("gf3d program end");
	CloseAudio();
    slog_sync();
    return 0;
}

/*eol@eof*/
