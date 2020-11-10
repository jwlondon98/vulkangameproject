#include "Gun.h"

typedef struct
{
	Bullet		*bulletList;		/* list of entities */
	Uint32		bulletCount;		/* numer of current active entities */

}BulletManager;

static BulletManager bulletManager = { 0 };

Gun* CreateGun(int ammoCount)
{
	slog("create gun start");
	Gun* gun;
	gun = malloc(sizeof(Gun));
	slog("create gun check");
	gun->initialAmmoCount = ammoCount;
	gun->ammoCount = ammoCount;
	bulletManager.bulletList = gfc_allocate_array(sizeof(Bullet), ammoCount);
	slog("create gun check 2");

	slog("gun created");

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

Bullet* Shoot(Gun *g, Vector3D spawnPos)
{
	slog("spawnPos: (%f, %f, %f)", spawnPos.x, spawnPos.y, spawnPos.z);

	if (g->ammoCount <= 0)
		return;

	Bullet* bullet;
	int i;
	for (i = 0; i < g->initialAmmoCount; i++)
	{
		if (bulletManager.bulletList[i]._inUse == 0)
		{
			bullet = CreateBullet(spawnPos);
			bulletManager.bulletList[i]._inUse = 1;
			bulletManager.bulletList[i] = *bullet;
			g->ammoCount -= 1;
			return &bullet;
		}
	}
	return NULL;
}

Bullet* GetBulletList()
{
	return bulletManager.bulletList;
}