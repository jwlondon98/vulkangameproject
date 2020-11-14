#pragma once

#include "gfc_vector.h"
#include <simple_logger.h>

typedef struct
{
	Vector3D center;
	Vector3D min;
	Vector3D max;
	Vector3D extents;
}Collider;

void FreeCollider(Collider* collider);

void UpdateCollider(Collider *c, Vector3D newCenter);

int DetectCollision(Collider *collider1, Collider *collider2);