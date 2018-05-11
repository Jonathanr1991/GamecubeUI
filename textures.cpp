#include "Sprite.h"
#include <string.h>
void printRect(SDL_Rect *r) {
  printf("x: %d y: %d, w: %d, h: %d\n", r->x, r->y, r->w, r->h);
}
void createTexture(SDL_Renderer *r, SDL_Texture *t, SDL_Surface *s, string imgPath) {
  s = SDL_LoadBMP(imgPath);
  t = SDL_LoadTextureFromSurface(r,s);
}
