#include "TextFileHandler.h"

void CreateJSONFile()
{
	jsonFile = sj_object_new();
}

void WriteJSON(char* key, char* entityType, Vector3D vect, int insert, int keyVal)
{
	SJString *str1 = sj_string_new_text(entityType);
	SJString *paren = sj_string_new_text(" (");
	SJString *vectStrX = sj_string_new_float(vect.x);
	SJString *str2 = sj_string_new_text(", ");
	SJString *vectStrY = sj_string_new_float(vect.y);
	SJString *vectStrZ = sj_string_new_float(vect.z);
	SJString *endStr = sj_string_new_text(")");

	SJString *realKeyStr = sj_string_new_text(key);
	int realKeyVal = sj_string_as_integer(realKeyStr);

	sj_string_concat(str1, paren);
	sj_string_concat(str1, vectStrX);
	sj_string_concat(str1, str2);
	sj_string_concat(str1, vectStrY);
	sj_string_concat(str1, str2);
	sj_string_concat(str1, vectStrZ);
	sj_string_concat(str1, endStr);

	char *vectStr = sj_string_get_text(str1);

	//slog("KEYSTR: %s, KEYVAL %i", key, keyVal);

	if (insert == 1)
		sj_object_update_object(jsonFile, key, sj_new_str(vectStr), keyVal);
	else
		sj_object_insert(jsonFile, key, sj_new_str(vectStr));

	SJString *file = sj_object_to_json_string(jsonFile);
	char *fileText = sj_string_get_text(file);
	slog(fileText);
}

void LoadJSON()
{
	jsonFile = sj_load("Level1.json");
	SJson *tempFile = sj_copy(jsonFile);
	fileWasLoaded = 1;

	SJString* jsonStr = sj_object_to_json_string(jsonFile);
	SJList* jsonList = jsonFile->v.array;
	int numElements = sj_list_get_count(jsonList);
	char *text = sj_string_get_text(jsonStr);

	char* entityName;
	char* xValStr;
	char* yValStr;
	char* zValStr;

	SJString *xJStr;
	SJString *yJStr;
	SJString *zJStr;

	float xVal;
	float yVal;
	float zVal;

	int i;
	char *valueStr;
	SJString *keyStr;
	char *splitStr;

	for (i = 0; i < numElements; i++)
	{
		keyStr = sj_string_new_integer(i);
		valueStr = sj_object_get_value_as_string(jsonFile, sj_string_get_text(keyStr));
		//slog("VALUE: %s", valueStr);

		// split for entity name
		splitStr = strtok(valueStr, " ");
		entityName = splitStr;
		//printf("%s\n", entityName);

		// split for xVal
		splitStr = strtok(NULL, " ");
		xValStr = splitStr;
		xValStr++[strlen(xValStr) - 1] = 0;
		//printf("%s\n", xValStr);

		// split for yVal
		splitStr = strtok(NULL, " ");
		yValStr = splitStr;
		yValStr[strlen(yValStr) - 1] = 0;
		//printf("%s\n", yValStr);

		// split for zVal
		splitStr = strtok(NULL, " ");
		zValStr = splitStr;
		zValStr[strlen(zValStr) - 1] = 0;
		//printf("%s\n", zValStr);

		// Convert vals to floats
		xJStr = sj_string_new_text(xValStr);
		yJStr = sj_string_new_text(yValStr);
		zJStr = sj_string_new_text(zValStr);
		xVal = sj_string_as_float(xJStr);
		yVal = sj_string_as_float(yJStr);
		zVal = sj_string_as_float(zJStr);

		entityNum = i;
		/*slog("entity num: %i", entityNum);

		slog("xVal: %f", xVal);
		slog("yVal: %f", yVal);
		slog("zVal: %f", zVal);*/

		// Spawn
		SpawnEntityAtPos(valueStr, vector3d(xVal, yVal, zVal), entityNum);
	}

	jsonFile = tempFile;
	SJString *file = sj_object_to_json_string(jsonFile);
	char *fileText = sj_string_get_text(file);
	slog(fileText);
	slog("All entites loaded from file.");
}
