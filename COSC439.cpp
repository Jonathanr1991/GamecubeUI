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

		Sprite(Uint32 color,int x,int y, int w, int h)
		{
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
int main( int argc, char *argv[]){
	
	int SCREEN_WIDTH =1280;
	int SCREEN_HEIGHT =720;
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Window *window=NULL;

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

	SDL_Rect logoLocation;
	logoLocation.x=(10*SCREEN_WIDTH)/32;
	logoLocation.y=10;

	SDL_Event keyPress;
	

// Pictures for game menu set up
	game1=SDL_LoadBMP("sunshine.bmp");
	game2=SDL_LoadBMP("smash.bmp");
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

//SDL_BlitSurface(gameSelector, NULL, screen, &gameSelectorLocation);

	

	Uint32 starting_tick;
	SDL_Event event;
	bool running = true;
 	//creates loop for the main window
	while( running) {   // keeps the window open until quit is pressed
		starting_tick=SDL_GetTicks();
		while( SDL_PollEvent( &event)){
			
			if( event.type == SDL_QUIT){
				running = false;
				break;
			}
			else if(event.type==SDL_KEYDOWN){
		switch(event.key.keysym.sym)
	{
			case SDLK_RIGHT:
				printf("right");
				gameSelectorLocation.x=(10*SCREEN_WIDTH)/32-10;
				
				break;
			
				

			 case SDLK_LEFT:
				gameSelectorLocation.x =(2*SCREEN_WIDTH)/32-10;
				break;
	}
}
			SDL_BlitSurface(gameSelector, NULL, screen, &gameSelectorLocation);
			SDL_UpdateWindowSurface(window);
		}
		
		if (( 1000/fps)>SDL_GetTicks()-starting_tick){
		SDL_Delay(1000/fps-(SDL_GetTicks()-starting_tick));
		}

	}

	
	
	
	SDL_Quit();
	return 0;
						
}
