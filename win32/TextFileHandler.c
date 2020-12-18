#include "TextFileHandler.h"

void CreateJSONFile()
{
	jsonFile = sj_object_new();
}

void WriteJSON(char* key, char* entityType, Vector3D vect, Vector3D rot, int insert, int keyVal)
{
	// wall2 (0.000000, 0.000000, 0.000000), (0.000000, 0.000000, 0.000000)

	// helpers
	SJString *str1 = sj_string_new_text(entityType);
	SJString *paren = sj_string_new_text(" (");
	SJString *parenNoSpace = sj_string_new_text("(");
	SJString *str2 = sj_string_new_text(", ");
	SJString *endStr = sj_string_new_text(")");

	// pos strings
	SJString *vectStrX = sj_string_new_float(vect.x);
	SJString *vectStrY = sj_string_new_float(vect.y);
	SJString *vectStrZ = sj_string_new_float(vect.z);

	// rot strings
	SJString *rotStrX = sj_string_new_float(rot.x);
	SJString *rotStrY = sj_string_new_float(rot.y);
	SJString *rotStrZ = sj_string_new_float(rot.z);

	// key string
	SJString *realKeyStr = sj_string_new_text(key);
	int realKeyVal = sj_string_as_integer(realKeyStr);

	// concat strings
	sj_string_concat(str1, paren);			// wall2 (
	sj_string_concat(str1, vectStrX);		// 0.000000
	sj_string_concat(str1, str2);			// , 
	sj_string_concat(str1, vectStrY);		// 0.000000
	sj_string_concat(str1, str2);			// ,
	sj_string_concat(str1, vectStrZ);		// 0.000000
	sj_string_concat(str1, endStr);			//)
	sj_string_concat(str1, str2);			// ,
	sj_string_concat(str1, parenNoSpace);	// (
	sj_string_concat(str1, rotStrX);		// 0.000000
	sj_string_concat(str1, str2);			// , 
	sj_string_concat(str1, rotStrY);		// 0.000000
	sj_string_concat(str1, str2);			// ,
	sj_string_concat(str1, rotStrZ);		// 0.000000
	sj_string_concat(str1, endStr);			//)

	char *vectStr = sj_string_get_text(str1);

	//slog("KEYSTR: %s, KEYVAL %i", key, keyVal);

	if (insert == 1)
		sj_object_update_object(jsonFile, key, sj_new_str(vectStr), keyVal);
	else
		sj_object_insert(jsonFile, key, sj_new_str(vectStr));

	//SJString *file = sj_object_to_json_string(jsonFile);
	//char *fileText = sj_string_get_text(file);
	//slog(fileText);
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
	char* xRotStr;
	char* yRotStr;
	char* zRotStr;

	SJString *xJStr;
	SJString *yJStr;
	SJString *zJStr;
	SJString *xRotJStr;
	SJString *yRotJStr;
	SJString *zRotJStr;

	float xVal;
	float yVal;
	float zVal;
	float xRot;
	float yRot;
	float zRot;

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
		zValStr[strlen(zValStr) - 2] = 0;
		//printf("%s\n", zValStr);

		// wall2 (0.000000, 0.000000, 0.000000), (0.000000, 0.000000, 0.000000)

		// split for xRot
		splitStr = strtok(NULL, " ");
		xRotStr = splitStr;
		xRotStr++[strlen(xRotStr) - 1] = 0;
		//printf("%s\n", xRotStr);

		// split for yRot
		splitStr = strtok(NULL, " ");
		yRotStr = splitStr;
		yRotStr[strlen(yRotStr) - 1] = 0;
		//printf("%s\n", yRotStr);

		// split for zRot
		splitStr = strtok(NULL, " ");
		zRotStr = splitStr;
		zRotStr[strlen(zRotStr) - 1] = 0;
		//printf("%s\n", zRotStr);

		// Convert vals to floats
		xJStr = sj_string_new_text(xValStr);
		yJStr = sj_string_new_text(yValStr);
		zJStr = sj_string_new_text(zValStr);
		xRotJStr = sj_string_new_text(xRotStr);
		yRotJStr = sj_string_new_text(yRotStr);
		zRotJStr = sj_string_new_text(zRotStr);
		xVal = sj_string_as_float(xJStr);
		yVal = sj_string_as_float(yJStr);
		zVal = sj_string_as_float(zJStr);
		xRot = sj_string_as_float(xRotJStr);
		yRot = sj_string_as_float(yRotJStr);
		zRot = sj_string_as_float(zRotJStr);

		entityNum = i;
		/*slog("entity num: %i", entityNum);

		slog("xVal: %f", xVal);
		slog("yVal: %f", yVal);
		slog("zVal: %f", zVal);*/

		// Spawn
		SpawnEntityAtPos(
			valueStr, 
			vector3d(xVal, yVal, zVal), 
			vector3d(xRot, yRot, zRot), 
			entityNum);
	}

	jsonFile = tempFile;
	SJString *file = sj_object_to_json_string(jsonFile);
	char *fileText = sj_string_get_text(file);
	slog(fileText);
	slog("All entites loaded from file.");
}
