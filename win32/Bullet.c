#include "Bullet.h";

Bullet* CreateBullet(Vector3D spawnPos)
{
	Bullet* bullet;
	bullet = malloc(sizeof(Bullet));

	bullet->model = gf3d_model_load("cube2");
	bullet->speed = 1;
	bullet->lastPos = spawnPos;
	bullet->collider = CreateCollider();
	bullet->collider->extents = vector3d(1, 1, 1);
	UpdateCollider(bullet->collider, vector3d(0, 0, 0));

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

	slog("bullet destroyed");


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
		if (entities[i]._inUse == 1 && DetectCollision(bullet->collider, entities[i].collider) == 1)
		{
			entities[i]._inUse = 0;
			entities[i].renderOn = 0;
			bullet->_inUse = 0;
			FreeBullet(bullet);
		}
		else
		{
			Move(bullet);
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
		vector3d(0, yPos, 0)
	);

	bullet->lastPos = vector3d(0, yPos, 0);

	UpdateCollider(bullet->collider, bullet->lastPos);

	//slog("bullet moved to pos: (%f ,%f, %f)", xPos, yPos, zPos);
}

int GetDistance(float yPos1, float yPos2)
{
	if (yPos1 <= yPos2)
	{
		slog("distance of 0 reached. there was a collision");
		return 1;
	}
	else
		return 0;
}