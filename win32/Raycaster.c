#include "Raycaster.h"

void Raycast(Ray* ray)
{
	// https://antongerdelan.net/opengl/raycasting.html
}

Ray CreateRay(Vector3D origin, Vector3D direction)
{
	Ray* ray;
	ray->origin = origin;
	ray->direction = direction;

	return *ray;
}

Vector3D GetNormalizedMouseCoordinates(int mouseX, int mouseY, int screenWidth, int screenHeight)
{
	float x = (2.0 * mouseX) / screenWidth - 1.0;
	float y = 1.0 - (2.0 * mouseY) / screenHeight;
	float z = 1.0;

	return vector3d(x, z, y);
}

Vector4D CreateClipCoordinates(Vector3D normMouseCoords)
{
	return vector4d(normMouseCoords.x, -1.0, normMouseCoords.y, 1.0);
}

Vector4D CreateCamEyeCoordinates(Matrix4 projectionMatrix, Vector4D rayClip)
{
	//Vector4D rayEye = vector4d_reflect
}