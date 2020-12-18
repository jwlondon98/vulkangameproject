#ifndef __POSITIONRECORDER_H__
#define __POSITIONRECORDER_H__

#include "gf3d_model.h"
#include "gf3d_vgraphics.h"
#include <simple_logger.h>
#include "EntitySpawner.h"

typedef struct PositionRecorder
{
	int			_inUse;
	float		step;
	Vector3D	currentPos;
	Matrix4		mat;

	// if set to 1 (with spacebar input) the entity will lock to the pos recorder
	// and the entity will move with it
	int			lastEntityLocked;
};

extern struct PositionRecorder posRec;

void CreatePR();
void FreePR();

void MovePR(Vector3D moveVect);
void UpdateEntRot();

void EnableDisableEntityLock();

void Rotate(float dir, char axis);
void RotateCamera(float dir, char axis);
void RotateCameraAboutEntity(float dir, char axis);
void RotateEntity(Entity* ent, Vector3D rot);

#endif