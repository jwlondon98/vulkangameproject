#include "AudioPlayer.h"

void InitAudio()
{
	SDL_Init(SDL_INIT_AUDIO);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	// load audio files
	//Mix_Music *bgMusic = Mix_LoadMUS(".mp3");
	explosionSound = Mix_LoadWAV("audio/Explosion.wav");
}

void PlaySFX(Mix_Chunk *sfx)
{
	Mix_PlayChannel(-1, sfx, 0);
}

void CloseAudio()
{
	Mix_FreeChunk(explosionSound);
	Mix_CloseAudio();
}