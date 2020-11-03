#ifndef __GF3D_ENTITY_H__
#define __GF3D_ENTITY_H__

#include "gfc_types.h"
#include "gf3d_model.h"

typedef struct Entity_S
{
	Uint8			_inUse;
	Vector3D		pos;
	Model			*model;

	//void (Think*)(struct Entity_S *self);
}Entity;

//void Think(struct Entity_S *self);

void InitEntity(Uint32 maxEntities);
Entity* CreateEntity();
void CloseEntity();
void FreeEntity();

#endif