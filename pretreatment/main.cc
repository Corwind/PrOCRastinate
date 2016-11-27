#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "grayscale.hh"

#include "../tools/events.hh"
#include "../tools/surface.hh"

int main(int argc, char *argv[])
{
  if (argc < 2)
    exit(1);

  SDL_Init( SDL_INIT_EVERYTHING );
  SDL_Window *display;
  display = SDL_CreateWindow("OCR", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_OPENGL);
  auto renderer = SDL_CreateRenderer(display, -1, SDL_RENDERER_ACCELERATED);

  auto src = IMG_Load(argv[1]);
  display_image(src, renderer);
  auto grayscaled_src = grayscale(src);
  display_image(grayscaled_src, renderer);
  SDL_DestroyWindow(display);
  SDL_Quit();
  return 0;
}
