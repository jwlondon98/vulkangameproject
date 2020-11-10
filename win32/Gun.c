#include "Gun.h"

Bullet Shoot(Gun *g, Vector3D spawnPos)
{
	Bullet* bullet = CreateBullet(spawnPos);
	return *bullet;
}