#include "Sprite.h"
#include <string.h>
void createTexture(SDL_Renderer *r, SDL_Texture *t, SDL_Surface *s, string imgPath) {
  s = SDL_LoadBMP(imgPath);
  t = SDL_LoadTextureFromSurface(r,s);
}
