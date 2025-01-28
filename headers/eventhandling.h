#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

void handleInput()
{
    SDL_Event input;
    SDL_Event closeWindow;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&input))
        {
            switch (input.type)
            {
            case SDL_KEYDOWN:
                switch (input.key.keysym.sym)
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
                    printf("move backwards\n");
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
                default:
                    break;
                }
                break;
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
            }
        }
        
    }
}
