#ifndef __BULLET_H__
#define __BULLET_H__

#include "gf3d_model.h"

typedef struct Bullet_S
{
	Model* model;
	Matrix4 modelMatrix;
	int speed;
	//void (Think*)(struct Entity_S *self);
}Bullet;

Bullet* CreateBullet(Vector3D spawnPos);
void FreeBullet(Bullet* bullet);

#endif