#ifndef __TEXTFILEHANDLER_H__
#define __TEXTFILEHANDLER_H__

#include "../gfc/simple_json/include/simple_json.h"
#include "../gfc/include/gfc_vector.h"
#include "simple_logger.h"
#include "EntitySpawner.h"

SJson* jsonFile;
int	 fileWasLoaded;

void CreateJSONFile();

void WriteJSON(char* key, char* entityType, Vector3D vect, Vector3D rot);
void AppendJSON(char* key, char* entityName, Vector3D pos, Vector3D rot, int index);

void LoadJSON();

#endif