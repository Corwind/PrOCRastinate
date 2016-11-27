#ifndef SURFACE_HH_PQJQUBI2
#define SURFACE_HH_PQJQUBI2

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_video.h>
#include <stddef.h>

void display_image(SDL_Surface *img, SDL_Renderer *renderer);

SDL_Surface *create_surface(size_t width, size_t heigth);

static inline Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

#endif /* end of include guard: SURFACE_HH_PQJQUBI2 */
