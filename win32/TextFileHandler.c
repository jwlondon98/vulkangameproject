#include "TextFileHandler.h"

void CreateJSONFile()
{
	jsonFile = sj_object_new();
	sj_save(jsonFile, "Level1.json");
}

void WriteJSON(char* key, char* entityName, Vector3D pos, Vector3D rot)
{
	int newObj = 0;

	// key string
	SJson *parentArr = sj_object_get_value(jsonFile, "Level");
	if (sj_array_get_count(parentArr) == 0)
	{
		parentArr = sj_array_new();
		newObj = 1;
	}

	SJson *mainObj = sj_object_new();
	sj_object_insert(mainObj, "name", sj_new_str(entityName));

	// Position 
	SJson *posArr = sj_array_new();
	sj_array_append(posArr, sj_new_float(pos.x));
	sj_array_append(posArr, sj_new_float(pos.y));
	sj_array_append(posArr, sj_new_float(pos.z));
	sj_object_insert(mainObj, "pos", posArr);

	// Rotation 
	SJson *rotArr = sj_array_new();
	sj_array_append(rotArr, sj_new_float(rot.x));
	sj_array_append(rotArr, sj_new_float(rot.y));
	sj_array_append(rotArr, sj_new_float(rot.z));
	sj_object_insert(mainObj, "rot", rotArr);

	sj_array_append(parentArr, mainObj);
	if (newObj == 1)
		sj_object_insert(jsonFile, "Level", parentArr);
	
	sj_save(jsonFile, "Level1.json");

	slog("JSON WRITTEN");
}

void AppendJSON(char* key, char* entityName, Vector3D pos, Vector3D rot, int index)
{
	slog("APPENDING JSON..");
	//slog("ENTITY NUMBER: %i", index);

	// key string
	SJson *parentArr = sj_object_get_value(jsonFile, "Level");

	SJson *mainObj = sj_object_new();
	sj_object_insert(mainObj, "name", sj_new_str(entityName));

	// Position 
	SJson *posArr = sj_array_new();
	sj_array_append(posArr, sj_new_float(pos.x));
	sj_array_append(posArr, sj_new_float(pos.y));
	sj_array_append(posArr, sj_new_float(pos.z));
	sj_object_insert(mainObj, "pos", posArr);

	// Rotation 
	SJson *rotArr = sj_array_new();
	sj_array_append(rotArr, sj_new_float(rot.x));
	sj_array_append(rotArr, sj_new_float(rot.y));
	sj_array_append(rotArr, sj_new_float(rot.z));
	sj_object_insert(mainObj, "rot", rotArr);

	//sj_echo(parentArr);

	//parentArr->v.array = sj_list_delete_last(parentArr->v.array);
	sj_array_insert(parentArr, mainObj, index);

	//sj_echo(parentArr);

	//sj_object_update(parentArr, "pos", posArr, 1);
	//sj_object_update(parentArr, "rot", rotArr, 1);

	sj_save(jsonFile, "Level1.json");

	slog("JSON APPENDED");
}

//void WriteJSON(char* key, char* entityName, Vector3D pos, Vector3D rot, int update, int keyVal)
//{
//	// key string
//	SJString *keyStr = sj_string_new_text(key);
//	int realKeyVal = sj_string_as_integer(keyStr);
//
//	// entity name
//	SJString *entityNameStr = sj_string_new_text(entityName);
//
//	// pos strings
//	SJString *pStrX = sj_string_new_text("x");
//	sj_string_concat(pStrX, keyStr);
//	SJString *pStrY = sj_string_new_text("y");
//	sj_string_concat(pStrY, keyStr);
//	SJString *pStrZ = sj_string_new_text("z");
//	sj_string_concat(pStrZ, keyStr);
//
//	// rot strings
//	SJString *rStrA = sj_string_new_text("a");
//	sj_string_concat(rStrA, keyStr);
//	SJString *rStrB = sj_string_new_text("b");
//	sj_string_concat(rStrB, keyStr);
//	SJString *rStrC = sj_string_new_text("c");
//	sj_string_concat(rStrC, keyStr);
//
//	// concat strings
//	//sj_string_concat(str1, paren);			// wall2 (
//	//sj_string_concat(str1, posStrX);		// 0.000000
//	//sj_string_concat(str1, str2);			// , 
//	//sj_string_concat(str1, posStrY);		// 0.000000
//	//sj_string_concat(str1, str2);			// ,
//	//sj_string_concat(str1, posStrZ);		// 0.000000
//	//sj_string_concat(str1, endStr);			//)
//	//sj_string_concat(str1, str2);			// ,
//	//sj_string_concat(str1, parenNoSpace);	// (
//	//sj_string_concat(str1, rotStrX);		// 0.000000
//	//sj_string_concat(str1, str2);			// , 
//	//sj_string_concat(str1, rotStrY);		// 0.000000
//	//sj_string_concat(str1, str2);			// ,
//	//sj_string_concat(str1, rotStrZ);		// 0.000000
//	//sj_string_concat(str1, endStr);			//)
//
//	char *entStr = sj_string_get_text(entityNameStr);
//
//	//slog("KEYSTR: %s, KEYVAL %i", key, keyVal);
//
//	if (update == 1)
//	{
//		//sj_object_update_object(jsonFile, key, sj_new_str(entStr), keyVal);
//	
//		// entity name
//		sj_object_update_object(jsonFile, key, sj_new_str(entStr), keyVal);
//
//		// pos
//		sj_object_update_object(jsonFile, sj_string_get_text(pStrX), sj_new_float(pos.x), keyVal + 1); // x
//		sj_object_update_object(jsonFile, sj_string_get_text(pStrY), sj_new_float(pos.y), keyVal + 2); // y
//		sj_object_update_object(jsonFile, sj_string_get_text(pStrZ), sj_new_float(pos.z), keyVal + 3); // z
//
//		// rot
//		sj_object_update_object(jsonFile, sj_string_get_text(rStrA), sj_new_float(rot.x), keyVal + 4); // a
//		sj_object_update_object(jsonFile, sj_string_get_text(rStrB), sj_new_float(rot.y), keyVal + 5); // b
//		sj_object_update_object(jsonFile, sj_string_get_text(rStrC), sj_new_float(rot.z), keyVal + 6); // c
//	}
//	else
//	{
//		// entity name
//		sj_object_insert(jsonFile, key, sj_new_str(entStr)); 
//
//		// pos
//		sj_object_insert(jsonFile, sj_string_get_text(pStrX), sj_new_float(pos.x)); // x
//		sj_object_insert(jsonFile, sj_string_get_text(pStrY), sj_new_float(pos.y)); // y
//		sj_object_insert(jsonFile, sj_string_get_text(pStrZ), sj_new_float(pos.z)); // z
//
//		// rot
//		sj_object_insert(jsonFile, sj_string_get_text(rStrA), sj_new_float(rot.x)); // a
//		sj_object_insert(jsonFile, sj_string_get_text(rStrB), sj_new_float(rot.y)); // b
//		sj_object_insert(jsonFile, sj_string_get_text(rStrC), sj_new_float(rot.z)); // c
//	}
//
//	SJString *file = sj_object_to_json_string(jsonFile);
//	char *fileText = sj_string_get_text(file);
//	slog(fileText);
//}

void LoadJSON()
{
	slog("LOADING JSON");
	jsonFile = sj_load("Level1.json");
	if (jsonFile == NULL)
	{
		slog("JSON file empty or missing. Cannot load.");
		return;
	}
	
	SJson *parentArr = sj_object_get_value(jsonFile, "Level");

	int length = sj_array_get_count(parentArr);
	int i;
	for (i = 0; i < length; i++)
	{
		SJson *child = sj_array_get_nth(parentArr, i);
	
		char* nameText = sj_object_get_value_as_string(child, "name");

		SJson *posArr = sj_object_get_value(child, "pos");
		sj_echo(posArr);
		float xPos = sj_get_float_value(sj_array_get_nth(posArr, 0));
		float yPos = sj_get_float_value(sj_array_get_nth(posArr, 1));
		float zPos = sj_get_float_value(sj_array_get_nth(posArr, 2));

		SJson *rotArr = sj_object_get_value(child, "rot");
		float xRot = sj_get_float_value(sj_array_get_nth(rotArr, 0));
		float yRot = sj_get_float_value(sj_array_get_nth(rotArr, 1));
		float zRot = sj_get_float_value(sj_array_get_nth(rotArr, 2));


		SpawnEntityAtPos(nameText, vector3d(xPos, yPos, zPos),
			vector3d(xRot, yRot, zRot), i, i);
	}

	fileWasLoaded = 1;
	slog("All entites loaded from file.");
}
