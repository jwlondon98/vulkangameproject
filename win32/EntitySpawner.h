#ifndef __ENTITYSELECTOR_H__
#define __ENTITYSELECTOR_H__

#include "Entity.h"
#include "PositionRecorder.h"
#include "TextFileHandler.h"
#include <simple_logger.h>


char* lastEntityName;
int entityNum;


void SelectEntity(int index);
void SpawnEntity();

typedef void(*SpawnSpecificEntity)(char*, Vector3D);
extern void SpawnSpecificEntity(char* entityName, Vector3D spawnPos);

#endif