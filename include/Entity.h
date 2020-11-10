#ifndef __GF3D_ENTITY_H__
#define __GF3D_ENTITY_H__

#include "gfc_types.h"
#include "gf3d_model.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../win32//Collider.h"

typedef enum 
{
	WAIT, APPEAR, ATTACK, ATTACKWAIT, DEAD
}State;

typedef struct Entity_S
{
	Uint8			_inUse;
	Vector3D		lastPos;
	Model			*model;
	Matrix4			modelMatrix;
	int				renderOn;

	Collider*		collider;

	State			state;
	int				targetX;
	int				targetZ;

	//void (Think*)(struct Entity_S *self);
}Entity;

//void Think(struct Entity_S *self);

void InitEntity(Uint32 maxEntities);
Entity* CreateEntity(char* modelName);
void CloseEntity();
void FreeEntity(Entity* entity);

Entity* GetEntityList();
int GetEntityCount();
void Think(Entity* entity);
void Step(Entity* entity, Vector3D targetPos, float speed);

void Delay(float sec);
void InitRandom();
int GetRandomNum(int min, int max);


#endif