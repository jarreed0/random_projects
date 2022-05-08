#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#define WORLD 2000 //14000

namespace sdltemplate {

SDL_Color bkg;
SDL_Color blue = {0,0,255,255};

const char *title = "SDL2 Template";
int width = 500, height = 500;
SDL_Renderer *renderer;
SDL_Window *window;
SDL_Texture *screen;
SDL_Rect screensize, screenpos;
int frameCount, timerFPS, lastFrame, fps, lastTime;
int setFPS = 60;
SDL_Point mouse;
const Uint8 *keystates;
Uint32 mousestate;
SDL_Event event;
bool running;

void drawLine(int x0, int y0, int x1, int y1) {
        SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
}
void drawLine(SDL_Point a, SDL_Point b) {
        SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
}

SDL_Color createColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
 SDL_Color c{r,g,b,a};
 return c;
}

SDL_Rect createRect(int x, int y, int w, int h) {
 SDL_Rect r{x,y,w,h};
 return r;
}

SDL_Point createPoint(int x, int y) {
 SDL_Point p{x,y};
 return p;
}

std::vector<SDL_Texture*> images;
int loadImage(std::string filename) {
 images.push_back(IMG_LoadTexture(renderer, filename.c_str()));
 return images.size()-1;
}
void drawImage(int img, SDL_Rect dest, SDL_Rect src) {
 SDL_RenderCopy(renderer, images[img], &src, &dest);
}
void drawImage(int img, SDL_Rect dest, SDL_Rect src, double ang, SDL_Point c, bool flipH, bool flipV) {
 SDL_RendererFlip flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
 if(!flipV && !flipH) {
  flip = SDL_FLIP_NONE;
 } else if(flipH) {
  flip = SDL_FLIP_HORIZONTAL;
 } else if(flipV) {
  flip = SDL_FLIP_VERTICAL;
 }
 SDL_RenderCopyEx(renderer, images[img], &src, &dest, ang, &c, flip);
}

void sdl() {
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  SDL_Init(SDL_INIT_EVERYTHING);
  window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  running = 1;
  screensize.x=screensize.y=0;
  screensize.w=WORLD;screensize.h=WORLD;
  screenpos = screensize;
  screenpos.w=width;screenpos.h=width;
  screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WORLD, WORLD);
}

void drawPoint(SDL_Point p) { SDL_RenderDrawPoint(renderer, p.x, p.y); }
void drawPoint(int x, int y) { SDL_RenderDrawPoint(renderer, x, y); }

void sdl(const char *t, int w, int h) {
  title = t;
  width = w;
  height = h;
  sdl();
}

void updateKeys() {
  keystates = SDL_GetKeyboardState(NULL);
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
      running = false;
  }
  mousestate = SDL_GetMouseState(&mouse.x, &mouse.y);
}

void setDrawColor(SDL_Color c) { SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a); }

void begin_render() {
  SDL_SetRenderTarget(renderer, screen);
  setDrawColor(bkg);
  //SDL_RenderClear(renderer);
  /*frameCount++;
  timerFPS = SDL_GetTicks()-lastFrame;
  if(timerFPS<(1000/setFPS)) {
   SDL_Delay((1000/setFPS)-timerFPS);
  }*/
}

void end_render() {
  SDL_SetRenderTarget(renderer, NULL);
  SDL_RenderCopy(renderer, screen, &screensize, &screenpos);
  SDL_RenderPresent(renderer);
}

void quit() {
  running = 0;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void loop() {
  end_render();
  /*lastFrame = SDL_GetTicks();
  if (lastFrame >= (lastTime + 1000)) {
    lastTime = lastFrame;
    fps = frameCount;
    frameCount = 0;
  }*/
  updateKeys();
  begin_render();
}

void drawpoint(int x, int y) { SDL_RenderDrawPoint(renderer, x, y); }
void drawpoint(int x, int y, int b) {
  int c = 255 * b;
  SDL_SetRenderDrawColor(renderer, c, c, c, 255);
  SDL_RenderDrawPoint(renderer, x, y);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

} // namespace sdltemplate
