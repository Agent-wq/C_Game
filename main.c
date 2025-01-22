#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <drawtoscreen.c>


int main(int argc, char *argv[]) 
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_BREADTH = 480;
    
    SDL_Surface *screen;
    SDL_Window *window = NULL;


    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n",SDL_GetError());
        // exit(-1);
    }
    else
    {
        window = SDL_CreateWindow("C_Game", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_BREADTH,SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

        }
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        printf("could not create renderer %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    //puts pixel 
    int x,y;
    Uint32 yellow;
    screen = SDL_GetWindowSurface(window);
    yellow = SDL_MapRGB(screen->format, 0xff, 0xff, 0x00);

    x = screen->w / 2;
    y = screen->h / 2;
    //lock the screen for direct access to pixels
    if(SDL_MUSTLOCK(screen))
    {
        if(SDL_LockSurface(screen) < 0)
        {
            fprintf(stderr ,"Can't lock screen\n", SDL_GetError());
            return 0;
        }
    }

    // Draw a horizontal line of yellow pixels
    for (int x = 100; x < 200; x++) 
    {
        for(int y = 150; y < 250; y++)
        {
            putPixel(screen, x,y, yellow); 
        }
    }

    SDL_UpdateWindowSurface(window);

    if(SDL_MUSTLOCK(screen))
    {
        SDL_UnlockSurface(screen);
    }
    

    //Keeps window from closing instantly
    SDL_Event event;
    int running = 1;
    while(running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }
        SDL_Delay(16);
    }

 

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

