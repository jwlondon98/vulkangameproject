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

	int lane;

	Entity* gunLoc;

	GunType gunType;

	void(*EnemyShoot)(Vector3D spawnPos);
};

extern struct Gun gun;

void CreateGun(int ammoCount);
void FreeGun();

void Shoot(Vector3D spawnPos);
void EnemyShoot(Vector3D spawnPos);

Bullet* GetBulletList();

void StartGunChange();

static int ChangeGun(void * data);

void SaveHostage(Entity* entities, int count);

#endif