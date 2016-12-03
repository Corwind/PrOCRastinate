#ifndef CONVOLUTION_HH_HUAJ1XJC
#define CONVOLUTION_HH_HUAJ1XJC

#include <vector>

#include <SDL.h>
#include <SDL_image.h>

typedef struct
{
  int length;
  std::vector<std::vector<float>> array;
} kernel;

SDL_Surface *apply_convolution(SDL_Surface *src, kernel *k);

#endif /* end of include guard: CONVOLUTION_HH_HUAJ1XJC */
