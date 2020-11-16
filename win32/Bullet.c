#include "Bullet.h";

Bullet* CreateBullet(Vector3D spawnPos, int enemyBullet)
{
	Bullet* bullet;
	bullet = malloc(sizeof(Bullet));

	//slog("bullet created at: (%f, %f, %f)", spawnPos.x, spawnPos.y, spawnPos.z);

	bullet->model = gf3d_model_load("bullet");
	bullet->_inUse = 1;
	bullet->speed = 1;
	bullet->lastPos = spawnPos;
	bullet->collider = CreateCollider();
	bullet->collider->extents = vector3d(0.1, 0.1, 0.1);
	UpdateCollider(bullet->collider, spawnPos);

	// is the bullet an enemy bullet?
	bullet->enemyBullet = enemyBullet;

	// set model's position to world origin
	gfc_matrix_identity(bullet->modelMatrix);

	// move bullet to spawn pos
	gfc_matrix_make_translation(
		bullet->modelMatrix,
		spawnPos
	);

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
		if (entities[i]._inUse == 1 && DetectCollision(bullet->collider, entities[i].collider, i) == 1)
		{
			/*slog("\nlast bullet pos: (%f, %f, %f)", bullet->lastPos.x,
				bullet->lastPos.y, bullet->lastPos.z);*/

			//Vector3D lastEntityPos = entities[i].lastPos;
			/*slog("\nlast entity pos: (%f, %f, %f)", lastEntityPos.x,
				lastEntityPos.y, lastEntityPos.z);*/

			if (entities[i].renderOn == 1)
			{
				if (entities[i].entityType == Gun)
					return;

				// keep enemy from killing itself
				if (bullet->enemyBullet == 1)
					return;

				// free entity
				entities[i]._inUse = 0;
				entities[i].renderOn = 0;

				// handle the entity hit 
				HandleEntityHit(entities[i].entityType, bullet);

				FreeEntity(&entities[i]);
				// delay and spawn new entity
				Delay(2, EntityCreate, &entities[i]);
			}
			bullet->_inUse = 0;
			FreeBullet(bullet);
			return;
		}
		else
		{
			Move(bullet);
		}
	}
}

void HandleEntityHit(EntityType entType, Bullet* bullet)
{
	int randNum;
	switch (entType)
	{
		case EnemyBasic:
			break;
		case EnemyAdvanced:
			break;
		case Hostage:
			break;
		case Target:
			break;
		case WeaponDrop:
			StartGunChange();
			break;
	}
}

void Move(Bullet* bullet)
{
	if (bullet->_inUse == 0)
		return;

	Vector3D lastPos = bullet->lastPos;

	float xPos = lastPos.x;
	float yPos;
	if (bullet->enemyBullet == 0)
		yPos = lastPos.y - bullet->speed;
	else
		yPos = lastPos.y + bullet->speed;
	float zPos = lastPos.z + bullet->speed;

	gfc_matrix_make_translation(
		bullet->modelMatrix,
		vector3d(xPos, yPos, 0)
	);

	bullet->lastPos = vector3d(xPos, yPos, 0);

	UpdateCollider(bullet->collider, bullet->lastPos);

	//slog("bullet moved to pos: (%f ,%f, %f)", xPos, yPos, zPos);
}
