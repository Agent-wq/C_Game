#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>

void display_bmp(const char *file_name, SDL_Renderer *renderer)
{
    SDL_Surface *image_surface = SDL_LoadBMP(file_name);
    if(image_surface == NULL)
    {
        printf("could not load BMP file '%s\n'", file_name,SDL_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    SDL_FreeSurface(image_surface);
    if(texture ==NULL)
    {
        printf("could not create texture from BMP file '%s\n'", file_name, SDL_GetError());
        return;
    }
    SDL_RenderClear(renderer);
    if(SDL_RenderCopy(renderer,texture,NULL,NULL)<0)
    {
        printf("Could not copy texture %s\n", SDL_GetError());
        return;
    }

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);

}
int main(int argc, char *argv[]) 
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_BREADTH = 480;

    SDL_Window *window = NULL;
    // SDL_Renderer *renderer = NULL;

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

    // display_bmp("res/sample1.bmp",renderer); //with this approach i can load the only one image that is added
    display_bmp(argv[1],renderer); //with this i can render any bmp file i specify in the command
    
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

