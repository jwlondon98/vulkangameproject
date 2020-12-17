#include "TextFileHandler.h"

void CreateJSONFile()
{
	jsonFile = sj_object_new();
}

void WriteJSONStr(char* key, char* value)
{
	sj_object_insert(jsonFile, key, sj_new_str(value));
}

void WriteJSONVect(char* key, Vector3D value)
{
	char str1[80];
	char str2[80];
	char str3[80];
	snprintf(str1, sizeof str1, "%s%s", key, "x");
	snprintf(str2, sizeof str2, "%s%s", key, "y");
	snprintf(str3, sizeof str3, "%s%s", key, "z");
	sj_object_insert(jsonFile, str1, sj_new_float(value.x));
	sj_object_insert(jsonFile, str2, sj_new_float(value.y));
	sj_object_insert(jsonFile, str3, sj_new_float(value.z));
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

	sj_string_concat(str1, paren);
	sj_string_concat(str1, vectStrX);
	sj_string_concat(str1, str2);
	sj_string_concat(str1, vectStrY);
	sj_string_concat(str1, str2);
	sj_string_concat(str1, vectStrZ);
	sj_string_concat(str1, endStr);

	char *vectStr = sj_string_get_text(str1);

	slog("KEYVAL: %i", keyVal);

	if (insert == 1)
		sj_object_insertByIndex(jsonFile, key, sj_new_str(vectStr), keyVal);
	else
		sj_object_insert(jsonFile, key, sj_new_str(vectStr));

}

void LoadJSON(void(*SpawnSpecificEntity)(char*, Vector3D))
{
	jsonFile = sj_load("Level1.json");

	SJString* jsonStr = sj_object_to_json_string(jsonFile);
	int i;
	char* key;
	char str[80];
	for (i = 0; i < 4; i++)
	{
		// Get entity name
		SJString* indexStr = sj_string_new_integer(i);
		key = sj_string_get_text(indexStr);
		char* entityName = sj_object_get_value_as_string(jsonFile, key);
		slog(entityName);

		// get x float val
		SJString* keyX= sj_string_new_text("x");
		SJString* xKey = indexStr;
		sj_string_concat(xKey, keyX);
		float xVal;
		sj_string_as_float(xKey, &xVal);

		// get y float val
		SJString* keyY = sj_string_new_text("y");
		SJString* yKey = indexStr;
		sj_string_concat(yKey, keyY);
		float yVal;
		sj_string_as_float(yKey, &yVal);

		// get z float val
		SJString* keyZ = sj_string_new_text("z");
		SJString* zKey = indexStr;
		sj_string_concat(zKey, keyZ);
		float zVal;
		sj_string_as_float(zKey, &zVal);

		//SpawnSpectificEntity(entityName, vector3d(xVal, yVal, zVal));
	}
}
