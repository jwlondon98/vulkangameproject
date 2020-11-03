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
		slog ("WARNING: entity system already initialized");
		return;
	}

	// allocate memory 
	entityManager.entityList = gfc_allocate_array(sizeof(Entity), maxEntities);
	if (!entityManager.entityList)
	{
		slog ("failed to allocate memory for entity list");
		return;
	}

	entityManager.entityCount = maxEntities;
}

/*
	@brief Creates a new entity 
*/
Entity *CreateEntity()
{
	int i;
	for (i = 0; i < entityManager.entityCount; i++)
	{
		if (!entityManager.entityList[i]._inUse)
		{
			entityManager.entityList[i]._inUse = 1;
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
}

void FreeEntity(Entity *entity)
{
	if (!entity) return;

	/*gf3d_model_free(entity->model);
	entityManager.entityList[i]._inUse = 0;*/
;}