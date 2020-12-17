#include "PositionRecorder.h"

struct PositionRecorder posRec;

void CreatePR()
{
	posRec._inUse = 1;
	posRec.currentPos = vector3d(0, 0, 0);
	posRec.step = 1;
	posRec.lastEntityLocked = 0;

	// set pr's position to world origin
	gfc_matrix_identity(posRec.mat);

	gfc_matrix_make_translation(
		posRec.mat,
		posRec.currentPos
	);

	slog("Position Recorder Created");
}

void FreePR()
{
	memset(&posRec, 0, sizeof(posRec));
	slog("Position Recorder Freed");
}

void MovePR(Vector3D moveVect)
{
	Vector3D lastPos = posRec.currentPos;
	float step = posRec.step;

	float xPos = lastPos.x + (moveVect.x * step);
	float yPos = lastPos.y + (moveVect.y * step);
	float zPos = lastPos.z + (moveVect.z * step);

	float entityXPos;
	float entityYPos;
	float entityZPos;

	if (lastSpawnedEntity)
	{
		 entityXPos = lastSpawnedEntity->lastPos.x + (moveVect.x * -step);
		 entityYPos = lastSpawnedEntity->lastPos.y + (moveVect.y * -step);
		 entityZPos = lastSpawnedEntity->lastPos.z + (moveVect.z * -step);
	}

	gfc_matrix_make_translation(
		posRec.mat,
		vector3d(xPos, yPos, zPos)
	);

	gf3d_vgraphics_translate_camera(vector3d(xPos, yPos, zPos));

	if (posRec.lastEntityLocked == 1)
	{
		gfc_matrix_make_translation(
			lastSpawnedEntity->modelMatrix,
			vector3d(entityXPos, entityYPos, entityZPos)
		);

		lastSpawnedEntity->lastPos = vector3d(entityXPos, entityYPos, entityZPos);

		/*slog("LAST SPAWNED ENTITY current pos at (%f, %f, %f)",
			lastSpawnedEntity->lastPos.x, lastSpawnedEntity->lastPos.y, lastSpawnedEntity->lastPos.z);
		*/

		// Record position to JSON
		if (lastSpawnedEntity->jsonKey)
		{
			WriteJSON(
				lastSpawnedEntity->jsonKey,
				lastSpawnedEntity->entityName,
				lastSpawnedEntity->lastPos, 1, lastSpawnedEntity->entityNum);

			sj_save(jsonFile, "Level1.json");
		}
	}

	posRec.currentPos = vector3d(xPos, yPos, zPos);
	//slog("POSREC current pos at (%f, %f, %f)",
	//	posRec.currentPos.x, posRec.currentPos.y, posRec.currentPos.z);

	//slog("Pos Rec moved to (%f, %f, %f)", xPos, yPos, zPos);
}

void RotateCamera(float dir, char axis)
{
	if (axis == 'x')
		gf3d_vgraphics_rotate_camera(dir, 'x', 1);
	else if (axis == 'y')
		gf3d_vgraphics_rotate_camera(dir, 'y', 1);
	else if (axis == 'z')
		gf3d_vgraphics_rotate_camera(dir, 'z', 1);
}

void RotateCameraAboutEntity(float dir, char axis)
{
	if (axis == 'x')
		gf3d_vgraphics_rotate_camera_about_entity(lastSpawnedEntity, posRec.currentPos, dir, 'x', 1);
	else if (axis == 'y')
		gf3d_vgraphics_rotate_camera_about_entity(lastSpawnedEntity, posRec.currentPos, dir, 'y', 1);
	else if (axis == 'z')
		gf3d_vgraphics_rotate_camera_about_entity(lastSpawnedEntity, posRec.currentPos, dir, 'z', 1);
}

void RotateEntity(float dir, char axis)
{
	if (axis == 'x')
		gf3d_vgraphics_rotate_entity(lastSpawnedEntity, dir, 'x', 1);
	else if (axis == 'y')
		gf3d_vgraphics_rotate_entity(lastSpawnedEntity, dir, 'y', 1);
	else if (axis == 'z')
		gf3d_vgraphics_rotate_entity(lastSpawnedEntity, dir, 'z', 1);
}

void Rotate(float dir, char axis)
{
	if (posRec.lastEntityLocked == 0)
		RotateCamera(dir, axis);
	else
		RotateEntity(dir, axis);
}	

void EnableDisableEntityLock()
{
	if (posRec.lastEntityLocked == 0)
		posRec.lastEntityLocked = 1;
	else
		posRec.lastEntityLocked = 0;
}