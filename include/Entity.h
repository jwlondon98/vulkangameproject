#pragma once

#ifndef __GF3D_ENTITY_H__
#define __GF3D_ENTITY_H__

#include "gfc_types.h"
#include "gf3d_model.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_thread.h>
#include <SDL.h>
#include "Collider.h"
#include "Entity.h"
#include "simple_logger.h"
#include "GameStateManager.h"

typedef enum 
{
	WAIT, MOVE, ATTACK, NONE
}State;

typedef enum
{
	Target, EnemyBasic, EnemyAdvanced, Hostage, WeaponDrop, Gun, None
}EntityType;

typedef enum
{
	EntityCreate, EnemyBullet, HostageDeath, NoDelay
}DelayType;

typedef enum
{
	AnimWait, AnimPlay, AnimStop
}AnimState;

typedef struct Entity_S
{
	Uint8			_inUse;

	Vector3D		lastPos;
	Vector3D		targetPos;

	Vector3D		lastRot;
	Vector3D		targetRot;

	Model			*model;
	Matrix4			modelMatrix;
	int				renderOn;

	int				canThink;

	float			speed;

	State			state;
	int				targetX;
	int				targetZ;

	int				lane;
	int				score;

	EntityType		entityType;

	Collider*		collider;

	int				entityNum;
	char*			entityName;
	int				jsonIndex;
	char*			jsonKey;
	char*			jsonValue;

	int				isAnimated;
	int				startFrame;
	int				endFrame;
	int				currFrame;
	float			frameIncStart;
	float			frameInc;

	AnimState		currAnimState;
	AnimState		endAnimState;

	//void (Think*)(struct Entity_S *self);
}Entity;

typedef struct DelayData_S 
{
	float delayLength;
	Entity* entity;
}DelayData;

//void Think(struct Entity_S *self);

void InitEntity(Uint32 maxEntities, GameMode gameMode);
Entity* CreateEntity(char* modelName, int render, Vector3D spawnPos, Vector3D rot);
Entity* CreateAnimatedEntity(
	char* modelName, int render, Vector3D spawnPos, Vector3D rot, 
	int startFrame, int endFrame, float frameInc);
void CloseEntity();
void FreeEntity(Entity* entity);

Entity* GetEntityList();
Entity* GetLastAvailableEntity();
int GetEntityCount();
void MoveEntity(Entity* entity);
void Think(Entity* entity);

void Delay(float sec, DelayType delayType, Entity* entity);
void InitRandom();
int GetRandomNum(int min, int max);

void RandomEntitySpawn();

static int DelayEntityCreation(void *data);
static int DelayEnemyBullet(void *data);
static int DelayHostageDeath(void *data);

void AddScore(Entity* entity, int amt);

void ChangeAnimState(Entity* ent, AnimState aState);

void ChangeAnimStateAll(AnimState aState);

#endif