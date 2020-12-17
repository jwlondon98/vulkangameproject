#ifndef __TEXTFILEHANDLER_H__
#define __TEXTFILEHANDLER_H__

#include "../gfc/simple_json/include/simple_json.h"
#include "../gfc/include/gfc_vector.h"
#include "simple_logger.h"

SJson* jsonFile;

void CreateJSONFile();

void WriteJSONStr(char* key, char *value);

void WriteJSONVect(char* key, Vector3D value);

void LoadJSON(void(*SpawnSpecificEntity)(char*, Vector3D));

#endif