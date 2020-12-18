#include "Entity.h"
#include "simple_logger.h"

typedef struct
{
	Entity		*entityList;		/* list of entities */
	Uint32		entityCount;		/* numer of current active entities */

	GameMode	gameMode;
}EntityManager;

static EntityManager entityManager = {0};

/*
	@brief Initializes an entity
*/
void InitEntity(Uint32 maxEntities, GameMode gm)
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
	entityManager.gameMode = gm;
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
			slog("entity %s spawned", modelName);
			slog("\nspawn pos: (%f, %f, %f)", spawnPos.x,
				spawnPos.y, spawnPos.z);

			entityManager.entityList[i]._inUse = 1;

			if (render == 1)
				entityManager.entityList[i].renderOn = 1;
			else
				entityManager.entityList[i].renderOn = 0;

			if (modelName != "player")
				entityManager.entityList[i].model = gf3d_model_load(modelName);
			else 
				entityManager.entityList[i].model = gf3d_model_load("cube");

			// assign entity type based on model name
			if (modelName == "enemy1")
			{
				entityManager.entityList[i].entityType = EnemyBasic;
				//slog("enemy basic spawned");
			}
			else if (modelName == "enemy2")
			{
				entityManager.entityList[i].entityType = EnemyAdvanced;
				//slog("enemy advanced spawned");
			}
			else if (modelName == "target")
			{
				entityManager.entityList[i].entityType = Target;
				//slog("target spawned");
			
			}
			else if (modelName == "hostage")
			{
				entityManager.entityList[i].entityType = Hostage;
				//slog("hostage spawned");
			}
			else if (modelName == "weapondrop")
			{
				entityManager.entityList[i].entityType = WeaponDrop;
				//slog("weapondrop spawned");
			}
			else
			{
				entityManager.entityList[i].entityType = None;
			}

			// CAN THINK SET HERE -- CHANGE TO 0 to stop thinking for all entities
			//entityManager.entityList[i].canThink = 1;

			if (modelName != "gun")
				entityManager.entityList[i].state = MOVE;

			if (modelName == "enemy2")
			{
				entityManager.entityList[i].state = WAIT;
				spawnPos.y = -35;
			}

			if (modelName == "player" || modelName == "wall" || modelName == "wall2")
			{
				entityManager.entityList[i].state = NONE;
				entityManager.entityList[i].canThink = 0;
			}

			// set entity lane
			int lane;
			if (spawnPos.x == 10.0)
				lane = -1;
			else if (spawnPos.x == 0.0)
				lane = 0;
			else if (spawnPos.x == -10.0)
				lane = 1;
			entityManager.entityList[i].lane = lane;

			if (modelName == "hostage")
			{
				//slog("HOSTAGE SPAWN POSX: %f", spawnPos.x);
				//slog("HOSTAGE LANE: %i", lane);
				spawnPos.x = spawnPos.x + 2;
			}

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

	entity->_inUse = 0;
	entity->renderOn = 0;

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
	{
		Delay(2, EnemyBullet, entity);
		//entity->state = NONE;
		return;
	}
	else if (entity->state == MOVE)
	{
		MoveEntity(entity);
		return;
	}
	else if (entity->state == ATTACK)
	{
		// enemy shoot
		//EnemyShoot(entity->lastPos);
		//slog("enemy attacking");

		// set state back to waiting 
		//entity->state = WAIT;
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
		if (entity->entityType == Hostage && entity->state == MOVE)
			AddScore(&entityManager.entityList[0], 60);
		else if (entity->entityType == EnemyBasic || entity->entityType == EnemyAdvanced)
			AddScore(&entityManager.entityList[0], -40);

		FreeEntity(entity);

		Delay(1, EntityCreate, NULL);
	}
}

static int DelayEntityCreation(void *data)
{
	DelayData *delayData = data;
	float sec = delayData->delayLength;

	SDL_Delay(sec);

	RandomEntitySpawn();

	return 1;
}

static int DelayEnemyBullet(void *data)
{
	DelayData *delayData = data;
	float sec = delayData->delayLength;
	Entity* ent = delayData->entity;

	SDL_Delay(sec);

	ent->state = ATTACK;

	return 1;
}

static int DelayHostageDeath(void *data)
{
	DelayData *delayData = data;
	Entity* ent = delayData->entity;

	AddScore(&entityManager.entityList[0], -40);

	// free entity
	ent->_inUse = 0;
	ent->renderOn = 0;

	FreeEntity(&ent);
	// delay and spawn new entity
	Delay(2, EntityCreate, &ent);
}

void Delay(float sec, DelayType delayType, Entity* entity)
{
	DelayData* delayData = malloc(sizeof(DelayData));
	delayData->delayLength = sec * 1000;

	SDL_Thread *thread;
	if (delayType == EntityCreate)
	{
		RandomEntitySpawn();
		//thread = SDL_CreateThread(DelayEntityCreation, "DelayEntityCreation", delayData);
	}
	else if (delayType == EnemyBullet)
	{
		delayData->delayLength = 1000;
		delayData->entity = entity;
		entity->state = ATTACK;
		//thread = SDL_CreateThread(DelayEnemyBullet, "DelayEnemyBullet", delayData);
	}
	else if (delayType == HostageDeath)
	{
		delayData->delayLength = 5000;
		delayData->entity = entity;
		//thread = SDL_CreateThread(DelayHostageDeath, "DelayHostageDeath", delayData);
	}
}

void RandomEntitySpawn()
{
	//slog("RANDOM ENTITY SPAWN");

	InitRandom();

	int randEntity = GetRandomNum(0, 5);
	int randTrack = GetRandomNum(0, 2);

	//slog("RANDOM ENTITY: %i", randEntity);

	float spawnPosX;
	if (randTrack == 0)
		spawnPosX = -10;
	else if (randTrack == 1)
		spawnPosX = 0;
	else if (randTrack == 2)
		spawnPosX = 10;

	//switch (randEntity)
	//{
		/*case 0:
			CreateEntity("enemy1", 1, vector3d(spawnPosX, -50, 0));
			break;
		case 1:
			CreateEntity("enemy2", 1, vector3d(spawnPosX, -50, 0));
			break;
		case 2:
			CreateEntity("hostage", 1, vector3d(spawnPosX, -50, 0));
			break;
		case 3:
			CreateEntity("weapondrop", 1, vector3d(spawnPosX, -50, 0));
			break;
		case 4:
			CreateEntity("target", 1, vector3d(spawnPosX, -50, 0));
			break;
		default:
			CreateEntity("enemy1", 1, vector3d(spawnPosX, -50, 0));
			break;*/
	//}
}

void InitRandom()
{
	srand(time(NULL));
}

int GetRandomNum(int min, int max)
{
	return rand() % (max - min) + min;
}

float GetRandomFloat(float min, float max)
{
	return (float)(rand()) / (float)((RAND_MAX)) * max;
}

void AddScore(Entity* entity, int amt)
{
	entity->score += amt;
	slog("PLAYER SCORE: %i", entity->score);
}