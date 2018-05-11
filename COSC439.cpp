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
#define LEFT_DEADZONE -8000
#define RIGHT_DEADZONE 8000

#define ADVANCE_LEFT -1
#define ADVANCE_RIGHT 1
#define ADVANCE_DOWN 2
#define ADVANCE_UP 2

#define SMASH "Smash Bros"
#define SONICHEROES "Sonic Heroes"
#define SUNSHINE "Super Mario Sunshine"

#define fps 60
using namespace std;

void printRect(SDL_Rect *r) {
  printf("x: %d y: %d, w: %d, h: %d\n", r->x, r->y, r->w, r->h);
}

void executeDolphin(string game) { // TODO put macros here
  if (game.compare("Smash Bros") == 0)
    system("dolphin-emu -e melee.iso");
  if (game.compare("Sonic Heroes") == 0)
    system("dolphin-emu -e sonicheroes.iso");
  if (game.compare("Super Mario Sunshine") == 0)
	  system("dolphin-emu -e supermariosunshine.iso");
    
}

void advanceSelection(SDL_Renderer *r, SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dest) {
  printf("advancing selection\n");
  SDL_RenderClear(r);
  SDL_RenderCopy(r, tex, src, dest);
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
			     SCREEN_HEIGHT,       SDL_WINDOW_FULLSCREEN);
    if (window!= NULL)
      printf("created window\n");
    
    SDL_Surface *screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
      printf("screen is null, exiting\n");
      exit(1);
    }

    //    SDL_Rect box1, box2, box3, box4, logoRect; // rects we're gonna render to
    SDL_Rect box1 = { (2*SCREEN_WIDTH)/32, (6*SCREEN_HEIGHT)/18, BMPSIZE, BMPSIZE};
    SDL_Rect box2 = { (10*SCREEN_WIDTH)/32, (6*SCREEN_HEIGHT)/18, BMPSIZE, BMPSIZE };
    SDL_Rect box3 = { ((10*SCREEN_WIDTH) / 32)+320, (6*SCREEN_HEIGHT)/18, BMPSIZE, BMPSIZE};
    SDL_Rect logoRect = { (10*SCREEN_WIDTH)/32, 10, 768, 176 };
    SDL_Rect *gameSelectorLocation = &box1;
    
    printf("box1: ");
    printRect(&box1);
    printf("box2: ");
    printRect(&box2);
    printf("box3: ");
    printRect(&box3);
    printf("logo: ");
    printRect(&logoRect);
    

    // surfaces we're gonnna create the textures with
    SDL_Surface *game1s;
    SDL_Surface *game2s;
    SDL_Surface *game3s;
    SDL_Surface  *logos;
    SDL_Surface *gameSelectors;
    
    game1s = SDL_LoadBMP("res/sunshine.bmp");
    game2s = SDL_LoadBMP("res/melee.bmp");
    game3s = SDL_LoadBMP("res/sonicheroes.bmp");
    logos = SDL_LoadBMP("res/gamecubelogo.bmp");
    gameSelectors = SDL_LoadBMP("res/selector.bmp");
    
    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
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
    // render games

    SDL_RenderCopy(renderer, game1, NULL, &box1);
    SDL_RenderCopy(renderer, game2, NULL, &box2);
    SDL_RenderCopy(renderer, game3, NULL, &box3);
    SDL_RenderCopy(renderer, logo, NULL, &logoRect);
    SDL_RenderPresent(renderer);
    
    SDL_Event event;
    bool running = true;
    //creates loop for the main window
    while(running) {   // keeps the window open until quit is pressed
		  while(SDL_PollEvent( &event)){
		    printf("entered event loop\n");
			  if(event.type == SDL_QUIT){
				  running = false;
				  break;
			  }

			  if (event.type == SDL_CONTROLLERAXISMOTION) {
			    printf("event axis motion\n");
				  if (event.caxis.which == 0) { // TODO MAKE SURE THIS WORKS WITH THE RIGHT AXIS!!!!!!!!!! IS THIS THE LEFT/RIGHT OR UP/DOWN ONE?
					  if (event.caxis.value < LEFT_DEADZONE) {
						  if (SDL_RectEquals(gameSelectorLocation, &box1) == SDL_TRUE) { // super mario sunshine is selected
							  if (event.caxis.value < RIGHT_DEADZONE) {
								  advanceSelection(renderer, gameSelector, &box1, &box2);
								  gameSelectorLocation = &box2;
								  printf("box1: moving right: %d\n", event.caxis.value);
							  }
						  }

						  if (SDL_RectEquals(gameSelectorLocation, &box2) == SDL_TRUE) { // smash is selected
							  if (event.caxis.value < LEFT_DEADZONE) {
								  advanceSelection(renderer, gameSelector, &box2, &box1);
								  gameSelectorLocation = &box1;
								  printf("box2: moving left: %d\n", event.caxis.value);
							  }
							  else if (event.caxis.value < RIGHT_DEADZONE) {
								  advanceSelection(renderer, gameSelector, &box2, &box3);
								  gameSelectorLocation = &box3;
								  printf("box2: moving right: %d\n", event.caxis.value);
							  }
						  }

						  if (SDL_RectEquals(gameSelectorLocation, &box3) == SDL_TRUE) { // sonic heroes is selected.
							  if(event.caxis.value < LEFT_DEADZONE) {
								  advanceSelection(renderer, gameSelector, &box3, &box2);
								  gameSelectorLocation = &box2;
								  printf("box3: moving left: %d\n", event.caxis.value);
							  }
						  }
					  }
				  }
			  }

			  if (event.type == SDL_CONTROLLERBUTTONDOWN) {
				  if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
					  if (SDL_RectEquals(gameSelectorLocation, &box1) == SDL_TRUE)
						  executeDolphin(SUNSHINE);
					  if (SDL_RectEquals(gameSelectorLocation, &box2) == SDL_TRUE)
						  executeDolphin(SMASH);
					  if (SDL_RectEquals(gameSelectorLocation, &box3) == SDL_TRUE)
						  executeDolphin(SONICHEROES);
				  }

			  }
		  } // end pollevent loop
    } // end main loop
    
    SDL_UpdateWindowSurface(window);
    
    SDL_Quit();
    return 0;
}
