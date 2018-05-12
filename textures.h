#include "Sprite.h"
#include <string.h>
void printRect(SDL_Rect *r) {
  printf("x: %d y: %d, w: %d, h: %d\n", r->x, r->y, r->w, r->h);
}
void renderTextures(SDL_Renderer *r, SDL_Texture *texs[], SDL_Rect *rects[], int size) {
  SDL_RenderClear(r);
  SDL_SetRenderDrawColor(r,255,255,255,255); // white rectangle. 
  for (int i = 0; i < size-1; i++) {
    SDL_RenderCopy(r, tex[i], NULL, rects[i]);
  }
  SDL_DrawRect(r, rects[size-1]);
  SDL_RenderPresent(r);
   
void createTexture(SDL_Renderer *r, SDL_Texture *t, SDL_Surface *s, string imgPath) {
  s = SDL_LoadBMP(imgPath);
  t = SDL_LoadTextureFromSurface(r,s);
}
