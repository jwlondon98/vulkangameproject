#ifndef __GUN_H__
#define __GUN_H__

#include "gfc_vector.h"
#include "Bullet.h"

typedef struct Gun_S
{
	float fireRate;
	int ammoCount;
	Bullet* shotBullets;

	Bullet(*Shoot)(struct Gun *g, Vector3D spawnPos);

}Gun;

Bullet Shoot(Gun *g, Vector3D spawnPos);

#endif