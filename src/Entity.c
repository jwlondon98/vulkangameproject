#include "Entity.h"
#include "simple_logger.h"

typedef struct
{
	Entity		*entityList;		/* list of entities */
	Uint32		entityCount;		/* numer of current active entities */

}EntityManager;

static EntityManager entityManager = {0};

/*
	@brief Initializes an entity
*/
void InitEntity(Uint32 maxEntities)
{
	if (entityManager.entityList != NULL)
	{
		slog("WARNING: entity system already initialized");
		return;
	}

	// allocate memory 
	entityManager.entityList = gfc_allocate_array(sizeof(Entity), maxEntities);
	if (!entityManager.entityList)
	{
		slog("failed to allocate memory for entity list");
		return;
	}

	entityManager.entityCount = maxEntities;
	atexit(CloseEntity);
	slog("Entity System intiialized");
}

/*
	@brief Creates a new entity 
*/
Entity *CreateEntity(char* modelName)
{
	int i;
	for (i = 0; i < entityManager.entityCount; i++)
	{
		if (!entityManager.entityList[i]._inUse)
		{
			entityManager.entityList[i]._inUse = 1;

			entityManager.entityList[i].model = gf3d_model_load(modelName);

			// set model's position to world origin
			gfc_matrix_identity(entityManager.entityList[i].modelMatrix);

			gfc_matrix_make_translation(
				entityManager.entityList[i].modelMatrix,
				vector3d(0, 0, 0)
			);

			entityManager.entityList[i].lastPos = vector3d(0, 0, 0);
			entityManager.entityList[i].currentPos = vector3d(0, 0, 0);

			return &entityManager.entityList[i];
		}
	}

	slog ("Failed to create new entity, no unused slots");
	return NULL;
}

void CloseEntity()
{
	int i;
	if (entityManager.entityList != NULL)
	{
		for (i = 0; i < entityManager.entityCount; i++)
		{
			FreeEntity(&entityManager.entityList[i]);
		}
		free(entityManager.entityList);
	}

	memset(&entityManager, 0, sizeof(EntityManager));
	slog("Entity System closed");
}

void FreeEntity(Entity *entity)
{
	if (!entity) return;

	gf3d_model_free(entity->model);
	memset(entity, 0, sizeof(Entity));
;}


Entity* GetEntityList()
{
	return entityManager.entityList;
}

int GetEntityCount()
{
	return entityManager.entityCount;
}

void MoveToPos(Entity* entity, Vector3D targetPos)
{
	Vector3D lastPos = entity->lastPos;
	Vector3D currentPos = entity->currentPos;
	
	entity->lastPos = currentPos;

	gfc_matrix_make_translation(
		entity->modelMatrix,
		vector3d(targetPos.x - currentPos.x, targetPos.y - currentPos.y, targetPos.z - currentPos.z)
	);

	entity->currentPos = targetPos;
}