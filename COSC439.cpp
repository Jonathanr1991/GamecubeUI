#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "SDL_scancode.h"
#include "Sprite.h"
//#include "controller.h"
#include <SDL_gamecontroller.h>

#define BMPSIZE 240
#define LEFT_DEADZONE -28000
#define RIGHT_DEADZONE 28000

#define ADVANCE_LEFT -1
#define ADVANCE_RIGHT 1
#define ADVANCE_DOWN 2
#define ADVANCE_UP 2

#define MELEE "Smash Bros"
#define SONICHEROES "Sonic Heroes"
#define SUNSHINE "Super Mario Sunshine"

#define fps 60
using namespace std;
SDL_Rect box1;
SDL_Rect box2;
SDL_Rect box3;
SDL_Rect logo;
SDL_Rect selectorRect;

// global variables. 

void printRect(SDL_Rect *r) {
  printf("x: %d y: %d, w: %d, h: %d\n", r->x, r->y, r->w, r->h);
}

void executeDolphin(string game, SDL_Window *w) { // TODO put macros here
  SDL_HideWindow(w);
  if (game.compare("Smash Bros") == 0) 
    system("dolphin-emu -e /usr/local/GamecubeUI/iso/melee.iso");
  if (game.compare("Sonic Heroes") == 0) 
    system("dolphin-emu -e /usr/local/GamecubeUI/iso/sonicheroes.iso");
  if (game.compare("Super Mario Sunshine") == 0)
    system("dolphin-emu -e /usr/local/GamecubeUI/iso/supermariosunshine.iso ");
    
}

void advanceSelection(SDL_Renderer *r, SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dest) {
  SDL_RenderCopy(r, tex, src, dest);
  SDL_RenderPresent(r);
}

void renderTextures(SDL_Renderer *r, SDL_Texture *texs[], SDL_Rect *rects[], int size) {
  SDL_SetRenderDrawColor(r, 153,51,255,255); // set to blue to fill background
  SDL_RenderClear(r);
  SDL_SetRenderDrawColor(r,255,255,255,255); // white rectangle. 
  for (int i = 0; i < size; i++) {
    SDL_RenderCopy(r, texs[i], NULL, rects[i]);
  }
  SDL_RenderDrawRect(r, rects[size]);
  SDL_RenderPresent(r);
}

int main( int argc, char *argv[]){
    FILE* f = NULL;
    
    f = fopen("./log.txt", "w+"); // TODO Make the log file do more.
    
    if (f == NULL) {
      printf("couldn't open file");
      exit(1);
    }

    printf("opened log file\n");

    int SCREEN_WIDTH =1280;
    int SCREEN_HEIGHT =1024;
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window *window=NULL;
    string currentSelection="Super Mario Sunshine";
    window = SDL_CreateWindow("GameCube", 
			     SDL_WINDOWPOS_UNDEFINED,
			     SDL_WINDOWPOS_UNDEFINED,
			     SCREEN_WIDTH, 
			     SCREEN_HEIGHT,       SDL_WINDOW_MAXIMIZED);
    if (window!= NULL)
      printf("created window\n");
    
    SDL_Surface *screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
      printf("screen is null, exiting\n");
      exit(1);
    }
    
    SDL_GameController *controller;

    for (int i = 0; i < 4; i++) {
      if (SDL_IsGameController(i)) {
	controller = SDL_GameControllerOpen(i);
	printf("found controller\n");
	break;
      }
    }

    bool controllerExists;
    if (controller == NULL) {
      controllerExists = false;
      printf("No controllers found\n");
    }
    else {
      controllerExists = true;
    }

    while(!controllerExists) {
      for (int i = 0; i < 4; i++) {
	if (SDL_IsGameController(i)) {
	  controller = SDL_GameControllerOpen(i);
	  printf("found controller\n");
	  controllerExists = true;
	  break;
	}
	printf("no controller found\n");
      }
    }
    
    //    SDL_Rect box1, box2, box3, box4, logoRect; // rects we're gonna render to
    SDL_Rect box1 = { (2*SCREEN_WIDTH)/32, (6*SCREEN_HEIGHT)/18, BMPSIZE, BMPSIZE};
    SDL_Rect box2 = { (13*SCREEN_WIDTH)/32, (6*SCREEN_HEIGHT)/18, BMPSIZE, BMPSIZE };
    SDL_Rect box3 = { ((24*SCREEN_WIDTH) / 32), (6*SCREEN_HEIGHT)/18, BMPSIZE, BMPSIZE};
    SDL_Rect logoRect = { (10*SCREEN_WIDTH)/32, 10, 768, 176 };

    SDL_Rect selectorRect = { box1.x-5, box1.y-5, BMPSIZE+10, BMPSIZE+10};
    printf("box1: ");
    printRect(&box1);
    printf("box2: ");
    printRect(&box2);
    printf("box3: ");
    printRect(&box3);
    printf("logo: ");
    printRect(&logoRect);
    printf("selectorRect: ");
    printRect(&selectorRect);
   
    

    // surfaces we're gonnna create the textures with
    SDL_Surface *game1s;
    SDL_Surface *game2s;
    SDL_Surface *game3s;
    SDL_Surface  *logos;
    SDL_Surface *gameSelectors;
    
    game1s = SDL_LoadBMP("/usr/local/GamecubeUI/res/sunshine.bmp");
    game2s = SDL_LoadBMP("/usr/local/GamecubeUI/res/melee.bmp");
    game3s = SDL_LoadBMP("/usr/local/GamecubeUI/res/sonicheroes.bmp");
    logos = SDL_LoadBMP("/usr/local/GamecubeUI/res/gamecubelogo.bmp");
    gameSelectors = SDL_LoadBMP("/usr/local/GamecubeUI/res/selector.bmp");
    
    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 153,51,255,255);
    SDL_RenderClear(renderer);
    SDL_Texture *game1, *game2, *game3, *logo, *gameSelector;
    game1 = SDL_CreateTextureFromSurface(renderer, game1s);
    game2 = SDL_CreateTextureFromSurface(renderer, game2s);
    game3 = SDL_CreateTextureFromSurface(renderer, game3s);
    logo = SDL_CreateTextureFromSurface(renderer, logos);
    gameSelector = SDL_CreateTextureFromSurface(renderer, gameSelectors);

    SDL_FreeSurface(game1s);
    SDL_FreeSurface(game2s);
    SDL_FreeSurface(game3s);
    SDL_FreeSurface(logos);
    SDL_FreeSurface(gameSelectors);

    SDL_Texture *textures[] = { game1, game2, game3, logo }; 
    SDL_Rect *rects[] = { &box1, &box2, &box3, &logoRect, &selectorRect };
    bool gameLoaded = false;
    // render selector
    SDL_Event event;
    bool running = true;
    bool youveGoneBackToZero = false;
    //creates loop for the main window
    while(running && !gameLoaded) {   // keeps the window open until quit is pressed
		  while(SDL_PollEvent( &event)){
		    //printf("entered event loop\n");
			  if(event.type == SDL_QUIT){
				  running = false;
				  break;
			  }
#define RECT_DISTANCE 440
			  if (event.type == SDL_CONTROLLERAXISMOTION) {
			    printf("event axis motion\n");
			    if (event.caxis.which == 0) {
			      if (!youveGoneBackToZero && event.caxis.value > LEFT_DEADZONE && event.caxis.value < RIGHT_DEADZONE) {
				youveGoneBackToZero = true; 
			      }
			      if (event.caxis.value < LEFT_DEADZONE && youveGoneBackToZero) {
				youveGoneBackToZero = false;
				switch (selectorRect.x){
				case 515:
				  selectorRect.x -= RECT_DISTANCE;
				  break;
				case 955:
				  selectorRect.x -= RECT_DISTANCE;
				  break;
				}
			      }
			      if (event.caxis.value > RIGHT_DEADZONE && youveGoneBackToZero) {
				youveGoneBackToZero = false;
				switch(selectorRect.x) {
				case 515:
				  selectorRect.x += RECT_DISTANCE;
				  break;
				case 75:
				  selectorRect.x += RECT_DISTANCE;
				  break;
				}
			      }
			    }
			  }
			

			      if (event.type == SDL_CONTROLLERBUTTONDOWN) {
				  if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
				    if (selectorRect.x == (box1.x-5)) { 
				      gameLoaded = true;
				      executeDolphin(SUNSHINE, window);
				    }
				    if (selectorRect.x == (box2.x-5)) {
				      gameLoaded = true;
				      executeDolphin(MELEE, window);
				    }
				    if (selectorRect.x == (box3.x-5)) {
				      gameLoaded = true;
				      executeDolphin(SONICHEROES, window);
				    }
				  }

			      }
			  
			  
			  //  SDL_RenderPresent(renderer);
		  } // end pollevent loop
	          renderTextures(renderer, textures, rects, 4); // render textures while running
    } // end main loop
    // free up some memory
    SDL_DestroyTexture(game1);
    SDL_DestroyTexture(game2);
    SDL_DestroyTexture(game3);
    SDL_DestroyTexture(logo);
    SDL_GameControllerClose(controller);
    SDL_FreeSurface(screen);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
