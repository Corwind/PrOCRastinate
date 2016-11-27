#include "events.hh"

void wait_for_keypressed(void)
{
  SDL_Event event;

  for(;;)
  {
      SDL_PollEvent(&event);
      switch (event.type)
      {
            case SDL_KEYDOWN:
              return;
            default:
              break;
          }
    }
}

