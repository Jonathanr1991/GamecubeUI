#include <SDL2/SDL.h>
#include "SDL.h"
#include <iostream>
#include <vector>
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "SDL_scancode.h"

#define fps 60
using namespace std;

class Sprite{

private:
  SDL_Surface *image;
  SDL_Rect rect;
  int origin_x, origin_y;
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
int main( int argc, char *argv[]){
    FILE* f = NULL;
    
    f = fopen("./log.txt", "w+");
    
    if (f == NULL) {
      printf("couldn't open file");
      exit(1);
    }

    fprintf(f,"opened log file\n");

	int SCREEN_WIDTH =1280;
	int SCREEN_HEIGHT =1024;
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Window *window=NULL;
	string currentSelection="Super Mario Sunshine";
	window= SDL_CreateWindow("GameCube", 
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					SCREEN_WIDTH, 
					SCREEN_HEIGHT,       SDL_WINDOW_RESIZABLE);

	SDL_Surface *screen = SDL_GetWindowSurface(window);



	SDL_Surface *game1,*game2, *game3=NULL;
	SDL_Surface *gameCubeLogo, *gameSelector=NULL;
	Uint32 blue = SDL_MapRGB(screen->format,0,0,150);
	Uint32 blue2 = SDL_MapRGB(screen->format,0,0,255);
	Uint32 white = SDL_MapRGB(screen->format,255,255,255);
	//main background color
	SDL_FillRect(screen, NULL, blue2);
	//Game 1 location main menu
	SDL_Rect box;
	box.x=(2*SCREEN_WIDTH)/32;
	box.y=(6*SCREEN_HEIGHT)/18;
	// game 2 location
	SDL_Rect box2;
	box2.x=(10*SCREEN_WIDTH)/32;
	box2.y=box.y;
	// game 3 location
	SDL_Rect box3;
	box3.x=(10*SCREEN_WIDTH)/32 +320;
	box3.y=box.y;

	SDL_Rect logoLocation;
	logoLocation.x=(10*SCREEN_WIDTH)/32;
	logoLocation.y=10;

	SDL_Event keyPress;
	

// Pictures for game menu set up
	game1=SDL_LoadBMP("sunshine.bmp");
	game2=SDL_LoadBMP("smash.bmp");
	game3=SDL_LoadBMP("sonicheroes.bmp");
	gameCubeLogo=SDL_LoadBMP("GamecubeLogo.bmp");
	gameSelector= SDL_LoadBMP("gameSelectorPic.bmp");

	Sprite topBox( blue,0,0, SCREEN_WIDTH,3*SCREEN_HEIGHT/18);
	topBox.draw(screen);
	Sprite bottomBox(blue,0,SCREEN_HEIGHT-SCREEN_HEIGHT/6,SCREEN_WIDTH, SCREEN_HEIGHT/6); 
	bottomBox.draw(screen);
	Sprite pressAToStartGame(white, (11*SCREEN_WIDTH)/32, (16*SCREEN_HEIGHT)/18, (10*SCREEN_WIDTH)/32, (SCREEN_HEIGHT)/18);
	pressAToStartGame.draw(screen);



// game selector 
	SDL_Rect gameSelectorLocation;
	gameSelectorLocation.x=(2*SCREEN_WIDTH)/32-10;
	gameSelectorLocation.y = (6*SCREEN_HEIGHT)/18-10;
	
    SDL_BlitSurface(gameCubeLogo,NULL,screen,&logoLocation);
    SDL_BlitSurface(game1,NULL,screen,&box);
    SDL_BlitSurface(game2,NULL,screen,&box2);
    SDL_BlitSurface(game3,NULL,screen,&box3);

    // TODO, make it recognize 4 controllers
    SDL_GameController *controller = NULL;
    SDL_Joystick *joy;
    
    for(int i = 0; i < SDL_NumJoysticks(); i++) {
      if(SDL_IsGameController(i)) {
	controller = SDL_GameControllerOpen(i);
	break;
      }
    }
    if (controller == NULL) {
      fprintf(f,"no controller found\n");
      fprintf(stdout, "critical failure\n");
      exit(1);
    }
    else if (controller != NULL) {
      fprintf(f,"found controller!!!!!!!!!");
      fprintf(f, SDL_GameControllerMapping(controller));
      fprintf(f, "\n");
    }

    joy = SDL_GameControllerGetJoystick(controller);
    
    SDL_Event event;
    bool running = true;
    //creates loop for the main window
    while( running) {   // keeps the window open until quit is pressed
      while( SDL_PollEvent( &event)){
			
	if( event.type == SDL_QUIT){
	  running = false;
	  break;
	}

	else if (event.type==SDL_CONTROLLERBUTTONDOWN) {
	  if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
	    fprintf(f, "A Button Pressed\n");
	  }
	}

	else if (event.type == SDL_JOYAXISMOTION) {
	  /*  if (event.jaxis.axis == 0) {
	    //   std:: cout << event.jaxis.value << std::endl;
	    fprintf(f, "value: %d\n", event.jaxis.value); 
	    }*/
	  if (event.type == SDL_JOYAXISMOTION) {
	    else if (event.jaxis.value < 8000) {
	      if (currentSelection.compare("Super Mario Sunshine") == 0) {
		currentSelection = advanceCurrentSelection(); // implement this method
		gameSelectorLocation.x = advanceGameSelector(); //implement this method 
	      }
	      else if (currentSelection.compare("Smash Bro") == 0) {
		currentSelection = advanceCurrentSelection();
		gameSelectorLocation.x = advanceGameSelector();
	      }
	      else if (currentSelection.compare("game3") == 0) { // SONIC GOES HERE
		currentSelection = advanceCurrentSelection(); // i think i have to make this a pointer.
	      }	      
	    }

	    else if (event.jaxis.value < -8000) {
	      
	    }
	  }
	}
	
	
	else if(event.type==SDL_JOYAXISMOTION){
	  switch(event.jaxis.value)
	    {
	    case 7000:
	      if(currentSelection.compare("Super Mario Sunshine")==0){
		gameSelectorLocation.x+=320;
		currentSelection="Smash Bro";		
	      }
		  
	      else if(currentSelection.compare("Smash Bro")==0) {
		gameSelectorLocation.x+=320;
		currentSelection="game3";				
	      }
		  
	      else if(currentSelection.compare("game3")==0) {		
		currentSelection="game3";
	      }
	      break;
				
	    case SDLK_LEFT:
	      if(currentSelection.compare("Super Mario Sunshine")==0) {
		  currentSelection="Super Mario Sunshine";
		}
	      else if(currentSelection.compare("Smash Bro")==0) {
		  gameSelectorLocation.x-=320;
		  currentSelection="Super Mario Sunshine";
				
		}
	      else if(currentSelection.compare("game3")==0) {
		  gameSelectorLocation.x-=320;
		  currentSelection="Smash Bro";
		}
	      
	      break;

	    case SDLK_DOWN:
	      if(currentSelection.compare("Super Mario Sunshine")==0) {
		  currentSelection="setting";
		}
	      else if(currentSelection.compare("Smash Bro")==0)	{	  
		  currentSelection="setting";				
		}
	      else if(currentSelection.compare("game3")==0) {	  
		  currentSelection="setting";		
		}
	      break;
        case SDLK_a:
	  cout<<currentSelection<<endl;
	  running=false;
	    }
	}
	
      }
       
      SDL_BlitSurface(gameSelector, NULL, screen, &gameSelectorLocation);
        
      SDL_UpdateWindowSurface(window);
	
    }
    SDL_Quit();
    return 0;
}
