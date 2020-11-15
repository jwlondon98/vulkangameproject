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

typedef enum 
{
	WAIT, MOVE, ATTACK
}State;

typedef enum
{
	Target, EnemyBasic, EnemyAdvanced, Hostage, WeaponDrop, Gun
}EntityType;

typedef struct DelayData_S 
{
	float delayLength;
}DelayData;

typedef struct Entity_S
{
	Uint8			_inUse;
	Vector3D		lastPos;
	Model			*model;
	Matrix4			modelMatrix;
	int				renderOn;

	float			speed;

	State			state;
	int				targetX;
	int				targetZ;

	EntityType		entityType;

	Collider*		collider;

	//void (Think*)(struct Entity_S *self);
}Entity;

//void Think(struct Entity_S *self);

void InitEntity(Uint32 maxEntities);
Entity* CreateEntity(char* modelName, int render, Vector3D spawnPos);
void CloseEntity();
void FreeEntity(Entity* entity);

Entity* GetEntityList();
int GetEntityCount();
void Think(Entity* entity);
void MoveEntity(Entity* entity);

void Delay(float sec);
void InitRandom();
int GetRandomNum(int min, int max);

void RandomEntitySpawn();

static int DelayEntityCreation(void *data);

#endif