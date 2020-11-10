#pragma once

#ifndef __GUN_H__
#define __GUN_H__

#include "gfc_vector.h"
#include "Bullet.h"

typedef struct Gun_S
{
	float fireRate;
	int initialAmmoCount;
	int ammoCount;
}Gun;

Gun* CreateGun(int ammoCount);
void FreeGun(Gun* gun);

Bullet* Shoot(Gun *g, Vector3D spawnPos);

Bullet* GetBulletList();

#endif