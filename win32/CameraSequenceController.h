#pragma once

#ifndef __CAMERA_SEQUENCE_CONTROLLER_H__
#define __CAMERA_SEQUENCE_CONTROLLER_H__

#include "../gfc/include/gfc_matrix.h"
#include "Entity.h"
#include "PositionRecorder.h"
#include "../include/gf3d_vgraphics.h"

//struct CamSeqController
//{
//	Entity *triggers;		// list of triggers
//	int triggerCount;
//
//	int triggerIndex;		// the index of the trigger that the player is currently at
//};
//
//extern struct CamSeqController camSeqController;

void InitCameraController(Uint32 numTriggers);
void CloseCamSeqController();
void FreeTrigger(Entity *trigger);

Entity* CreateTrigger(Vector3D spawnPos, Vector3D rot);
void MoveToNextTrigger();
void EnableDisableTriggerRender(int enable);

Entity* GetTriggerList();
int GetTriggerCount();

#endif