#ifndef __RAYCASTER_H__
#define __RAYCASTER_H__

#include "gfc_vector.h"
#include "InputPoller.h"
#include "simple_logger.h"
#include "Entity.h"
#include "gfc_matrix.h"

typedef struct Ray_S
{
	Vector3D origin;
	Vector3D direction;

	Vector3D normMouseCoords;
	
	Vector3D (*GetPoint)(const struct Ray_S**);

}Ray;

typedef struct RaycastHit_S
{
	// collider it hit
	Entity* hitEntity;

}RaycastHit;


void Raycast(Ray* ray);

Ray CreateRay(Vector3D origin, Vector3D direction);

//Vector3D GetNormalizedMouseCoordinates(int mouseX, int mouseY);

Vector4D CreateClipCoordinates(Vector3D normMouseCoords);

Vector4D CreateCamEyeCoordinates(Matrix4 projectionMatrix, Vector4D rayClip);

Vector3D GetPoint(const struct Ray_S* r);

#endif