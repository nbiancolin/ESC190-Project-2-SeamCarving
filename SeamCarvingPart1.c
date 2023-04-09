#include "c_img.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  printf("Hello World\n");

  struct rgb_img im;
  struct rgb_img *p_im = &im;

  read_in_img(&p_im, "image(3).bin");
  system("ls");
  printf("clear");

  int height = p_im->height;
  int width = p_im->width;
  printf("clear");

  printf("%d %d", p_im->height, p_im->width);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {

      int r = 2 * get_pixel(p_im, i, j, 0);
      int g = 2 * get_pixel(p_im, i, j, 1);
      int b = 2 * get_pixel(p_im, i, j, 2);
      
      r = r > 255 ? 255 : r;
      g = g > 255 ? 255 : g;
      b = b > 255 ? 255 : b;

      set_pixel(p_im, i, j, r, g, b);

      write_img(p_im, "image.bin");

      // get red green and blue and store them in int r,g,b
      // set pixel with a sm of r g and b
      // at end write img
    }
  }

  return 0;
}

// Hassan Tahir - 2023/04/09