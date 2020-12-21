#pragma once

#ifndef __CAMERA_SEQUENCE_CONTROLLER_H__
#define __CAMERA_SEQUENCE_CONTROLLER_H__

#include "../gfc/include/gfc_matrix.h"
#include "Entity.h"
#include "PositionRecorder.h"
#include "../include/gf3d_vgraphics.h"
#include "SpriteManager.h"
#include "AudioPlayer.h"

//struct CamSeqController
//{
//	Entity *triggers;		// list of triggers
//	int triggerCount;
//
//	int triggerIndex;		// the index of the trigger that the player is currently at
//};
//
//extern struct CamSeqController camSeqController;

char combos[3];
int comboIndex;

int playerHealth;
int invincible;

void InitCameraController(Uint32 numTriggers);
void CloseCamSeqController();
void FreeTrigger(Entity *trigger);

Entity* CreateTrigger(Vector3D spawnPos, Vector3D rot);
void MoveToNextTrigger(Vector2D dir);
void HandleEnemiesAtTriggerPos();
void MoveCameraToTrigger(Entity* entity);
void EnableDisableTriggerRender(int enable);

void TriggerThink(Entity* entity);

Entity* GetTriggerList();
int GetTriggerCount();
void AddEnemyToCamSeqController(Entity* ent, int health);

void Combo(char attack);
void Attack();

#endif