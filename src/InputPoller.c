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
void OnMousePress(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT)
	{
		slog("LEFT MOUSE BUTTON CLICKED");
	}
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

