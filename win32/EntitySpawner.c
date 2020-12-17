#include "EntitySpawner.h"

void SelectEntity(int index)
{
	switch (index)
	{
		case 1:
			lastEntityName = "wall2";
			break;
		case 2:
			lastEntityName = "enemy1";
			break;
	}
}

void SpawnEntity()
{
	//SpawnSpecificEntity("wall", vector3d(0, 3, 0));

	posRec.lastEntityLocked = 0;

	if (!jsonFile)
	{
		CreateJSONFile();
		entityNum = 0;
	}

	if (!lastEntityName)
		lastEntityName = "wall2";

	slog("%s spawned at (%f, %f, %f)", 
		lastEntityName, posRec.currentPos.x, posRec.currentPos.y, posRec.currentPos.z);

	Vector3D spawnPos = vector3d(
		0 - posRec.currentPos.x, 0 - posRec.currentPos.y, 0 - posRec.currentPos.z
	);

	char key[3];
	itoa(entityNum, key, 10);

	WriteJSONStr(key, lastEntityName);
	WriteJSONVect(key, spawnPos);

	lastSpawnedEntity = CreateEntity(lastEntityName, 1, spawnPos);
	lastSpawnedEntity->lastPos = spawnPos;
	if (lastSpawnedEntity)
		slog("WE HAVE A LAST SPAWNED ENTITY");
	entityNum++;
	slog("entitynum: %i", entityNum);

	sj_save(jsonFile, "Level1.json");
}

//void SpawnSpecificEntity(char* entityName, Vector3D spawnPos)
//{
//	slog("%s: (%f, %f, %f)", entityName, spawnPos.x, spawnPos.y, spawnPos.z);
//	CreateEntity(entityName, 1, spawnPos);
//}

void DestroyEntity()
{
	if (posRec.lastEntityLocked == 1)
	{
		FreeEntity(lastSpawnedEntity);
		posRec.lastEntityLocked = 0;
	}
}