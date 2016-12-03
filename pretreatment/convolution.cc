#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <memory>

#include "convolution.hh"
#include "../tools/surface.hh"

using thread_vector = std::vector<std::thread>;

void apply(SDL_Surface *src, SDL_Surface *dst, kernel *kern, int start_h,
           int end_h)
{
  int index_i, index_j, sum_r, sum_g, sum_b;
  Uint8 r, g, b;
  Uint32 pixel;
  int div = kern->length * kern->length;
  for (int k = start_h; k < (end_h - kern->length / 2) + 1; ++k)
    for (int j = 0; j < src->w; ++j)
    {
      sum_b = sum_g = sum_r = 0;
      for (int l = 0; l < kern->length; ++l)
      {
        index_i = (j + l);
        index_i = (index_i > 0 ? (index_i < src->w ? index_i : src->w - kern->length / 2 - 1) : 0);
        for (int m = 0; m < kern->length; ++m)
        {
          index_j = (k + m);
          index_j = (index_j >= 0 ? (index_j < end_h ? index_j : end_h - kern->length / 2 - 1) : 0);
          pixel = getpixel(src, index_i, index_j);
          SDL_GetRGB(pixel, src->format, &r, &g, &b);
          sum_r += r * kern->array[l][m] / div;
          sum_g += g * kern->array[l][m] / div;
          sum_b += b * kern->array[l][m] / div;
        }
      }
      sum_r = (sum_r >= 255 ? 255 : (sum_r >= 0 ? sum_r : 0));
      sum_g = (sum_g >= 255 ? 255 : (sum_g >= 0 ? sum_g : 0));
      sum_b = (sum_b >= 255 ? 255 : (sum_b >= 0 ? sum_b : 0));
      pixel = SDL_MapRGB(dst->format, sum_r, sum_g, sum_b);
      if (((j + kern->length / 2) < dst->w) && ((k + kern->length / 2) < dst->h))
        putpixel(dst, j + kern->length / 2, k + kern->length / 2, pixel);
    }
}

SDL_Surface *apply_convolution(SDL_Surface *src, kernel *k)
{
  SDL_Surface *tmp = create_surface(src->w, src->h);
  unsigned int nb_threads = std::thread::hardware_concurrency();
  unsigned int h = src->h / nb_threads;
  thread_vector tv;
  tv.reserve(nb_threads);
  for (unsigned int i = 0; i < nb_threads; ++i) {
    tv.push_back(std::thread(apply, src, tmp, k, i * h, (i + 1) * h));
  }
  for (unsigned int i = 0; i < nb_threads; ++i) {
    tv[i].join();
  }
  return tmp;
}
