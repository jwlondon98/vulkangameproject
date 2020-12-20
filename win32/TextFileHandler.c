#include "TextFileHandler.h"

void CreateJSONFile()
{
	jsonFile = sj_object_new();
	sj_save(jsonFile, "Level1.json");
}

void WriteJSON(char* key, char* entityName, Vector3D pos, Vector3D rot, int update, int keyVal)
{
	// key string
	SJString *keyStr = sj_string_new_text(key);
	int realKeyVal = sj_string_as_integer(keyStr);

	// entity name
	SJString *entityNameStr = sj_string_new_text(entityName);

	// pos strings
	SJString *pStrX = sj_string_new_text("x");
	sj_string_concat(pStrX, keyStr);
	SJString *pStrY = sj_string_new_text("y");
	sj_string_concat(pStrY, keyStr);
	SJString *pStrZ = sj_string_new_text("z");
	sj_string_concat(pStrZ, keyStr);

	// rot strings
	SJString *rStrA = sj_string_new_text("a");
	sj_string_concat(rStrA, keyStr);
	SJString *rStrB = sj_string_new_text("b");
	sj_string_concat(rStrB, keyStr);
	SJString *rStrC = sj_string_new_text("c");
	sj_string_concat(rStrC, keyStr);

	// concat strings
	//sj_string_concat(str1, paren);			// wall2 (
	//sj_string_concat(str1, posStrX);		// 0.000000
	//sj_string_concat(str1, str2);			// , 
	//sj_string_concat(str1, posStrY);		// 0.000000
	//sj_string_concat(str1, str2);			// ,
	//sj_string_concat(str1, posStrZ);		// 0.000000
	//sj_string_concat(str1, endStr);			//)
	//sj_string_concat(str1, str2);			// ,
	//sj_string_concat(str1, parenNoSpace);	// (
	//sj_string_concat(str1, rotStrX);		// 0.000000
	//sj_string_concat(str1, str2);			// , 
	//sj_string_concat(str1, rotStrY);		// 0.000000
	//sj_string_concat(str1, str2);			// ,
	//sj_string_concat(str1, rotStrZ);		// 0.000000
	//sj_string_concat(str1, endStr);			//)

	char *entStr = sj_string_get_text(entityNameStr);

	//slog("KEYSTR: %s, KEYVAL %i", key, keyVal);

	if (update == 1)
	{
		//sj_object_update_object(jsonFile, key, sj_new_str(entStr), keyVal);
	
		// entity name
		sj_object_update_object(jsonFile, key, sj_new_str(entStr), keyVal);

		// pos
		sj_object_update_object(jsonFile, sj_string_get_text(pStrX), sj_new_float(pos.x), keyVal + 1); // x
		sj_object_update_object(jsonFile, sj_string_get_text(pStrY), sj_new_float(pos.y), keyVal + 2); // y
		sj_object_update_object(jsonFile, sj_string_get_text(pStrZ), sj_new_float(pos.z), keyVal + 3); // z

		// rot
		sj_object_update_object(jsonFile, sj_string_get_text(rStrA), sj_new_float(rot.x), keyVal + 4); // a
		sj_object_update_object(jsonFile, sj_string_get_text(rStrB), sj_new_float(rot.y), keyVal + 5); // b
		sj_object_update_object(jsonFile, sj_string_get_text(rStrC), sj_new_float(rot.z), keyVal + 6); // c
	}
	else
	{
		// entity name
		sj_object_insert(jsonFile, key, sj_new_str(entStr)); 

		// pos
		sj_object_insert(jsonFile, sj_string_get_text(pStrX), sj_new_float(pos.x)); // x
		sj_object_insert(jsonFile, sj_string_get_text(pStrY), sj_new_float(pos.y)); // y
		sj_object_insert(jsonFile, sj_string_get_text(pStrZ), sj_new_float(pos.z)); // z

		// rot
		sj_object_insert(jsonFile, sj_string_get_text(rStrA), sj_new_float(rot.x)); // a
		sj_object_insert(jsonFile, sj_string_get_text(rStrB), sj_new_float(rot.y)); // b
		sj_object_insert(jsonFile, sj_string_get_text(rStrC), sj_new_float(rot.z)); // c
	}

	SJString *file = sj_object_to_json_string(jsonFile);
	char *fileText = sj_string_get_text(file);
	slog(fileText);
}

void LoadJSON()
{
	slog("LOADING JSON");
	jsonFile = sj_load("Level1.json");
	if (jsonFile == NULL)
	{
		slog("JSON file empty or missing. Cannot load.");
		return;
	}

	SJson *tempFile = sj_copy(jsonFile);
	fileWasLoaded = 1;
	SJString* jsonStr = sj_object_to_json_string(jsonFile);
	SJList* jsonList = jsonFile->v.array;
	int numElements = sj_list_get_count(jsonList);

	float xPos;
	float yPos;
	float zPos;
	float aRot;
	float bRot;
	float cRot;

	char *entStr;
	
	SJString *keyStr;
	SJString *xStrKey;
	SJString *yStrKey;
	SJString *zStrKey;
	SJString *aStrKey;
	SJString *bStrKey;
	SJString *cStrKey;

	SJString *xStrVal;
	SJString *yStrVal;
	SJString *zStrVal;
	SJString *aStrVal;
	SJString *bStrVal;
	SJString *cStrVal;

	int jsonIndex;
	int i;
	slog("NUM ELEMENTS: %i", numElements);
	slog("NUM ELEMENTS / 7: %i", (numElements / 7));
	for (i = 0; i < (numElements / 7); i++)
	{
		slog("index: %i", i);
		jsonIndex = i * 6;

		keyStr = sj_string_new_integer(i);
		//slog("KEY STR: %s", sj_string_get_text(keyStr));
		entStr = sj_object_get_value_as_string(jsonFile, sj_string_get_text(keyStr));

		if (!entStr)
		{
			slog("ENT STR WAS NOT FOUND. STOPPING LOADING OF LEVEL FILE");
			return;
		}

		// concat keyStr with pos and rot strs
		xStrKey = sj_string_new_text("x");
		yStrKey = sj_string_new_text("y");
		zStrKey = sj_string_new_text("z");
		aStrKey = sj_string_new_text("a");
		bStrKey = sj_string_new_text("b");
		cStrKey = sj_string_new_text("c");
		sj_string_concat(xStrKey, keyStr);
		sj_string_concat(yStrKey, keyStr);
		sj_string_concat(zStrKey, keyStr);
		sj_string_concat(aStrKey, keyStr);
		sj_string_concat(bStrKey, keyStr);
		sj_string_concat(cStrKey, keyStr);

		// get pos and rot
		xPos = sj_string_as_float(sj_string_to_json_string(sj_object_get_value(jsonFile, sj_string_get_text(xStrKey))));
		yPos = sj_string_as_float(sj_string_to_json_string(sj_object_get_value(jsonFile, sj_string_get_text(yStrKey))));
		zPos = sj_string_as_float(sj_string_to_json_string(sj_object_get_value(jsonFile, sj_string_get_text(zStrKey))));
		aRot = sj_string_as_float(sj_string_to_json_string(sj_object_get_value(jsonFile, sj_string_get_text(aStrKey))));
		bRot = sj_string_as_float(sj_string_to_json_string(sj_object_get_value(jsonFile, sj_string_get_text(bStrKey))));
		cRot = sj_string_as_float(sj_string_to_json_string(sj_object_get_value(jsonFile, sj_string_get_text(cStrKey))));

		slog("Ent Str: %s", entStr);
		slog("X: %f", xPos);
		slog("Y: %f", yPos);
		slog("Z: %f", zPos);
		slog("Z: %f", aRot);
		slog("B: %f", bRot);
		slog("C: %f", cRot);

		// Spawn
		SpawnEntityAtPos(
			entStr, 
			vector3d(xPos, yPos, zPos), 
			vector3d(aRot, bRot, cRot), 
			entityNum, jsonIndex);
	}

	jsonFile = tempFile;
	SJString *file = sj_object_to_json_string(jsonFile);
	char *fileText = sj_string_get_text(file);
	slog(fileText);
	slog("All entites loaded from file.");
}
