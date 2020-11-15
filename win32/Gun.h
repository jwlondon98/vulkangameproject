#pragma once

#ifndef __GUN_H__
#define __GUN_H__

#include "gfc_vector.h"
#include "Bullet.h"

typedef enum
{
	Pistol, Shotgun, Machinegun
}GunType;

struct Gun
{
	float fireRate;
	int initialAmmoCount;
	int ammoCount;

	int score;

	Entity* gunLoc;

	GunType gunType;
};

extern struct Gun gun;

CreateGun(int ammoCount);
void FreeGun();

void Shoot(Vector3D spawnPos);

Bullet* GetBulletList();

void ChangeGun();

void AddScore(int amt);

#endif