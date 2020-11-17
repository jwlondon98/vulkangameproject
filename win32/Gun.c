#include "Gun.h"

struct Gun gun;

typedef struct
{
	Bullet		*bulletList;		/* list of entities */
	Uint32		bulletCount;		/* numer of current active entities */

}BulletManager;

static BulletManager bulletManager = { 0 };

void CreateGun(GunType gunType, int ammoCount)
{
	gun.initialAmmoCount = ammoCount;
	gun.ammoCount = ammoCount;
	gun.gunType = gunType;
	bulletManager.bulletList = gfc_allocate_array(sizeof(Bullet), ammoCount);

	gun.EnemyShoot = EnemyShoot;

	// spawn bullet to act as gun location holder
	//gun.gunLoc = CreateEntity("gun", 1, vector3d(0,10,0));

	atexit(CloseGun);
	atexit(FreeGun);
}

void CloseGun()
{
	int i;
	if (&bulletManager != NULL)
	{
		for (i = 0; i < bulletManager.bulletCount; i++)
		{
			FreeBullet(&bulletManager.bulletList[i]);
		}
		free(bulletManager.bulletList);
	}

	memset(&bulletManager, 0, sizeof(BulletManager));
	slog("Entity System closed");
}

void FreeGun()
{
	// free any bullets we need to still free
	/*int i;
	for (i = 0; i < gun.initialAmmoCount; i++)
		FreeBullet(&bulletManager.bulletList[i]);*/

	//memset(&bulletManager, 0, sizeof(BulletManager));
	memset(&gun, 0, sizeof(Gun));
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
				//slog("shooting pistol");

				Bullet* bullet;
				bullet = CreateBullet(spawnPos, 0);
				bulletManager.bulletList[i] = *bullet;
				//g->ammoCount -= 1;
				return;
			}
			else if (gun.gunType == Shotgun)
			{
				//slog("shooting shotgun");

				Bullet* bullet;
				bullet = CreateBullet(vector3d(spawnPos.x, 50, 0), 0);
				bulletManager.bulletList[i] = *bullet;
				//g->ammoCount -= 1;
				return;
			}
			else if (gun.gunType == Machinegun)
			{
				//slog("shooting machinegun");

				Bullet* bullet;
				bullet = CreateBullet(spawnPos, 0);
				bulletManager.bulletList[i] = *bullet;
				//g->ammoCount -= 1;
				return;
			}
		}
	}
	return NULL;
}

void EnemyShoot(Vector3D spawnPos)
{
	//slog("enemy shoot");
	Bullet* bullet;
	int i;
	for (i = 0; i < gun.initialAmmoCount; i++)
	{
		if (bulletManager.bulletList[i]._inUse == 0)
		{
			bullet = CreateBullet(spawnPos, 1);
			bullet->speed = 1;

			bulletManager.bulletList[i] = *bullet;

			slog("enemy bullet created");
			return;
		}
	}
}

Bullet* GetBulletList()
{
	return bulletManager.bulletList;
}

void StartGunChange()
{
	SDL_Thread *thread;

	thread = SDL_CreateThread(ChangeGun, "ChangeGun", (void *)NULL);
}

static int ChangeGun(void * data)
{
	GunType lastGunType = gun.gunType;

	InitRandom();
	int randNum = GetRandomNum(0, 3);
	if (randNum == 0)
	{
		gun.gunType = Pistol;
		//slog("gun type changed to pistol");
	}
	else if (randNum == 1)
	{
		gun.gunType = Shotgun;
		//slog("gun type changed to shotgun");
	}
	else if (randNum == 2)
	{
		gun.gunType = Machinegun;
		//slog("gun type changed to machinegun");
	}

	// make sure you don't get the same gun type twice in a row
	if (lastGunType == gun.gunType)
	{
		//slog("same gun type. changing gun again");
	}
}

void SaveHostage(Entity* entities, int count)
{
	//slog("saving hostage");

	int i;
	for (i = 0; i < count; i++)
	{
		if (entities[i].entityType != Hostage)
			continue;

		if (gun.gunType == Shotgun)
			entities[i].speed = 2;
		else
		{
			//slog("GUN LANE: %i", gun.lane);
			//slog("ENTITY LANE: %i", entities[i].lane);
			if (gun.lane == entities[i].lane)
			{
				//slog("CORRECT LANE");
				entities[i].speed = 2;
			}
		}
	}
}