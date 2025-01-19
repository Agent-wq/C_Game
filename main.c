#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>

int main() 
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_BREADTH = 480;

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

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
        screenSurface = SDL_GetWindowSurface(window);
        // SDL_FillRect(screenSurface,NULL,SDL_MapRGB(screenSurface -> format, 0xFF, 0xFF, 0xFF)); //Makes the screen white
        SDL_UpdateWindowSurface(window);

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
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}