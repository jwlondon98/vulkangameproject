#ifndef __GF3D_INPUTPOLLER_H__
#define __GF3D_INPUTPOLLER_H__

#include <SDL.h>  
#include <simple_logger.h>

typedef enum
{
	RELEASED, PRESSED
}KeyState;

KeyState mouseBtn;
KeyState enterBtn;

int screenWidth;
int screenHeight;

// actual mouse positions
int xMousePos;
int yMousePos;

// delta mouse postions
int xMouseDelta;
int yMouseDelta;

void GetMousePos();
void GetDeltaMousePos(int* x, int* y);

void HandleKey(SDL_Keycode keycode, SDL_Event* eventType);

void PollForInput();

void OnMousePress(SDL_MouseButtonEvent event);

#endif