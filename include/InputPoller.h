#ifndef __GF3D_INPUTPOLLER_H__
#define __GF3D_INPUTPOLLER_H__

#include <SDL.h>  
#include <simple_logger.h>

typedef enum
{
	Down, Up
}KeyState;

KeyState wBtn;
KeyState aBtn;
KeyState sBtn;
KeyState dBtn;

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

void HandleKey(SDL_Keycode keycode, KeyState state);

void PollForInput();

void OnMousePress(SDL_MouseButtonEvent event);

#endif