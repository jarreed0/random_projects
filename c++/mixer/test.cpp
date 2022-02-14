#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "sdltemplate.h"

std::vector<Mix_Chunk*> sounds;
std::vector<Mix_Music*> music;

int loadMusic(const char* filename) {
 Mix_Music *m = NULL;
 m = Mix_LoadMUS(filename);
 if(m == NULL) {
  printf( "Failed to load wav! SDL_mixer Error: %s\n", Mix_GetError() );
  return -1;
 }
 music.push_back(m);
 return music.size()-1;
}

int loadSound(const char* filename) {
 Mix_Chunk *s = NULL;
 s = Mix_LoadWAV(filename);
 if(s == NULL) {
  printf( "Failed to load wav! SDL_mixer Error: %s\n", Mix_GetError() );
  return -1;
 }
 sounds.push_back(s);
 return sounds.size()-1;
}

int volume;
void setVolume(int v) {
 volume = (MIX_MAX_VOLUME * v) / 100;
}

int playSound(int s) {
 Mix_Volume(-1, volume);
 Mix_PlayChannel(-1, sounds[s], 0);
 return 0;
}

int playMusic(int m) {
 if(Mix_PlayingMusic() == 0) {
  Mix_Volume(1, volume);
  Mix_PlayMusic(music[m], -1);
 }
 return 0;
}

int initMixer() {
 Mix_Init(MIX_INIT_MP3);
 SDL_Init(SDL_INIT_AUDIO);
 if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
  printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
  return -1;
 }
 setVolume(80);
 return 0;
}

void togglePlay() {
 if(Mix_PausedMusic() == 1) {
  Mix_ResumeMusic();
  std::cout << "play" << std::endl;
 } else {
  std::cout << "pause" << std::endl;
  Mix_PauseMusic();
 }
}

void quitMixer() {
 for(int s=0; s<sounds.size(); s++) {
  Mix_FreeChunk(sounds[s]);
  sounds[s]=NULL;
 }
 for(int m=0; m<music.size(); m++) {
  Mix_FreeMusic(music[m]);
  music[m]=NULL;
 }
 Mix_Quit();
}

int main() {
 if(SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cout << "Failed at SDL_Init()" << std::endl;
 initMixer();
 int sound = loadSound("sound.wav");
 int song = loadMusic("song.mp3");
 playMusic(song);
 sdltemplate::init();
 while(sdltemplate::running) {
  sdltemplate::loop();
  sdltemplate::begin_render();
  sdltemplate::end_render();
  if(sdltemplate::keystates[SDL_SCANCODE_Q]) playSound(sound);
  if(sdltemplate::keystates[SDL_SCANCODE_W]) togglePlay();
 }
 quitMixer();
 sdltemplate::quit();
 return 0;
}
