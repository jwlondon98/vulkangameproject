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
			entityManager.entityList[i].renderOn = 1;

			entityManager.entityList[i].model = gf3d_model_load(modelName);

			// create a collider for the entity
			entityManager.entityList[i].collider = CreateCollider();
			entityManager.entityList[i].collider->extents = vector3d(1, 1, 1);
			entityManager.entityList[i].collider->Update(vector3d(0, 0, 0));

			// set model's position to world origin
			gfc_matrix_identity(entityManager.entityList[i].modelMatrix);

			gfc_matrix_make_translation(
				entityManager.entityList[i].modelMatrix,
				vector3d(0, 0, 0)
			);

			entityManager.entityList[i].lastPos = vector3d(0, 0, 0);
			entityManager.entityList[i].targetX = GetRandomNum(-50, 50);
			entityManager.entityList[i].targetZ = GetRandomNum(-50, 50);

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

void Think(Entity* entity)
{
	if (entity->state == WAIT)
		return;
	else if (entity->state == APPEAR)
	{
		slog("STATE = ATTACK");
		entity->renderOn = 1;

		int i;
		for (i = 0; i < 20; i++)
			Step(entity, vector3d(1, 0, 0), .1);

		entity->state = ATTACK;
	}
	else if (entity->state == ATTACK)
	{
		Delay(1);
		entity->state = APPEAR;
	}
}

void Step(Entity* entity, Vector3D targetPos, float speed)
{
	Vector3D lastPos = entity->lastPos;
	
	float xPos = targetPos.x + lastPos.x;
	float yPos = targetPos.y + lastPos.y;
	float zPos = targetPos.z + lastPos.z;

	gfc_matrix_make_translation(
		entity->modelMatrix,
		vector3d(xPos * speed, yPos * speed, zPos * speed)
	);

	entity->lastPos = vector3d(xPos, yPos, zPos);

	slog("move to pos: (%f ,%f, %f)", xPos, yPos, zPos);
}

void Delay(float sec)
{
	// Converting time into milli_seconds 
	float milli_seconds = 1000 * sec;

	// Storing start time 
	clock_t start_time = clock();

	// looping till required time is not achieved 
	while (clock() < start_time + milli_seconds);
}

void InitRandom()
{
	time_t t;
	srand((unsigned)time(&t));
}

int GetRandomNum(int min, int max)
{
	return ((rand() % (max - min + 1)) + min);
}