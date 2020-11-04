#ifndef __GF3D_ENTITY_H__
#define __GF3D_ENTITY_H__

#include "gfc_types.h"
#include "gf3d_model.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

typedef struct Entity_S
{
	Uint8			_inUse;
	Vector3D		lastPos;
	Vector3D		currentPos;
	Model			*model;
	Matrix4			modelMatrix;

	//void (Think*)(struct Entity_S *self);
}Entity;

//void Think(struct Entity_S *self);

void InitEntity(Uint32 maxEntities);
Entity* CreateEntity(char* modelName);
void CloseEntity();
void FreeEntity(Entity* entity);

Entity* GetEntityList();
int GetEntityCount();
void MoveToPos(Matrix4 matrix, Vector3D targetPos);

#endif