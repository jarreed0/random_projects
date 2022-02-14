#include "sdltemplate.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <iostream>

std::vector<Mix_Chunk*> sounds;
std::vector<Mix_Music*> music;

int loadMusic(const char* filename) {
	Mix_Music *m = NULL;
	m = Mix_LoadMUS(filename);
	if(m == NULL) {
		printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
		return -1;
	}
	music.push_back(m);
	return music.size()-1;
}
int loadSound(const char* filename) {
	Mix_Chunk *m = NULL;
	m = Mix_LoadWAV(filename);
	if(m == NULL) {
		printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
		return -1;
	}
	sounds.push_back(m);
	return sounds.size()-1;
}

int volume;
void setVolume(int v) {
	volume = (MIX_MAX_VOLUME * v) / 100;
}

int playMusic(int m) {
	if(Mix_PlayingMusic() == 0) {
		Mix_Volume(1, volume);
		Mix_PlayMusic(music[m], -1);
	}
	return 0;
}
int playSound(int s) {
	Mix_Volume(-1, volume);
        Mix_PlayChannel(-1, sounds[s], 0);
	return 0;
}

int initMixer() {
	Mix_Init(MIX_INIT_MP3);
	SDL_Init(SDL_INIT_AUDIO);
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_Mixer couldnt init. Err: %s\n", Mix_GetError());
		return -1;
	}
	setVolume(80);
	return 0;
}
void quitMixer() {
	for(int s=0; s<sounds.size(); s++) {
		Mix_FreeChunk(sounds[s]);
		sounds[s]=NULL;
	}
	for(int s=0; s<music.size(); s++) {
		Mix_FreeMusic(music[s]);
		music[s]=NULL;
	}
	Mix_Quit();
}

void togglePlay() {
	if(Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
	} else {
		Mix_PauseMusic();
	}
}

int main() {
	sdltemplate::init();
	initMixer();
	int sound = loadSound("sound.wav");
	int song = loadMusic("song.mp3");
	playMusic(song);
	while(sdltemplate::running) {
		sdltemplate::loop();
		sdltemplate::begin_render();
		sdltemplate::end_render();
		if(sdltemplate::keystates[SDL_SCANCODE_Q]) playSound(sound);
		if(sdltemplate::keystates[SDL_SCANCODE_P]) togglePlay();
	}
	sdltemplate::quit();
	quitMixer();
	return 0;
}
