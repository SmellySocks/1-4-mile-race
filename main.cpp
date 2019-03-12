#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int fps = 60;


int main( int argc, char* agrs[])
{
	SDL_Window* window = NULL;
	SDL_Surface *background = NULL;
	SDL_Surface *vehicle = NULL;
	SDL_Surface *screen = NULL;
    SDL_Renderer *renderer = NULL;
	SDL_Texture *texture = NULL;
	SDL_Texture *carTexture = NULL;
	SDL_Texture *message = NULL;
	SDL_Rect CarRect;
	CarRect.x=15;
	CarRect.y=440;
	CarRect.w=40;
	CarRect.h=40;
	
	SDL_Init (SDL_INIT_EVERYTHING );
	SDL_Rect camera;
    camera.x = 0; //Don't worry about this camera, I need this after i get the background working.
    camera.y = 0;
    camera.w = 640;
    camera.h = 480;
    bool b[2] = {0,0};
    int x = 0, y = 0;
    Uint32 start;
	if ( SDL_Init (SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	
	else 
	{
		 window = SDL_CreateWindow( "1/4 Mile sim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		 
		 if( window == NULL )
		 {
			  printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() ); 
		 }
		 else
		 {
			background = SDL_LoadBMP("background.bmp");
			vehicle = SDL_LoadBMP("Hyundai.bmp");
			if(background == NULL || vehicle == NULL)
			{
				SDL_ShowSimpleMessageBox(0, "Background init error",         SDL_GetError(), window);
			}
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if(renderer == NULL)
			{
				SDL_ShowSimpleMessageBox(0, "Renderer init error", SDL_GetError(), window);
			}
			texture = SDL_CreateTextureFromSurface(renderer,background);
			carTexture = SDL_CreateTextureFromSurface(renderer,vehicle);
			if(texture == NULL || carTexture==NULL)
			{
				SDL_ShowSimpleMessageBox(0, "Texture init error", SDL_GetError(), window);
			}
			SDL_SetColorKey (background, SDL_TRUE, SDL_MapRGB(background->format,255,255,255));
				//SDL_RenderCopy(renderer, texture, &camera, NULL);
				//SDL_RenderCopy(renderer, carTexture, &CarRect, NULL);
				SDL_RenderPresent(renderer);
		}
	 }
	 
	bool move = false;
    bool running = true;
    while (running)
    {
        start = SDL_GetTicks();
        SDL_Event event;
        

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                running = false;
                cout<<"terminting"<<endl;
                SDL_DestroyTexture(texture);
                SDL_DestroyTexture(texture);
                SDL_FreeSurface(background);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    move=true;
                    break;
                case SDLK_LEFT:
                    b[1]=1;
                    break;
				case SDLK_d:
					//zmiana biegu
					break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                   
                    break;
                case SDLK_LEFT:
                    break;
                }
                break;
            }
            
          }
          if(1000/fps>SDL_GetTicks()-start)
        {
            SDL_Delay(1000/fps-(SDL_GetTicks() - start));  
          if(move)
        {
            
            camera.x += 5;
           
            if(camera.x >=4200-640)
            {
				camera.x=4200-640;	
				
        }
        
        else if(move==false)
        {
			
        }
	}
        
        SDL_BlitSurface(vehicle, NULL, screen, &CarRect);
        SDL_BlitSurface(background, &camera, screen, NULL);
       SDL_RenderCopy(renderer, texture, &camera, NULL);
        SDL_RenderCopy(renderer, carTexture, NULL, &CarRect);
        SDL_RenderPresent(renderer);
        
	}
	 
 }
 SDL_Quit();
 return 0;
}

