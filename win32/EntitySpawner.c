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
		case 3:
			lastEntityName = "enemy3";
			break;
		case 4:
			lastEntityName = "boss";
			break;
	}
}

void SpawnEntity(int useLastEntityTransform)
{
	if (gameMode == Game)
		return;

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
		WriteJSON(key, lastEntityName, spawnPos, vector3d(0,0,0), 0, entityNum);
	}
	else
	{

		//slog("SPAWN ENTITY FILE WAS NOT LOADED");
		keyStr = sj_string_new_integer(entityNum);
		key = sj_string_get_text(keyStr);
		WriteJSON(key, lastEntityName, spawnPos, vector3d(0, 0, 0), 0, entityNum);
	}

	if (strcmp(lastEntityName, "trigger") == 0)
		lastSpawnedEntity = CreateTrigger(spawnPos, spawnRot);
	else
		lastSpawnedEntity = CreateEntity(lastEntityName, 1, spawnPos, spawnRot);

	if (lastSpawnedEntity)
		slog("trigger found");
	else
	{
		slog("trigger not found");
		return;
	}

	lastSpawnedEntity->jsonKey = key;
	lastSpawnedEntity->jsonIndex = jsonIndex;
	//slog("entity num: %i", entityNum + offset);
	lastSpawnedEntity->entityNum = entityNum;
	lastSpawnedEntity->entityName = lastEntityName;
	lastSpawnedEntity->lastPos = spawnPos;
	lastSpawnedEntity->lastRot = spawnRot;

	// set model's position to world origin
	gfc_matrix_identity(lastSpawnedEntity->modelMatrix);
	gfc_matrix_make_translation(
		lastSpawnedEntity->modelMatrix,
		spawnPos
	);
	lastSpawnedEntity->lastPos = spawnPos;

	// rotate entity
	RotateEntity(lastSpawnedEntity, spawnRot);
	lastSpawnedEntity->lastRot = spawnRot;

	entityNum++;

	slog("End Spawn Entity");

	/*SJString *file = sj_object_to_json_string(jsonFile);
	char *fileText = sj_string_get_text(file);
	slog(fileText);*/
}

void SpawnEntityAtPos(char* entityName, Vector3D spawnPos, Vector3D rot, int entNum, int jIndex)
{
	if (strcmp(entityName, "trigger") == 0)
		lastSpawnedEntity = CreateTrigger(spawnPos, rot);
	else if (strcmp(entityName, "enemy3") == 0 || strcmp(entityName, "boss") == 0)
		lastSpawnedEntity = CreateAnimatedEntity(entityName, 1, spawnPos, rot, 1, 30, 0.05);
	else
		lastSpawnedEntity = CreateEntity(entityName, 1, spawnPos, rot);
	lastSpawnedEntity->entityName = entityName;
	lastSpawnedEntity->entityNum = entNum;
	lastSpawnedEntity->jsonIndex = jIndex;

	if (strcmp(entityName, "enemy3") == 0)
	{
		AddEnemyToCamSeqController(lastSpawnedEntity, 20);
		lastSpawnedEntity->ticks = 6 * 1000;
	}
	else if (strcmp(entityName, "boss") == 0)
	{
		AddEnemyToCamSeqController(lastSpawnedEntity, 50);
		lastSpawnedEntity->ticks = 8 * 1000;
	}

	// set model's position to world origin
	gfc_matrix_identity(lastSpawnedEntity->modelMatrix);
	gfc_matrix_make_translation(
		lastSpawnedEntity->modelMatrix,
		spawnPos
	);
	lastSpawnedEntity->lastPos = spawnPos;

	// rotate entity
	RotateEntity(lastSpawnedEntity, rot);
	lastSpawnedEntity->lastRot = rot;

	jsonIndex = jIndex;
	entityNum++;
}

void RotateEntity(Entity *ent, Vector3D rot)
{
	gf3d_vgraphics_rotate_entityByVect(ent, vector3d(rot.x, rot.y, rot.z));
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