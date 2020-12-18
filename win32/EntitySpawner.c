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
	entityNum++;
	posRec.lastEntityLocked = 0;

	if (!jsonFile)
	{
		CreateJSONFile();
		entityNum = 0;
	}

	if (!lastEntityName)
		lastEntityName = "wall2";

	//slog("%s spawned at (%f, %f, %f)", 
		//lastEntityName, posRec.currentPos.x, posRec.currentPos.y, posRec.currentPos.z);

	Vector3D spawnPos = vector3d(
		0 - posRec.currentPos.x, 0 - posRec.currentPos.y, 0 - posRec.currentPos.z
	);

	SJString *keyStr;
	char *key;
	int offset;

	if (fileWasLoaded == 1)
	{
		offset = 0;
		//slog("SPAWN ENTITY FILE WAS LOADED");
		keyStr = sj_string_new_integer(entityNum + offset);
		key = sj_string_get_text(keyStr);
		WriteJSON(key, lastEntityName, spawnPos, 0, entityNum + offset);
	}
	else
	{
		//slog("SPAWN ENTITY FILE WAS NOT LOADED");
		keyStr = sj_string_new_integer(entityNum);
		key = sj_string_get_text(keyStr);
		WriteJSON(key, lastEntityName, spawnPos, 0, entityNum);
	}

	lastSpawnedEntity = CreateEntity(lastEntityName, 1, spawnPos);
	lastSpawnedEntity->jsonKey = key;
	//slog("entity num: %i", entityNum + offset);
	lastSpawnedEntity->entityNum = entityNum + offset;
	lastSpawnedEntity->entityName = lastEntityName;
	lastSpawnedEntity->lastPos = spawnPos;


	/*SJString *file = sj_object_to_json_string(jsonFile);
	char *fileText = sj_string_get_text(file);
	slog(fileText);*/
	sj_save(jsonFile, "Level1.json");
}

void SpawnEntityAtPos(char* entityName, Vector3D spawnPos, int entNum)
{
	//slog("%s was loaded", entityName);

	lastSpawnedEntity = CreateEntity(entityName, 1, spawnPos);
	lastSpawnedEntity->entityName = entityName;
	lastSpawnedEntity->entityNum = entNum;
}


void DestroyEntity()
{
	if (posRec.lastEntityLocked == 1)
	{
		FreeEntity(lastSpawnedEntity);
		posRec.lastEntityLocked = 0;
		slog("entity destroyed");
	}
}