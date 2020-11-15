#pragma once

#ifndef __GUN_H__
#define __GUN_H__

#include "gfc_vector.h"
#include "Bullet.h"

typedef enum
{
	Pistol, Shotgun, Machinegun
}GunType;

typedef struct Gun_S
{
	float fireRate;
	int initialAmmoCount;
	int ammoCount;

	int score;

	Bullet* gunLoc;

	GunType gunType;
}Gun;

static Gun gun;

Gun* CreateGun(int ammoCount);
void FreeGun(Gun* gun);

void Shoot(Gun *g, Vector3D spawnPos);

Bullet* GetBulletList();

void ChangeGun(Gun* gun);

void AddScore(int amt);

#endif