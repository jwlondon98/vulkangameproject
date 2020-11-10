#include "Bullet.h";

Bullet* CreateBullet(Vector3D spawnPos)
{
	Bullet* bullet;
	bullet = malloc(sizeof(Bullet));

	bullet->model = gf3d_model_load("cube");
	bullet->speed = 1;
	bullet->lastPos = spawnPos;
	/*bullet->collider = CreateCollider();
	bullet->collider->extents = vector3d(1, 1, 1);
	UpdateCollider(bullet->collider, vector3d(0, 0, 0));*/

	// set model's position to world origin
	gfc_matrix_identity(bullet->modelMatrix);

	// move bullet to spawn pos
	gfc_matrix_make_translation(
		bullet->modelMatrix,
		spawnPos
	);

	slog("bullet created");

	atexit(FreeBullet);
	return bullet;
}

void FreeBullet(Bullet* bullet )
{
	if (!bullet) return;

	gf3d_model_free(bullet->model);

	bullet->_inUse = 0;
	memset(bullet, 0, sizeof(Bullet));
}

void BulletThink(Bullet* bullet, Entity* entities, int entityCount)
{
	// loop through all entities
	int i;
	for (i = 0; i < entityCount; i++)
	{
		// if a collision between the bullet and any of the rendered entities occurs..
		if (entities[i].renderOn)
		{
			slog("bullet hit something");
			bullet->_inUse = 0;
		}
		else
		{
			Move(bullet);
			slog("bullet moving");
		}
	}
}

void Move(Bullet* bullet)
{
	if (bullet->_inUse == 0)
		return;

	Vector3D lastPos = bullet->lastPos;

	float xPos = lastPos.x + bullet->speed;
	float yPos = lastPos.y - bullet->speed;
	float zPos = lastPos.z + bullet->speed;

	gfc_matrix_make_translation(
		bullet->modelMatrix,
		vector3d(xPos, yPos, zPos)
	);

	bullet->lastPos = vector3d(0, yPos, 0);

	//UpdateCollider(bullet->collider, bullet->lastPos);

	if (yPos <= -300)
		FreeBullet(bullet);

	slog("bullet moved to pos: (%f ,%f, %f)", xPos, yPos, zPos);
}