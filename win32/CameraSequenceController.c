#include "CameraSequenceController.h"

typedef struct 
{
	Entity *triggers;		// list of triggers
	int triggerCount;

	int triggerIndex;		// the index of the trigger that the player is currently at

	Vector3D camPos;

	Entity* enemies[10];
	int enemyIndex;

}CamSeqController;

static CamSeqController camSeqController = { 0 };

void InitCameraController(Uint32 numTriggers)
{
	if (camSeqController.triggers != NULL)
	{
		slog("WARNING: cam seq controller already initialized");
		return;
	}

	// allocate memory 
	camSeqController.triggers = gfc_allocate_array(sizeof(Entity), numTriggers);
	if (!camSeqController.triggers)
	{
		slog("failed to allocate memory for entity list");
		return;
	}

	camSeqController.triggerCount = numTriggers;
	atexit(CloseCamSeqController);
	slog("Entity System intiialized");
}

void CloseCamSeqController()
{
	int i;
	if (camSeqController.triggers != NULL)
	{
		for (i = 0; i < camSeqController.triggers; i++)
		{
			FreeEntity(&camSeqController.triggers[i]);
		}
		free(camSeqController.triggers);
	}

	memset(&camSeqController, 0, sizeof(CamSeqController));
	slog("Camera Sequence Controller closed");
}

void FreeTrigger(Entity *trigger)
{
	if (!trigger) return;

	trigger->_inUse = 0;
	trigger->renderOn = 0;

	// Move camera to next trigger location and rotation
	//MoveToNextTrigger(trigger->lastPos, trigger->lastRot);

	gf3d_model_free(trigger->model);
	memset(trigger, 0, sizeof(Entity));
}

Entity* CreateTrigger(Vector3D spawnPos, Vector3D rot)
{
	int i;
	for (i = 0; i < camSeqController.triggerCount; i++)
	{
		if (!camSeqController.triggers[i]._inUse)
		{
			camSeqController.triggers[i]._inUse = 1;
			camSeqController.triggers[i].renderOn = 0;
			camSeqController.triggers[i].model = gf3d_model_load("trigger");
			camSeqController.triggers[i].entityType = None;
			camSeqController.triggers[i].state = NONE;
			camSeqController.triggers[i].canThink = 0;
			camSeqController.triggers[i].entityName = "trigger";

			camSeqController.triggers[i].speed = 0.05;

			// create a trigger collider
			//camSeqController.triggers[i].collider = CreateCollider();
			//camSeqController.triggers[i].collider->extents = vector3d(1, 1, 1);

			// set model's position to world origin
			/*gfc_matrix_identity(camSeqController.triggers[i].modelMatrix);
			gfc_matrix_make_translation(
				camSeqController.triggers[i].modelMatrix,
				spawnPos
			);
			camSeqController.triggers[i].lastPos = spawnPos;

			RotateEntity(&camSeqController.triggers[i], rot);
			camSeqController.triggers[i].lastRot = rot;*/

			slog("TRIGGER CREATED");

			return &camSeqController.triggers[i];
		}
	}

	slog("Failed to add trigger to triggers list, no unused slots");
}

void MoveToNextTrigger(Vector2D dir)
{
	if (camSeqController.triggerIndex >= camSeqController.triggerCount)
	{
		slog("CANNOT MOVE TO NEXT TRIGGER. NO NEXT TRIGGER.");
		return;
	}

	Entity *trigger = &camSeqController.triggers[camSeqController.triggerIndex];
	trigger->state = MOVE;
	trigger->moveDir = dir;
	trigger->canThink = 1;

	camSeqController.triggerIndex++;
}

void HandleEnemiesAtTriggerPos()
{
	slog("HandleEnemiesAtTriggerPos");

	switch (camSeqController.triggerIndex)
	{
		case 1:
			camSeqController.enemies[0]->canThink = 1;
			camSeqController.enemies[0]->state = FIGHT;
			camSeqController.enemies[1]->canThink = 1;
			camSeqController.enemies[1]->state = FIGHT;
			camSeqController.enemies[2]->canThink = 1;
			camSeqController.enemies[2]->state = FIGHT;
			slog("TRIGGER POS 1 ENEMIES ENABLED");
			break;
		case 4:
			camSeqController.enemies[3]->canThink = 1;
			camSeqController.enemies[3]->state = FIGHT;
			slog("TRIGGER POS 4 ENEMIES ENABLED");
			break;
		case 5:
			camSeqController.enemies[4]->canThink = 1;
			camSeqController.enemies[4]->state = FIGHT;
			slog("TRIGGER POS 5 ENEMIES ENABLED");
			break;
		case 6:
			camSeqController.enemies[5]->canThink = 1;
			camSeqController.enemies[5]->state = FIGHT;
			slog("TRIGGER POS 6 ENEMIES ENABLED");
			break;
		case 7:
			camSeqController.enemies[6]->canThink = 1;
			camSeqController.enemies[6]->state = FIGHT;
			slog("TRIGGER POS 7 BOSS ENABLED");
			break;
	
	}
}

void MoveCameraToTrigger(Entity* entity)
{
	if (entity->canThink == 0)
	{
		slog("Trigger not allowed to think. Cannot move camera.");
		return;
	}

	Vector3D lastCamPos = camSeqController.camPos;
	Vector3D targetPos = entity->lastPos;
	Vector2D moveDir = entity->moveDir;
	/*slog("last cam pos x: %f", lastCamPos.x);
	slog("target pos x: %f", targetPos.x);
	slog("xDiff: %f", xDiff);*/
	//slog("zDiff: %f", zDiff);



	float xPos, yPos, zPos;

	Bool atPos = vector3d_distance_between_less_than(vector3d(-targetPos.x, -targetPos.y, -targetPos.z), lastCamPos, 1);
	if (atPos == false)
	{
		Vector3D newPos;

		if (moveDir.x == -1)
			newPos = vector3d(lastCamPos.x + entity->speed, 0, lastCamPos.z);
		else if (moveDir.x == 1)
			newPos = vector3d(lastCamPos.x - entity->speed, 0, lastCamPos.z);
		else if (moveDir.y == 1)
			newPos = vector3d(lastCamPos.x, 0, lastCamPos.z + entity->speed);

		camSeqController.camPos = newPos;

		gf3d_vgraphics_translate_camera(camSeqController.camPos);
		return;
	}
	else
	{
		slog("camera reached trigger pos");
		entity->canThink = 0;
		HandleEnemiesAtTriggerPos();
	}
}

void TriggerThink(Entity* entity)
{
	MoveCameraToTrigger(entity);
}

void EnableDisableTriggerRender(int enable)
{
	int i;
	for (i = 0; i < camSeqController.triggerCount; i++)
		camSeqController.triggers[i].renderOn = enable;

	if (enable == 0)
		slog("Trigger Renders disabled");
	else
		slog("Trigger Renders enabled");
}

Entity* GetTriggerList()
{
	return camSeqController.triggers;
}

int GetTriggerCount()
{
	return camSeqController.triggerCount;
}

void AddEnemyToCamSeqController(Entity* ent)
{
	camSeqController.enemies[camSeqController.enemyIndex] = ent;
	slog("enemy %s added to cam seq controller", camSeqController.enemies[camSeqController.enemyIndex]->entityName);

	camSeqController.enemyIndex++;
}