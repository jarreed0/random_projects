#include <SDL2/SDL.h>

namespace sdltemplate {

char *title = "SDL2 Template";
int width = 500, height = 500;
SDL_Renderer *renderer;
SDL_Window *window;
int frameCount, timerFPS, lastFrame, fps, lastTime;
int setFPS = 60;
SDL_Point mouse;
const Uint8 *keystates;
Uint32 mousestate;
SDL_Event event;
bool running;

void init() {
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  SDL_Init(SDL_INIT_EVERYTHING);
  window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  running = 1;
}

void init(char *t, int w, int h) {
  title = t;
  width = w;
  height = h;
  init();
}

void input() {
  keystates = SDL_GetKeyboardState(NULL);
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
      running = false;
  }
  mousestate = SDL_GetMouseState(&mouse.x, &mouse.y);
}

void begin_render() {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  frameCount++;
  timerFPS = SDL_GetTicks() - lastFrame;
  if (timerFPS < (1000 / setFPS)) {
    SDL_Delay((1000 / setFPS) - timerFPS);
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void end_render() { SDL_RenderPresent(renderer); }

void quit() {
  running = 0;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void loop() {
  lastFrame = SDL_GetTicks();
  if (lastFrame >= (lastTime + 1000)) {
    lastTime = lastFrame;
    fps = frameCount;
    frameCount = 0;
  }
}

void drawpoint(int x, int y) { SDL_RenderDrawPoint(renderer, x, y); }
void drawpoint(int x, int y, int b) {
  int c = 255 * b;
  SDL_SetRenderDrawColor(renderer, c, c, c, 255);
  SDL_RenderDrawPoint(renderer, x, y);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

} // namespace sdltemplate
