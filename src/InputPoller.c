#include "InputPoller.h"

/*
	@brief Polls for input
*/
void PollForInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				OnMousePress(event.button);
				break;
			case SDL_MOUSEMOTION:
				GetDeltaMousePos(event.motion.xrel, event.motion.yrel);
				GetMousePos();
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				HandleKey(event.key.keysym.sym, event.type, event.key.repeat);
				break;
		}
	}
}

int PollForMouseClick()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEBUTTONDOWN)
			return OnMousePress(event.button);
	}
}

void HandleKey(SDL_Keycode keycode, SDL_Event* eventType, int repeat)
{
	if (eventType == SDL_KEYDOWN && repeat != 0)
	{
		switch (keycode)
		{
			case SDLK_RETURN:
				enterBtn = PRESSED;
				break;
		}
	}
	else if (eventType == SDL_KEYUP)
	{
		switch (keycode)
		{
		case SDLK_RETURN:
			enterBtn = RELEASED;
			break;
		}
	}

}

/*
	@brief Handles a mouse click
*/
int OnMousePress(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT)
	{
		slog("left mouse press");
		mouseBtn = PRESSED;
		return 1;
	}
	else 
		return 0;
}

/*
	@brief Gets mouse position
*/
void GetDeltaMousePos(int* x, int* y)
{
	//int x;
	//int y;
	//SDL_GetMouseState(&x, &y);

	xMouseDelta = screenWidth / 2;
	yMouseDelta = screenHeight / 2;

	xMouseDelta = xMouseDelta + x;
	yMouseDelta = yMouseDelta + y;

	//slog("Mouse Delta Pos: x: %i   y:%i", xMousePos, yMousePos);
}

void GetMousePos()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);


	xMousePos = x;

	yMousePos = y;

	//slog("Mouse Pos: x: %i   y:%i", xMousePos, yMousePos);
}

Vector3D ScreenPointToWorldPoint(Vector3D screenPoint)
{
	// get the world matrix where the camera is
	Matrix4 worldMatrix;
	gfc_matrix_view(worldMatrix, vector3d(0, 0, 0), vector3d(0, 1, 0), vector3d(0, 0, 1));

	// get camera's view matrix 
	Matrix4 viewMatrix;
	GetCameraViewMatrix(viewMatrix);

	// get view matrix inverse
	//gfc_matrix_inverse(viewMatrix);

	// multiply world matrix and inverse of view matrix
	Matrix4 matrix;
	gfc_matrix_multiply(matrix, worldMatrix, viewMatrix);

	// transpose the matrix
	//gfc_matrix_transpose(matrix);

	// create matrix for screen point
	Matrix4* screenPointMatrix;
	Vector4D screenPtVect = vector4d(screenPoint.x, 1, screenPoint.y, 1);
	gfc_matrix_multiply_vector4d(&screenPtVect, matrix, screenPtVect);

	slog("world point: %f, %f, %f", screenPtVect.x, 1, screenPtVect.z);

	return vector3d(screenPtVect.x, 1, screenPtVect.z);
}

Vector3D GetNormalizedMouseCoordinates(int mouseX, int mouseY)
{
	float x = (2.0 * mouseX) / screenWidth - 1.0;
	float y = 1.0 - (2.0 * mouseY) / screenHeight;
	float z = 1.0;

	return vector3d(x, z, y);
}

