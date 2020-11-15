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
Entity *CreateEntity(char* modelName, int render, Vector3D spawnPos)
{
	int i;
	for (i = 0; i < entityManager.entityCount; i++)
	{
		if (!entityManager.entityList[i]._inUse)
		{
			slog("\nspawn pos%i: (%f, %f, %f)", i, spawnPos.x,
				spawnPos.y, spawnPos.z);

			entityManager.entityList[i]._inUse = 1;

			if (render == 1)
				entityManager.entityList[i].renderOn = 1;
			else
				entityManager.entityList[i].renderOn = 0;

			entityManager.entityList[i].model = gf3d_model_load(modelName);


			// create a collider for the entity
			entityManager.entityList[i].collider = CreateCollider();
			entityManager.entityList[i].collider->extents = vector3d(1, 1, 1);

			entityManager.entityList[i].speed = 0.5;

			// set model's position to world origin
			gfc_matrix_identity(entityManager.entityList[i].modelMatrix);

			gfc_matrix_make_translation(
				entityManager.entityList[i].modelMatrix,
				spawnPos
			);
			UpdateCollider(entityManager.entityList[i].collider, spawnPos);

			entityManager.entityList[i].lastPos = spawnPos;
			//entityManager.entityList[i].targetX = GetRandomNum(-50, 50);
			//entityManager.entityList[i].targetZ = GetRandomNum(-50, 50);

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
	MoveEntity(entity);

	if (entity->state == WAIT)
		return;
	else if (entity->state == APPEAR)
	{
		slog("STATE = ATTACK");
		entity->renderOn = 1;

		int i;
		/*for (i = 0; i < 20; i++)
			Step(entity, vector3d(1, 0, 0), .1);*/

		entity->state = ATTACK;
	}
	else if (entity->state == ATTACK)
	{
		//Delay(1);
		entity->state = APPEAR;
	}
}

void MoveEntity(Entity* entity)
{
	if (entity->_inUse == 0)
		return;

	Vector3D lastPos = entity->lastPos;

	float xPos = lastPos.x;
	float yPos = lastPos.y + entity->speed;
	float zPos = lastPos.z + entity->speed;

	gfc_matrix_make_translation(
		entity->modelMatrix,
		vector3d(xPos, yPos, 0)
	);

	entity->lastPos = vector3d(xPos, yPos, 0);

	UpdateCollider(entity->collider, entity->lastPos);

	if (yPos >= 50)
	{
		entity->renderOn = 0;
		entity->_inUse = 0;

		Delay();
	}
}

static int DelayEntityCreation(void *ptr, float sec)
{
	SDL_Delay(sec);

	CreateEntity("enemy", 1, vector3d(0, -50, 0));
}

void Delay(float sec)
{
	// Converting time into milli_seconds 
	float milli_seconds = 1000 * sec;

	SDL_Thread *thread;
	thread = SDL_CreateThread(DelayEntityCreation, "DelayEntityCreation", (void *)NULL, milli_seconds);
}

void RandomEntitySpawn()
{

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