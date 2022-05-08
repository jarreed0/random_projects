#include "sdltemplate.h"
using namespace sdltemplate;

SDL_Point tmp, tmp2;
SDL_Point hex[6];

SDL_Point centerOfTriangle(SDL_Point a, SDL_Point b, SDL_Point c) {
 SDL_Point p{(a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3};
 return p;
}

int main() {
 srand(time(NULL));
 sdl("Kosh Snowflake", 900, 900);

 hex[0] = createPoint(WORLD*.3,WORLD*.2);
 hex[1] = createPoint(WORLD*.7,WORLD*.2);
 hex[2] = createPoint(WORLD*.85,WORLD/2);
 hex[3] = createPoint(WORLD*.7,WORLD*.8);
 hex[4] = createPoint(WORLD*.3,WORLD*.8);
 hex[5] = createPoint(WORLD*.15,WORLD/2);
 begin_render();
 for(int i=0;i<(*(&hex + 1) - hex);i++) {
  setDrawColor(createColor(255,255,255,255));
  if(i<(*(&hex + 1) - hex)-1) {drawLine(hex[i],hex[i+1]);} else {drawLine(hex[i],hex[0]);}
 }

 int cnt = 0;
 //tmp.x = rand() % width/2 + hex[0].x;
 //tmp.y = rand() % height/2 + hex[0].y;
 tmp.x = WORLD*.3;
 tmp.y = WORLD/2;
 screenpos.x=-40;
 screenpos.y=-72;
 screenpos.w=screenpos.h=1020;
 while(running) {
  loop();
  if(keystates[SDL_SCANCODE_ESCAPE]) running=false;
  if(keystates[SDL_SCANCODE_D]) screenpos.x-=4;
  if(keystates[SDL_SCANCODE_A]) screenpos.x+=4;
  if(keystates[SDL_SCANCODE_S]) screenpos.y-=4;
  if(keystates[SDL_SCANCODE_W]) screenpos.y+=4;
  if(keystates[SDL_SCANCODE_Q]) {screenpos.w-=20; screenpos.h-=20; screenpos.x+=12; screenpos.y+=12;}
  if(keystates[SDL_SCANCODE_E]) {screenpos.w+=20; screenpos.h+=20; screenpos.x-=12; screenpos.y-=12;}
  if(keystates[SDL_SCANCODE_R]) {screenpos.x=tmp2.x-(width/2); screenpos.y=tmp2.y-(height/2);}

  int p1 = rand() % (*(&hex + 1) - hex);
  int p2 = rand() % (*(&hex + 1) - hex);
  if(p2==p1) {
   p2++;
  }
  if(p2==(*(&hex + 1) - hex)) p2=0;
  tmp2 = centerOfTriangle(hex[p1],hex[p2],tmp);
  setDrawColor(createColor(tmp2.x*255/WORLD,tmp2.y*255/WORLD,255-((255*tmp2.x)/WORLD),255));
  drawPoint(tmp2);
  tmp=tmp2;
  //std::cout << cnt << ": " << tmp2.x << ", " << tmp2.y << "\n";
  cnt++;
 }
 quit();
}
