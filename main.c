#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <drawtoscreen.h>
#include <eventhandling.h>

int main(int argc, char *argv[]) 
{
    const int SCREEN_WIDTH = 1366;
    const int SCREEN_HEIGHT = 768;
    
    SDL_Surface *screen;
    SDL_Window *window = NULL;


    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr,"SDL could not initialize! SDL_Error: %s\n",SDL_GetError());
        // exit(-1);
    }
    else
    {
        window = SDL_CreateWindow("C_Game", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
        if(window == NULL)
        {
            fprintf(stderr,"Window could not be created! SDL_Error: %s\n", SDL_GetError());

        }
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        fprintf(stderr,"could not create renderer %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    //puts pixel 
    int x,y;
    Uint32 black;
    Uint32 white;
    Uint32 yellow;
    screen = SDL_GetWindowSurface(window);
    yellow = SDL_MapRGB(screen->format,0xFF, 0xFF, 0x00);
    black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);  // Black color (for clearing)
    white = SDL_MapRGB(screen->format,0xff, 0xff, 0xff);

    //lock the screen for direct access to pixels
    if(SDL_MUSTLOCK(screen))
    {
        if(SDL_LockSurface(screen) < 0)
        {
            fprintf(stderr ,"Can't lock screen\n", SDL_GetError());
            return 0;
        }
    }

    //Render Ground
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        for (int y = screen->h - 100; y < SCREEN_HEIGHT; y++)
        {
            putPixel(screen,x,y,white);
        }
    }
 
    
    SDL_UpdateWindowSurface(window);
    SDL_FillRect(screen, NULL, black);

    if(SDL_MUSTLOCK(screen))
    {
        SDL_UnlockSurface(screen);
    }

    //event handling
    handleInput();

    SDL_DestroyWindowSurface(window);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}