#include "EntitySpawner.h"


void SelectEntity(int index)
{
	switch (index)
	{
		case 1:
			lastEntityName = "wall";
			break;
		case 2:
			lastEntityName = "enemy1";
			break;
	}
}

void SpawnEntity()
{
	if (!lastEntityName)
		lastEntityName = "wall";

	slog("%s spawned at (%f, %f, %f)", 
		lastEntityName, posRec.currentPos.x, posRec.currentPos.y, posRec.currentPos.z);

	Vector3D spawnPos = vector3d(
		0 - posRec.currentPos.x, 0 - posRec.currentPos.y, 0 - posRec.currentPos.z
	);

	CreateEntity(lastEntityName, 1, spawnPos);
}