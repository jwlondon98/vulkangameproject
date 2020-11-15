#include "Gun.h"

typedef struct
{
	Bullet		*bulletList;		/* list of entities */
	Uint32		bulletCount;		/* numer of current active entities */

}BulletManager;

static BulletManager bulletManager = { 0 };

struct Gun gun;

CreateGun(int ammoCount)
{
	gun.initialAmmoCount = ammoCount;
	gun.ammoCount = ammoCount;
	gun.gunType = Pistol;
	bulletManager.bulletList = gfc_allocate_array(sizeof(Bullet), ammoCount);

	// spawn bullet to act as gun location holder
	//gun.gunLoc = CreateEntity("gun", 1, vector3d(0,10,0));

	atexit(FreeGun);
}

void FreeGun()
{
	// free any bullets we need to still free
	int i;
	for (i = 0; i < gun.initialAmmoCount; i++)
		FreeBullet(&bulletManager.bulletList[i]);

	memset(&bulletManager, 0, sizeof(BulletManager));
	//memset(gun, 0, sizeof(Gun));
}

void Shoot(Vector3D spawnPos)
{
	if (gun.ammoCount <= 0)
	{
		slog("out of ammo");
		return;
	}

	//slog("spawnPos: (%f, %f, %f)", spawnPos.x, spawnPos.y, spawnPos.z);

	int i;
	for (i = 0; i < gun.initialAmmoCount; i++)
	{
		if (bulletManager.bulletList[i]._inUse == 0)
		{
			if (gun.gunType == Pistol)
			{
				slog("shooting pistol");

				Bullet* bullet;
				bullet = CreateBullet(spawnPos);
				bulletManager.bulletList[i] = *bullet;
				//g->ammoCount -= 1;
				return;
			}
			else if (gun.gunType == Shotgun)
			{
				slog("shooting shotgun");

				Bullet* bullet;
				bullet = CreateBullet(vector3d(spawnPos.x, 50, 0));
				bulletManager.bulletList[i] = *bullet;
				//g->ammoCount -= 1;
				return;
			}
			else if (gun.gunType == Machinegun)
			{
				slog("shooting machinegun");

				Bullet* bullet;
				bullet = CreateBullet(spawnPos);
				bulletManager.bulletList[i] = *bullet;
				//g->ammoCount -= 1;
				return;
			}
		}
	}
	return NULL;
}

Bullet* GetBulletList()
{
	return bulletManager.bulletList;
}

void ChangeGun()
{
	GunType lastGunType = gun.gunType;

	int randNum = GetRandomNum(0, 2);
	if (randNum == 0)
	{
		gun.gunType = Pistol;
		slog("gun type changed to pistol");
	}
	else if (randNum == 1)
	{
		gun.gunType = Shotgun;
		slog("gun type changed to shotgun");
	}
	else if (randNum == 2)
	{
		gun.gunType = Machinegun;
		slog("gun type changed to machinegun");
	}

	gun.gunType = Shotgun;

	// make sure you don't get the same gun type twice in a row
	if (lastGunType == gun.gunType)
	{
		slog("same gun type. changing gun again");
	}
}

void AddScore(int amt)
{
	
}