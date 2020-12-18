#ifndef __CAMERA_SEQUENCE_CONTROLLER_H__
#define __CAMERA_SEQUENCE_CONTROLLER_H__

#include "../gfc/include/gfc_matrix.h"
#include "Entity.h"
#include "PositionRecorder.h"
#include "gf3d_vgraphics.h"

void CloseCamSeqController();
void InitCameraController(Uint32 numPositions);
void FreeTrigger(Entity *trigger);

void CreateTrigger(Vector3D spawnPos, Vector3D rot);
void MoveToNextTrigger();
void EnableDisableTriggerRender(int enable);

Entity* GetTriggerList();
int GetTriggerCount();

#endif