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
	slog("Entity Spawned using Entity Spawner");
	CreateEntity(lastEntityName, 1, posRec.currentPos);
}