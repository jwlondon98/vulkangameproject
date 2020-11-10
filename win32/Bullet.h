#ifndef __BULLET_H__
#define __BULLET_H__

#include "gf3d_model.h"
#include <simple_logger.h>
#include <Collider.h>
#include <Entity.h>

typedef struct Bullet_S
{
	int			_inUse;
	Model*		model;
	Matrix4		modelMatrix;
	int			speed;

	Collider*	collider;

	Vector3D	lastPos;
}Bullet;

Bullet* CreateBullet(Vector3D spawnPos);
void FreeBullet(Bullet* bullet);

void BulletThink(Bullet* bullet, Entity* entities, int entityCount);
void Move(Bullet* bullet);

#endif