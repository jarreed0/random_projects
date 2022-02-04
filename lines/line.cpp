#include "sdltemplate.h"

SDL_Point anchor;

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

double slope(double x1, double y1, double x2, double y2) {
  if (x2 - x1 == 0)
    return (y2 - y1);
  return (y2 - y1) / (x2 - x1);
}

double slope(SDL_Point f, SDL_Point l) { return slope(f.x, f.y, l.x, l.y); }

void slopeline(SDL_Point s, SDL_Point e) {
  SDL_Point first, last;
  if (s.x < e.x) {
    first = s;
    last = e;
  } else {
    first = e;
    last = s;
  }
  double m = slope(first, last);
  double b = first.y - (m * first.x);
  for (int x = first.x; x < last.x; x += 1) {
    sdltemplate::drawpoint(x, (m * x) + b);
  }
}

void dda(double x1, double y1, double x2, double y2) {
  double dx = x2 - x1;
  double dy = y2 - y1;
  double steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
  double xinc = dx / steps;
  double yinc = dy / steps;
  double x = x1;
  double y = y1;
  for (int i = 0; i <= steps; i++) {
    sdltemplate::drawpoint(round(x), round(y));
    x += xinc;
    y += yinc;
  }
}

void bresenham(double x1, double y1, double x2, double y2) {
  int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
  dx = x2 - x1;
  dy = y2 - y1;
  dx1 = abs(dx);
  dy1 = abs(dy);
  px = 2 * dy1 - dx1;
  py = 2 * dx1 - dy1;
  if (dy1 <= dx1) {
    if (dx >= 0) {
      x = x1;
      y = y1;
      xe = x2;
    } else {
      x = x2;
      y = y2;
      xe = x1;
    }
    sdltemplate::drawpoint(x, y);
    for (i = 0; x < xe; i++) {
      x = x + 1;
      if (px < 0) {
        px = px + 2 * dy1;
      } else {
        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
          y = y + 1;
        } else {
          y = y - 1;
        }
        px = px + 2 * (dy1 - dx1);
      }
      sdltemplate::drawpoint(x, y);
    }
  } else {
    if (dy >= 0) {
      x = x1;
      y = y1;
      ye = y2;
    } else {
      x = x2;
      y = y2;
      ye = y1;
    }
    sdltemplate::drawpoint(x, y);
    for (i = 0; y < ye; i++) {
      y = y + 1;
      if (py <= 0) {
        py = py + 2 * dx1;
      } else {
        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
          x = x + 1;
        } else {
          x = x - 1;
        }
        py = py + 2 * (dx1 - dy1);
      }
      sdltemplate::drawpoint(x, y);
    }
  }
}

float adjustWu(float x) {
  if (x > 0)
    return x - (int)x;
  return x - (int)(x + 1);
}

void wu(int x0, int y0, int x1, int y1) {
  bool steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(&x0, &y0);
    swap(&x1, &y1);
  }
  if (x0 > x1) {
    swap(&x0, &x1);
    swap(&y0, &y1);
  }
  float dx = x1 - x0;
  float dy = y1 - y0;
  float gradient = dy / dx;
  if (dx == 0.0)
    gradient = 1;

  int xpxl1 = x0;
  int xpxl2 = x1;
  float intersectY = y0;
  int x;
  if (steep) {
    for (x = xpxl1; x <= xpxl2; x++) {
      sdltemplate::drawpoint((int)intersectY, x, adjustWu(intersectY));
      sdltemplate::drawpoint((int)intersectY - 1, x, 1 - intersectY);
      intersectY += gradient;
    }

  } else {
    for (x = xpxl1; x <= xpxl2; x++) {
      sdltemplate::drawpoint(x, (int)intersectY, adjustWu(intersectY));
      sdltemplate::drawpoint(x, (int)intersectY - 1, 1 - intersectY);
      intersectY += gradient;
    }
  }
}

void run() {
  sdltemplate::begin_render();

  // point
  // sdltemplate::drawpoint(anchor.x,anchor.y);
  // sdltemplate::drawpoint(sdltemplate::mouse.x,sdltemplate::mouse.y);

  // slopeline(anchor, sdltemplate::mouse);

  // digital differential analyser
  // dda(anchor.x, anchor.y, sdltemplate::mouse.x, sdltemplate::mouse.y);

  // bresenham line algorithm
  // bresenham(anchor.x, anchor.y, sdltemplate::mouse.x, sdltemplate::mouse.y);

  // xiaolin wu - anti-aliased
  wu(anchor.x, anchor.y, sdltemplate::mouse.x, sdltemplate::mouse.y);

  sdltemplate::end_render();
}

int main() {
  sdltemplate::init("Lines", 500, 500);
  anchor.x = sdltemplate::width / 2;
  anchor.y = sdltemplate::height / 2;
  while (sdltemplate::running) {
    sdltemplate::loop();
    sdltemplate::input();
    run();
  }
  sdltemplate::quit();
}
