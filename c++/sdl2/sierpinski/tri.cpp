#include "sdltemplate.h"
using namespace sdltemplate;
#include <vector>

std::vector<SDL_Point> dots;
SDL_Point tmp;
SDL_Point top, left, right;

int main() {
 srand(time(NULL));
 //sdl("Triforce - Sierpinski", 800, 800);
 sdl("Triforce - Sierpinski", 900/2, 1600/2);
 bkg = createColor(0,0,0,255);
 tmp.x = WORLD/2; tmp.y = 100;
 //tmp.x = 400; tmp.y = 100;
 top=tmp;
 dots.push_back(tmp);
 //tmp.y+=400; tmp.x+=280;
 tmp.x = WORLD - 100; tmp.y = WORLD - 100;
 right=tmp;
 dots.push_back(tmp);
 //tmp.x-=280; tmp.x-=280;
 tmp.x = 100; tmp.y = WORLD - 100;
 left=tmp;
 dots.push_back(tmp);
 tmp.x = rand() % 800;
 tmp.y = rand() % 800;
 dots.push_back(tmp);
 int cnt = 0;
 while(running) {
  loop();
  //setDrawColor(createColor(255,100,100,255));
  if(keystates[SDL_SCANCODE_ESCAPE]) running=false;
  if(keystates[SDL_SCANCODE_D]) screenpos.x-=4;
  if(keystates[SDL_SCANCODE_A]) screenpos.x+=4;
  if(keystates[SDL_SCANCODE_S]) screenpos.y-=4;
  if(keystates[SDL_SCANCODE_W]) screenpos.y+=4;
  //if(keystates[SDL_SCANCODE_Q]) {screenpos.w-=20+mouse.x; screenpos.h-=20-mouse.y;}
  //if(keystates[SDL_SCANCODE_E]) {screenpos.w+=20-mouse.x; screenpos.h+=20-mouse.y;}
  if(keystates[SDL_SCANCODE_Q]) {screenpos.w-=20; screenpos.h-=20; screenpos.x+=12; screenpos.y+=12;}
  if(keystates[SDL_SCANCODE_E]) {screenpos.w+=20; screenpos.h+=20; screenpos.x-=12; screenpos.y-=12;}
  if(keystates[SDL_SCANCODE_R]) {screenpos.x=tmp.x-(width/2); screenpos.y=tmp.y-(height/2);}

  /*for(int d=0;d<dots.size();d++) {
   //setDrawColor(createColor(dots[d].x+100,dots[d].y+100,100,255));
   setDrawColor(createColor(dots[d].x+200,dots[d].y+200,200,255));
   drawPoint(dots[d]);
   //SDL_RenderDrawPoint(screen, dots[d].x, dots[d].y);
  }*/
  int p = rand() % 3;
  SDL_Point sel;
  if(p==0) sel=top;
  if(p==1) sel=left;
  if(p==2) sel=right;
  int x = (tmp.x+sel.x)/2;
  int y = (tmp.y+sel.y)/2;
  tmp.x=x;tmp.y=y;
  setDrawColor(createColor(tmp.x+200,tmp.y+200,200,255));
  drawPoint(tmp);
  dots.push_back(tmp);
  //std::cout << cnt << ": " << tmp.x << ", " << tmp.y << "\n";
  cnt++;
 }
 quit();
}
