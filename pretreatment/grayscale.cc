#include "grayscale.hh"
#include "../tools/surface.hh"

SDL_Surface *grayscale(SDL_Surface *src)
{
  SDL_Surface *tmp = create_surface(src->w, src->h);

  Uint8 r, g, b;
  float gray;
  Uint32 pixel;
  for (int i = 0; i < src->w; ++i)
  {
    for (int j = 0; j < src->h; ++j)
    {
      pixel = getpixel(src, i, j);
      SDL_GetRGB(pixel, src->format, &r, &g, &b);
      gray = 0.3 * r + 0.59 * g + 0.11 * b;
      pixel = SDL_MapRGB(tmp->format, gray, gray, gray);
      putpixel(tmp, i, j, pixel);
    }
  }

  return tmp;
}
