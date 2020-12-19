#include "CameraSequenceController.h"

typedef struct 
{
	Entity *triggers;		// list of triggers
	int triggerCount;

	int triggerIndex;		// the index of the trigger that the player is currently at
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
	MoveToNextTrigger(trigger->lastPos, trigger->lastRot);

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
			camSeqController.triggers[i].renderOn = 1;
			camSeqController.triggers[i].model = gf3d_model_load("trigger");
			camSeqController.triggers[i].entityType = None;
			camSeqController.triggers[i].state = NONE;
			camSeqController.triggers[i].canThink = 0;
			camSeqController.triggers[i].entityName = "trigger";

			camSeqController.triggers[i].speed = 0.1;

			// create a trigger collider
			//camSeqController.triggers[i].collider = CreateCollider();
			//camSeqController.triggers[i].collider->extents = vector3d(1, 1, 1);

			// set model's position to world origin
			gfc_matrix_identity(camSeqController.triggers[i].modelMatrix);
			gfc_matrix_make_translation(
				camSeqController.triggers[i].modelMatrix,
				spawnPos
			);
			camSeqController.triggers[i].lastPos = spawnPos;

			camSeqController.triggers[i].lastRot = rot;

			slog("TRIGGER CREATED");

			return &camSeqController.triggers[i];
		}
	}

	slog("Failed to add trigger to triggers list, no unused slots");
}

void MoveToNextTrigger()
{
	if (camSeqController.triggerIndex >= camSeqController.triggerCount)
	{
		slog("CANNOT MOVE TO NEXT TRIGGER. NO NEXT TRIGGER.");
		return;
	}

	Entity *trigger = &camSeqController.triggers[camSeqController.triggerIndex];
	trigger->state = MOVE;
	trigger->canThink = 1;

	camSeqController.triggerIndex++;
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