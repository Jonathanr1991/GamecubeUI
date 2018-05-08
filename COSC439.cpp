#include <SDL2/SDL.h>
#include "SDL.h"
#include <iostream>
#include <vector>
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "SDL_scancode.h"
//#include "Sprite.h"
#include <SDL_gamecontroller.h>

#define ADVANCE_LEFT -1
#define ADVANCE_RIGHT 1
#define ADVANCE_DOWN 2
#define ADVANCE_UP 2

#define RIGHT_DEADZONE 8000
#define LEFT_DEADZONE -8000
#define DOWN_DEADZONE 8000
#define UP_DEADZONE -8000

#define SMASH "Smash Bros"
#define SONICHEROES "Sonic Heroes"
#define SUNSHINE "Super Mario Sunshine"

#define fps 60
using namespace std;

class Sprite{

private:

  SDL_Rect rect;
  int origin_x, origin_y;
  SDL_Surface *image;
public:

  Sprite(Uint32 color,int x,int y, int w, int h)  {
    image = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);

    SDL_FillRect(image, NULL, color);
    rect= image->clip_rect;
    origin_x=0;
    origin_y=0;
    rect.x=x- origin_x;
    rect.y=y-origin_y;

  }

  void update(){
  }
		
  void draw(SDL_Surface *destination){			
    SDL_BlitSurface(image,NULL,destination, &rect);
  }
								
		
		
};

/*
void log(char* string) {
  fprintf(f,string);
  }*/

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
			     SCREEN_HEIGHT,       SDL_WINDOW_RESIZABLE);
    if (window!= NULL)
      printf("created window\n");
    
    SDL_Surface *screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
      printf("screen is null, exiting\n");
      exit(1);
    }
    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, 0);
    printf("inited renderer\n");
    SDL_Surface *game1,*game2, *game3=NULL;
    SDL_Surface *gameCubeLogo, *gameSelector=NULL;
    Uint32 blue = SDL_MapRGB(screen->format,0,0,150);
    Uint32 blue2 = SDL_MapRGB(screen->format,0,0,255);
    Uint32 white = SDL_MapRGB(screen->format,255,255,255);
    printf("made colors and surfaces\n");
    //main background color
    SDL_FillRect(screen, NULL, blue2);
    printf("filled background\n");
    //Game 1 location main menu
    SDL_Rect box;
    box.x=(2*SCREEN_WIDTH)/32;
    box.y=(6*SCREEN_HEIGHT)/18;
    printf("made game1 box\n");
    // game 2 location
    SDL_Rect box2;
    box2.x=(10*SCREEN_WIDTH)/32;
    box2.y=box.y;
    printf("made game2 box\n");
    // game 3 location
    SDL_Rect box3;
    box3.x=(10*SCREEN_WIDTH)/32 +320;
    box3.y=box.y;
    printf("made game3 box\n");
    SDL_Rect logoLocation;
    logoLocation.x=(10*SCREEN_WIDTH)/32;
    logoLocation.y=10;
    printf("made logo box\n");
    
    // set the color for clearing the renderer to the background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // TODO figure out how to put blue2 here.
    printf("set renderer draw color\n");
    // Pictures for game menu set up
    game1=SDL_LoadBMP("sunshine.bmp");
    game2=SDL_LoadBMP("smash.bmp");
    game3=SDL_LoadBMP("sonicheroes.bmp");
    gameCubeLogo=SDL_LoadBMP("GamecubeLogo.bmp");
    gameSelector= SDL_LoadBMP("gameSelectorPic.bmp");
    printf("inited BMPs\n");

    // create sprites
    Sprite topBox( blue,0,0, SCREEN_WIDTH,3*SCREEN_HEIGHT/18);
    Sprite bottomBox(blue,0,SCREEN_HEIGHT-SCREEN_HEIGHT/6,SCREEN_WIDTH, SCREEN_HEIGHT/6); 
    bottomBox.draw(screen);
    Sprite pressAToStartGame(white, (11*SCREEN_WIDTH)/32, (16*SCREEN_HEIGHT)/18, (10*SCREEN_WIDTH)/32, (SCREEN_HEIGHT)/18);
    pressAToStartGame.draw(screen);
    printf("created Sprites\n");

    

    
    // GAME SELECTOR
    SDL_Rect gameSelectorLocation;
    SDL_Rect *gameSelectorLocation_p = &gameSelectorLocation;
    // set location of the rect
    gameSelectorLocation.x=(2*SCREEN_WIDTH)/32-10;
    gameSelectorLocation.y = (6*SCREEN_HEIGHT)/18-10;
    printf("inited gameSelector rect\n");
    // init the texture for the selector icon
    SDL_Texture *gameSelectorTexture = NULL;
    gameSelectorTexture = SDL_CreateTextureFromSurface(renderer, gameSelector);
    printf("created texture from surface\n");
    SDL_FreeSurface(gameSelector);
    printf("freed surface\n");
    
    // blit static BMPs
    if (gameCubeLogo != NULL && screen != NULL) {
      SDL_BlitSurface(gameCubeLogo,NULL,screen,&logoLocation);
      printf("blitted logo\n");
    }
    else {
      printf("can't blit, exiting\n");
      exit(1);
    }   
    
    SDL_BlitSurface(game1,NULL,screen,&box);
    printf("blitted game1\n");
    SDL_BlitSurface(game2,NULL,screen,&box2);
    printf("blittled game2\n");
    SDL_BlitSurface(game3,NULL,screen,&box3);
    printf("blittled game 3\n");
    printf("blited bmps\n");
    if (window != NULL) {
      SDL_UpdateWindowSurface(window);
    }
    else {
      printf("window is null\n");
      exit(1);
    }
    printf("updated window surface\n");
    // render the selector at the game 1 rect.
    SDL_RenderClear(renderer);
    printf("cleared renderer\n");
    SDL_RenderCopy(renderer, gameSelectorTexture, NULL, &box);
    printf("called rendercopy\n");
    SDL_RenderPresent(renderer);
    printf("called renderpresent\n");
    gameSelectorLocation_p = &box;
    printf( "rendered selector initially\n");
    SDL_GameController *controller;
    printf("controller created\n");

    for (int i = 0; i < SDL_NumJoysticks(); i++) {
      if (SDL_IsGameController(i)) {
	controller=SDL_GameControllerOpen(i);
	printf("found controller\n");
	break;
      }
    }
    // check to see if theres at least one controller 
    if (controller == NULL) {
      printf("No controllers exiting\n");
      exit(1);
    }
    // if there isn't a controller plugged in, do something about it
    // TODO make it do something so that a user can just plug a controller in.
    // run an idle loop.

    
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
						  if (SDL_RectEquals(gameSelectorLocation_p, &box) == SDL_TRUE) { // super mario sunshine is selected
							  if (event.caxis.value < RIGHT_DEADZONE) {
								  advanceSelection(renderer, gameSelectorTexture, &box, &box2);
								  gameSelectorLocation_p = &box2;
							  }
						  }

						  if (SDL_RectEquals(gameSelectorLocation_p, &box2) == SDL_TRUE) { // smash is selected
							  if (event.caxis.value < LEFT_DEADZONE) {
								  advanceSelection(renderer, gameSelectorTexture, &box2, &box);
								  gameSelectorLocation_p = &box;
							  }
							  else if (event.caxis.value < RIGHT_DEADZONE) {
								  advanceSelection(renderer, gameSelectorTexture, &box2, &box3);
								  gameSelectorLocation_p = &box3;
							  }
						  }

						  if (SDL_RectEquals(gameSelectorLocation_p, &box3) == SDL_TRUE) { // sonic heroes is selected.
							  if(event.caxis.value < LEFT_DEADZONE) {
								  advanceSelection(renderer, gameSelectorTexture, &box3, &box2);
								  gameSelectorLocation_p = &box2;
							  }
						  }
					  }
				  }
			  }

			  if (event.type == SDL_CONTROLLERBUTTONDOWN) {
				  if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
					  if (SDL_RectEquals(gameSelectorLocation_p, &box) == SDL_TRUE)
						  executeDolphin(SUNSHINE);
					  if (SDL_RectEquals(gameSelectorLocation_p, &box2) == SDL_TRUE)
						  executeDolphin(SMASH);
					  if (SDL_RectEquals(gameSelectorLocation_p, &box3) == SDL_TRUE)
						  executeDolphin(SONICHEROES);
				  }

			  }
		  } // end pollevent loop
    } // end main loop
    
    SDL_UpdateWindowSurface(window);
    
    SDL_Quit();
    return 0;
}
