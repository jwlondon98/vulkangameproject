#include "AudioPlayer.h"

void InitAudio()
{
	SDL_Init(SDL_INIT_AUDIO);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	// load audio files
	bgMusic = Mix_LoadMUS("audio/BackgroundMusic.mp3");
	explosionSound = Mix_LoadWAV("audio/Explosion.wav");
	explosionSound->volume = 50;
}

void PlayMusic(Mix_Music *music)
{
	Mix_PlayMusic(music, -1);
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