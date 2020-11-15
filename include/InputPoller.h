#pragma once

#ifndef __GF3D_INPUTPOLLER_H__
#define __GF3D_INPUTPOLLER_H__

#include <SDL.h>  
#include <simple_logger.h>
#include <gfc_vector.h>
#include "gf3d_vgraphics.h"

typedef enum
{
	RELEASED, PRESSED
}KeyState;

KeyState mouseBtn;
KeyState enterBtn;

int screenWidth;
int screenHeight;

int gunPos;

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

int OnMousePress(SDL_MouseButtonEvent event);
int OnMouseRelease(SDL_MouseButtonEvent event);

Vector3D ScreenPointToWorldPoint(Vector3D screenPoint);

Vector3D GetNormalizedMouseCoordinates(int mouseX, int mouseY);

#endif