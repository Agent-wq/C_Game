#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <drawtoscreen.h>


int main(int argc, char *argv[]) 
{
    const int SCREEN_WIDTH = 1024;
    const int SCREEN_BREADTH = 720;
    
    SDL_Surface *screen;
    SDL_Window *window = NULL;


    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr,"SDL could not initialize! SDL_Error: %s\n",SDL_GetError());
        // exit(-1);
    }
    else
    {
        window = SDL_CreateWindow("C_Game", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_BREADTH,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
    Uint32 yellow;
    Uint32 black;
    screen = SDL_GetWindowSurface(window);
    yellow = SDL_MapRGB(screen->format, 0xff, 0xff, 0x00);
    black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);  // Black color (for clearing)

    // x = screen->w / 2;
    // y = screen->h / 2;
 

    //lock the screen for direct access to pixels
    if(SDL_MUSTLOCK(screen))
    {
        if(SDL_LockSurface(screen) < 0)
        {
            fprintf(stderr ,"Can't lock screen\n", SDL_GetError());
            return 0;
        }
    }

    //test
    for (int i = 0; i < 20000; i++)
    {
        int x = rand() % screen->w;
        int y = rand() % screen->h;
        putPixel(screen,x,y,yellow);
    }
    SDL_UpdateWindowSurface(window);
    
    SDL_FillRect(screen, NULL, black);
    // SDL_UpdateWindowSurface(window);
    if(SDL_MUSTLOCK(screen))
    {
        SDL_UnlockSurface(screen);
    }

    //Input handling
    SDL_Event e;
    int quit =0;
    while(!quit)
    {
        while (SDL_PollEvent(&e))
        {

            switch (e.type)
            {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_a:
                    printf("move left\n");
                    break;
                case SDLK_d:
                    printf("move right\n");
                    break;
                case SDLK_w:
                    printf("move forward\n");
                    break;
                case SDLK_s:
                    printf("move backwards");
                    break;
                default:
                    break;
                }
                break;
            
            default:
                break;
            }
        }
        
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

