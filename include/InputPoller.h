#pragma once

#ifndef __GF3D_INPUTPOLLER_H__
#define __GF3D_INPUTPOLLER_H__

#include <SDL.h>  
#include <simple_logger.h>
#include <gfc_vector.h>
#include "gf3d_vgraphics.h"
#include "../win32/Gun.h"
#include "TextFileHandler.h"
#include "CameraSequenceController.h"
#include "AudioPlayer.h"
#include "SpriteManager.h"
#include "GameStateManager.h"
#include "PositionRecorder.h"
#include "EntitySpawner.h"

typedef enum
{
	RELEASED, PRESSED
}KeyState;

KeyState mouseBtn;
KeyState enterBtn;
KeyState equalsBtn;
KeyState spaceBtn;
KeyState leftShiftBtn;
KeyState startBtn;
KeyState deleteBtn;
KeyState backslashBtn;
KeyState pBtn;
KeyState ctrlBtn;

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