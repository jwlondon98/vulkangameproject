#pragma once

#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "gfc_vector.h"
#include "Bullet.h"

typedef struct Collider_S
{
	Vector3D center;
	Vector3D extents;

	Vector3D min;
	Vector3D max;

	//void(*Update)(Vector3D newCenter);

}Collider;


Collider* CreateCollider();
void FreeCollider(Collider* collider);


void UpdateCollider(Collider* collider, Vector3D newCenter);

int DetectCollision(Collider *collider1, Collider *collider2);

#endif