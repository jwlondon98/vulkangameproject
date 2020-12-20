#ifndef __AUDIO_PLAYER_H__
#define __AUDIO_PLAYER_H__

#include <SDL.h>
#include <SDL_mixer.h>   

#include "simple_logger.h"
#include "../gfc/include/gfc_text.h"

Mix_Chunk *explosionSound;
Mix_Music *bgMusic;

void InitAudio();
void CloseAudio();

void PlayMusic(Mix_Music *music);
void PlaySFX(Mix_Chunk *sfx);

#endif