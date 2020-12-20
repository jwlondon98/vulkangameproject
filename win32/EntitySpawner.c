#include "EntitySpawner.h"

void SelectEntity(int index)
{
	switch (index)
	{
		case 1:
			lastEntityName = "wall2";
			break;
		case 2:
			lastEntityName = "trigger";
			break;
	}
}

void SpawnEntity(int useLastEntityTransform)
{
	slog("hi");

	posRec.lastEntityLocked = 0;

	if (!jsonFile)
	{
		slog("NO JSON FILE. CREATING ONE.");
		CreateJSONFile();
		entityNum = 0;
	}

	if (!lastEntityName)
		lastEntityName = "wall2";

	if (lastSpawnedEntity)
	{
		jsonIndex = lastSpawnedEntity->jsonIndex + 6;
	}

	//slog("%s spawned at (%f, %f, %f)", 
		//lastEntityName, posRec.currentPos.x, posRec.currentPos.y, posRec.currentPos.z);

	Vector3D spawnPos;
	Vector3D spawnRot;
	if (useLastEntityTransform == 0)
	{
		spawnPos = vector3d(
			0 - posRec.currentPos.x, 0 - posRec.currentPos.y, 0 - posRec.currentPos.z);
		spawnRot = vector3d(0, 0, 0);
	}
	else
	{
		spawnPos = lastSpawnedEntity->lastPos;
		spawnRot = lastSpawnedEntity->lastRot;
	}

	SJString *keyStr;
	char *key;

	if (fileWasLoaded == 1)
	{
		//slog("SPAWN ENTITY FILE WAS LOADED");
		keyStr = sj_string_new_integer(entityNum);
		key = sj_string_get_text(keyStr);
		WriteJSON(key, lastEntityName, spawnPos, lastSpawnedEntity->lastRot, 0, entityNum);
		entityNum++;
	}
	else
	{

		//slog("SPAWN ENTITY FILE WAS NOT LOADED");
		keyStr = sj_string_new_integer(entityNum);
		key = sj_string_get_text(keyStr);
		WriteJSON(key, lastEntityName, spawnPos, vector3d(0, 0, 0), 0, entityNum);
		entityNum++;
	}

	if (lastEntityName == "trigger")
		lastSpawnedEntity = CreateTrigger(spawnPos, spawnRot);
	else
		lastSpawnedEntity = CreateEntity(lastEntityName, 1, spawnPos, spawnRot);
	lastSpawnedEntity->jsonKey = key;
	lastSpawnedEntity->jsonIndex = jsonIndex;
	//slog("entity num: %i", entityNum + offset);
	lastSpawnedEntity->entityNum = entityNum;
	lastSpawnedEntity->entityName = lastEntityName;
	lastSpawnedEntity->lastPos = spawnPos;
	lastSpawnedEntity->lastRot = spawnRot;


	/*SJString *file = sj_object_to_json_string(jsonFile);
	char *fileText = sj_string_get_text(file);
	slog(fileText);*/
	sj_save(jsonFile, "Level1.json");
}

void SpawnEntityAtPos(char* entityName, Vector3D spawnPos, Vector3D rot, int entNum, int jIndex)
{
	if (strcmp(entityName, "trigger") == 0)
		lastSpawnedEntity = CreateTrigger(spawnPos, rot);
	else
		lastSpawnedEntity = CreateEntity(entityName, 1, spawnPos, rot);
	lastSpawnedEntity->entityName = entityName;
	lastSpawnedEntity->entityNum = entNum;
	lastSpawnedEntity->jsonIndex = jIndex;
	jsonIndex = jIndex;
	entityNum++;
}

void DuplicateEntity()
{
	SpawnEntity(1);
}

void DestroyEntity()
{
	return;

	if (posRec.lastEntityLocked == 1 && lastSpawnedEntity)
	{
		sj_list_delete_last(jsonFile->v.array);
		//sj_list_delete_nth(jsonFile->v.array, lastSpawnedEntity->entityNum);
		sj_save(jsonFile, "Level1.json");
		FreeEntity(lastSpawnedEntity);
		posRec.lastEntityLocked = 0;
		lastSpawnedEntity = NULL;
		slog("entity destroyed");
	}
}

void ClearJSONFile()
{
	Entity *ents = GetEntityList();
	int entCount = GetEntityCount();

	Entity *trigs = GetTriggerList();
	int trigCount = GetTriggerCount();

	int i;
	for (i = 0; i < entCount; i++)
		FreeEntity(&ents[i]);

	for (i = 0; i < trigCount; i++)
		FreeTrigger(&trigs[i]);

	CreateJSONFile();
	entityNum = 0;
}