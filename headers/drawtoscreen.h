#include <SDL.h>
#include <stdio.h>

Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    //Address to pixel we want
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;
    case 2:
        return *(Uint16 *)p;
        break;
    case 3:
        if(SDL_BYTEORDER  == SDL_BIG_ENDIAN)
        {
            return p[0] << 16 | p[1] << 8 |p[2];
        
        }
        else
        {
            return p[0] | p[1] << 8 | p[2] << 16;
        }
        break;
    case 4:
        return *(Uint32 *)p;
        break;

    }
}

void putPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } 
        else 
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;

    }
}

//Draw images to screen
void display_bmp(const char *file_name, SDL_Renderer *renderer)
{
    SDL_Surface *image_surface = SDL_LoadBMP(file_name);
    if(image_surface == NULL)
    {
        fprintf(stderr,"could not load BMP file '%s\n'", file_name,SDL_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    SDL_FreeSurface(image_surface);
    if(texture ==NULL)
    {
        fprintf(stderr,"could not create texture from BMP file '%s\n'", file_name, SDL_GetError());
        return;
    }
    SDL_RenderClear(renderer);
    if(SDL_RenderCopy(renderer,texture,NULL,NULL)<0)
    {
        fprintf(stderr,"Could not copy texture %s\n", SDL_GetError());
        return;
    }

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}