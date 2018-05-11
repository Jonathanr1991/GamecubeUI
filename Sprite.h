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
