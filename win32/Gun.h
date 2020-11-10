#ifndef __GUN_H__
#define __GUN_H__

#include "gfc_vector.h"

typedef struct Gun_S
{
	float fireRate;
	int ammoCount;

	void(*Shoot)(struct Gun *g, Vector3D spawnPos);

}Gun;

void Shoot(Gun *g, Vector3D spawnPos);

#endif