#include "Bullet.h";

Bullet* CreateBullet(Vector3D spawnPos)
{
	Bullet* bullet;
	bullet = malloc(sizeof(Bullet));

	bullet->model = gf3d_model_load("cube");


	atexit(FreeBullet);
	return bullet;
}

void FreeBullet(Bullet* bullet )
{
	if (!bullet) return;

	memset(bullet, 0, sizeof(Bullet));
}