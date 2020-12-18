#ifndef __TEXTFILEHANDLER_H__
#define __TEXTFILEHANDLER_H__

#include "../gfc/simple_json/include/simple_json.h"
#include "../gfc/include/gfc_vector.h"
#include "simple_logger.h"
#include "EntitySpawner.h"

SJson* jsonFile;
int	 fileWasLoaded;

void CreateJSONFile();

void WriteJSON(char* key, char* entityType, Vector3D vect, Vector3D rot, int insert, int keyVal);

void LoadJSON();

#endif