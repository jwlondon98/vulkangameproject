#ifndef __POSITIONRECORDER_H__
#define __POSITIONRECORDER_H__

#include "gf3d_model.h"
#include <simple_logger.h>

typedef struct PositionRecorder
{
	int			_inUse;
	float		step;
	Vector3D	currentPos;
	Matrix4		mat;
};

extern struct PositionRecorder posRec;

void CreatePR();
void FreePR();

void MovePR(Vector3D moveVect);

#endif