#include "c_img.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int square_gradient(struct rgb_img *im, int y, int x) {
  
  // delta_y is y2 - y1 ([y+1] - [y-1])
  // delta_x is x2 - x1 ([x+1] - [x-1])
  // for 3x4.bin, width is 3 and height is 4
  
  int y2;
  int y1;
  int x2;
  int x1;
  
  if (y == 0) {
    y1 = im->height-1;
    y2 = y + 1;
  }
  else if (y == im->height-1) {
    y1 = y - 1;
    y2 = 0;
  }
  else {
    y1 = y - 1;
    y2 = y + 1;
  }
  // Wrap around y
  
  if (x == 0) {
    x1 = im->width-1;
    x2 = x + 1;
  }
  else if (x == im->width-1) {
    x1 = x - 1;
    x2 = 0;
  }
  else {
    x1 = x - 1;
    x2 = x + 1;
  }
  // Wrap around x
  
  x1 > im->width-1 || x1 < 0 || x2 > im->width-1 || x2 < 0  ? printf("Wraparound Error in X dimension\n") : NULL;
  y1 > im->height-1 || y1 < 0 || y2 > im->height-1 || y2 < 0  ? printf("Wraparound Error in Y dimension\n") : NULL;
  // Error handling

  int r2_y = get_pixel(im, y2, x, 0);
  int g2_y = get_pixel(im, y2, x, 1);
  int b2_y = get_pixel(im, y2, x, 2);
  int r1_y = get_pixel(im, y1, x, 0);
  int g1_y = get_pixel(im, y1, x, 1);
  int b1_y = get_pixel(im, y1, x, 2);

  int r2_x = get_pixel(im, y, x2, 0);
  int g2_x = get_pixel(im, y, x2, 1);
  int b2_x = get_pixel(im, y, x2, 2);
  int r1_x = get_pixel(im, y, x1, 0);
  int g1_x = get_pixel(im, y, x1, 1);
  int b1_x = get_pixel(im, y, x1, 2);
  // Getting RGB values

  int r_y = r2_y - r1_y;
  int g_y = g2_y - g1_y;
  int b_y = b2_y - b1_y;
  int r_x = r2_x - r1_x;
  int g_x = g2_x - g1_x;
  int b_x = b2_x - b1_x;
  // Delta RGB calculation

  int delta_y = pow(r_y, 2) + pow(g_y, 2) + pow(b_y, 2);
  int delta_x = pow(r_x, 2) + pow(g_x, 2) + pow(b_x, 2);
  int gradient = delta_y + delta_x;
  int gradient_squared = pow(gradient, 0.5);
  // Gradient calculation
  
  return gradient_squared;

  
  /*
  //Testing Infrastructure - REMOVE WHEN SUBMITTING
  printf("y2: %d\ty1: %d\nx2: %d\tx1: %d\n", y2, y1, x2, x1);
  printf("RGB1_y: (%d, %d, %d)\nRGB2_y: (%d, %d, %d)\n", r1_y, g1_y, b1_y, r2_y, g2_y, b2_y);
  printf("RGB1_x: (%d, %d, %d)\nRGB2_x: (%d, %d, %d)\n", r1_x, g1_x, b1_x, r2_x, g2_x, b2_x);
  printf("Delta RGB Y: (%d,%d,%d)\n", r_y, g_y, b_y);
  printf("Delta RGB X: (%d,%d,%d)\n", r_x, g_x, b_x);
  printf("Gradient: %d\n\n", gradient);
  //Testing Infrastructure - REMOVE WHEN SUBMITTING
  */
}

void calc_energy(struct rgb_img *im, struct rgb_img **grad) {
  create_img(grad, im->height, im->width);
  
  for(int y = 0; y < im->height; y++) {
    for(int x = 0; x < im->width; x++) {
      int energy = square_gradient(im, y, x);
      uint8_t dual_gradient = (energy)/10;
      // uint conversion

      set_pixel(*grad, y, x, dual_gradient, dual_gradient, dual_gradient);
      // Storing in image

      //TEST PRINT STATEMENT - REMOVE WHEN SUBMITTING
      printf("%d\t", dual_gradient);
    }
    //TEST PRINT STATEMENT - REMOVE WHEN SUBMITTING
    printf("\n");
  }
}


int main(void) {
  
  struct rgb_img *grad;
  struct rgb_img im;
  struct rgb_img *p_im = &im;
  read_in_img(&p_im, "3x4.bin");
  
  
  //Test Infrastructure - REMOVE WHEN SUBMITTING
  printf("Width: %d\nHeight: %d\n\n", (int)p_im->width, (int)p_im->height);
  square_gradient(p_im, 0, 1);
  calc_energy(p_im, &grad);
  printf("\nGrad:\n");
  print_grad(grad);
  return 0;
  // End of Test Infrastructure - REMOVE WHEN SUBMITTING
  
  
  return 0;
}

// Hassan Tahir - 2023/04/09
