#include "PositionRecorder.h"

struct PositionRecorder posRec;

void CreatePR()
{
	posRec._inUse = 1;
	posRec.currentPos = vector3d(0, 0, 0);
	posRec.step = 1;

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

	gfc_matrix_make_translation(
		posRec.mat,
		vector3d(xPos, yPos, zPos)
	);

	gf3d_vgraphics_translate_camera(vector3d(xPos, yPos, zPos));

	posRec.currentPos = vector3d(xPos, yPos, zPos);

	slog("Pos Rec moved to (%f, %f, %f)", xPos, yPos, zPos);
}