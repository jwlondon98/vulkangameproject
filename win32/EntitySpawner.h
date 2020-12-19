#ifndef __ENTITYSELECTOR_H__
#define __ENTITYSELECTOR_H__

#include "Entity.h"
#include "PositionRecorder.h"
#include "TextFileHandler.h"
#include <simple_logger.h>
#include "CameraSequenceController.h"


char* lastEntityName;
int entityNum;
Entity* lastSpawnedEntity;


void SelectEntity(int index);
void SpawnEntity(int useLastEntityTransform);
void SpawnEntityAtPos(char* entityName, Vector3D spawnPos, Vector3D rot, int entNum);
void DuplicateEntity();

void DestroyEntity();
void ClearJSONFile();
//typedef void(*SpawnSpecificEntity)(char*, Vector3D);
//extern void SpawnSpecificEntity(char* entityName, Vector3D spawnPos);

#endif