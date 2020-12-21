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
			case SDL_MOUSEBUTTONUP:
				OnMouseRelease(event.button);
			case SDL_MOUSEMOTION:
				GetDeltaMousePos(event.motion.xrel, event.motion.yrel);
				GetMousePos();
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				HandleKey(event.key.keysym.sym, event.type);
				break;
		}
	}
}

void HandleKey(SDL_Keycode keycode, SDL_Event* eventType)
{
	if (eventType == SDL_KEYDOWN)
	{
		switch (keycode)
		{
			case SDLK_TAB:
				tabBtn = PRESSED;
				break;
			case SDLK_RETURN:
				enterBtn = PRESSED;
				break;
			case SDLK_PAGEDOWN:
				pageDownBtn = PRESSED;
				break;
			case SDLK_SPACE:
				spaceBtn = PRESSED;
				break;
			case SDLK_EQUALS:
				equalsBtn = PRESSED;
				break;
			case SDLK_HOME:
				startBtn = PRESSED;
				break;
			case SDLK_DELETE:
				deleteBtn = PRESSED;
				break;
			case SDLK_BACKSLASH:
				backslashBtn = PRESSED;
				break;
			case SDLK_LSHIFT:
				leftShiftBtn = PRESSED;
				break;
			case SDLK_1:
				/*gunPos = -1;
				gun.lane = -1;*/
				SelectEntity(1);
				ChangeGunSprite(1);
				break;
			case SDLK_2:
			/*	gunPos = 0;
				gun.lane = 0;*/
				SelectEntity(2);
				ChangeGunSprite(2);
				break;
			case SDLK_3:
				SelectEntity(3);
				/*gunPos = 1;
				gun.lane = 1;*/
				break;
			case SDLK_4:
				SelectEntity(4);
				/*gunPos = 1;
				gun.lane = 1;*/
				break;
			case SDLK_w:
				MovePR(vector3d(0, 0, 1));
				break;
			case SDLK_a:
				MovePR(vector3d(1, 0, 0));
				break;
			case SDLK_s:
				MovePR(vector3d(0, 0, -1));
				break;
			case SDLK_d:
				MovePR(vector3d(-1, 0, 0));
				break;
			case SDLK_q:
				MovePR(vector3d(0, 1, 0));
				break;
			case SDLK_e:
				MovePR(vector3d(0, -1, 0));
				break;
			case SDLK_LEFT:
				/*if (leftShiftBtn == PRESSED)
					Rotate(-1.0, 'z');
				else
					Rotate(1.0, 'y');*/
				MoveToNextTrigger(vector2d(-1, 0));
				break;
			case SDLK_RIGHT:
				/*if (leftShiftBtn == PRESSED)
					Rotate(1.0, 'z');
				else
					Rotate(-1.0, 'y');*/
				MoveToNextTrigger(vector2d(1, 0));
				break;
			case SDLK_DOWN:
				break;
			case SDLK_UP:
				MoveToNextTrigger(vector2d(0, 1));
				break;
			case SDLK_BACKSPACE:
				DestroyEntity();
				break;
			case SDLK_p:
				pBtn = PRESSED;
				break;
			case SDLK_LCTRL:
				ctrlBtn = PRESSED;
				break;
			case SDLK_MINUS:
				minusBtn = PRESSED;
				break;
			case SDLK_h:
				hBtn = PRESSED;
				break;
			case SDLK_j:
				jBtn = PRESSED;
				break;
			case SDLK_u:
				uBtn = PRESSED;
				break;
		}
	}
	else if (eventType == SDL_KEYUP)
	{
		switch (keycode)
		{
			case SDLK_h:
				hBtn =	RELEASED;
				Combo('H');
				break;
			case SDLK_j:
				jBtn = RELEASED;
				Combo('J');
				break;
			case SDLK_u:
				uBtn = RELEASED;
				Combo('U');
				break;
			case SDLK_TAB:
				tabBtn = RELEASED;
				SwitchGameMode();
				{
				default:
					break;
				}
				break;
			case SDLK_RETURN:
				enterBtn = RELEASED;
				SpawnEntity(0);
				break;
			case SDLK_PAGEDOWN:
				pageDownBtn = RELEASED;
				ChangeAnimStateAll(AnimPlay);
				break;
			case SDLK_EQUALS:
				equalsBtn = RELEASED;
				break;
			case SDLK_MINUS:
				minusBtn = RELEASED;
				health -= 1;
				break;
			case SDLK_SPACE:
				spaceBtn = RELEASED;
				EnableDisableEntityLock();
				Attack();
				break;
			case SDLK_LSHIFT:
				leftShiftBtn = RELEASED;
				break;
			case SDLK_HOME:
				startBtn = RELEASED;
				slog("startBtn pressed");
				//MoveToNextTrigger();
				break;
			case SDLK_DELETE:
				deleteBtn = RELEASED;
				ClearJSONFile();
				break;
			case SDLK_BACKSLASH:
				backslashBtn = RELEASED;
				DuplicateEntity();
				break;
			case SDLK_p:
				pBtn = RELEASED;
				PlaySFX(explosionSound);
				break;
			case SDLK_LCTRL:
				ctrlBtn = RELEASED;
				SetGameState(PLAYING);
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
		//slog("left mouse press");
		mouseBtn = PRESSED;
		return 1;
	}
	else 
		return 0;
}

int OnMouseRelease(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT)
	{
		//slog("left mouse release");
		mouseBtn = RELEASED;
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

