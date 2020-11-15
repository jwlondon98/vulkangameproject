#include "Gun.h"

typedef struct
{
	Bullet		*bulletList;		/* list of entities */
	Uint32		bulletCount;		/* numer of current active entities */

}BulletManager;

static BulletManager bulletManager = { 0 };

Gun* CreateGun(int ammoCount)
{
	Gun* gun;
	gun = malloc(sizeof(Gun));
	gun->initialAmmoCount = ammoCount;
	gun->ammoCount = ammoCount;
	gun->gunType = Pistol;
	bulletManager.bulletList = gfc_allocate_array(sizeof(Bullet), ammoCount);

	// spawn bullet to act as gun location holder
	gun->gunLoc = CreateBullet(vector3d(0,10,0));

	atexit(FreeGun);
	return gun;
}

void FreeGun(Gun* gun)
{
	// free any bullets we need to still free
	int i;
	for (i = 0; i < gun->initialAmmoCount; i++)
		FreeBullet(&bulletManager.bulletList[i]);

	memset(&bulletManager, 0, sizeof(BulletManager));
	memset(gun, 0, sizeof(Gun));
}

void Shoot(Gun *g, Vector3D spawnPos)
{
	if (g->ammoCount <= 0)
	{
		slog("out of ammo");
		return;
	}

	slog("spawnPos: (%f, %f, %f)", spawnPos.x, spawnPos.y, spawnPos.z);

	int i;
	for (i = 0; i < g->initialAmmoCount; i++)
	{
		if (bulletManager.bulletList[i]._inUse == 0)
		{
			if (g->gunType == Pistol)
			{
				Bullet* bullet;
				bullet = CreateBullet(spawnPos);
				bulletManager.bulletList[i] = *bullet;
				bulletManager.bulletList[i]._inUse = 1;
				//g->ammoCount -= 1;
				return;
			}
			else if (g->gunType == Shotgun)
			{
				int j;
				for (j = 0; j < 2; j++)
				{
					Bullet* bullet;
					if (j == 0)
						bullet = CreateBullet(vector3d(-10, 50, 0));
					else if (j == 1)
						bullet = CreateBullet(vector3d(0, 50, 0));
					else if (j == 2)
						bullet = CreateBullet(vector3d(10, 50, 0));
					bulletManager.bulletList[i] = *bullet;
					bulletManager.bulletList[i]._inUse = 1;
					//g->ammoCount -= 1;
					return;
				}
			}
			else if (g->gunType == Machinegun)
			{
				
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

	// make sure you don't get the same gun type twice in a row
	if (lastGunType == gun.gunType)
	{
		slog("same gun type. changing gun again");
		ChangeGun(gun);
	}
}

void AddScore(int amt)
{
	
}