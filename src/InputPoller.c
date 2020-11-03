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
				slog("xDelta: %i", event.motion.xrel);
				GetDeltaMousePos(event.motion.xrel, event.motion.yrel);
				GetMousePos();
				break;
			case SDL_KEYDOWN:
				HandleKey(event.key.keysym.sym, Down);
				break;
			case SDL_KEYUP:
				HandleKey(event.key.keysym.sym, Up);
				break;
		}
	}
}

void HandleKey(SDL_Keycode keycode, KeyState state)
{
	switch (keycode)
	{
		case SDLK_w:
			wBtn = state;
			break;
		case SDLK_a:
			aBtn = state;
			break;
		case SDLK_s:
			sBtn = state;
			break;
		case SDLK_d:
			dBtn = state;
			break;
	}
}

/*
	@brief Handles a mouse click
*/
void OnMousePress(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT)
		slog("LEFT MOUSE BUTTON CLICKED");
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

	slog("Mouse Pos: x: %i   y:%i", xMousePos, yMousePos);
}

