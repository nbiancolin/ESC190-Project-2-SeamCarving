#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "c_img.h"
#include <limits.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y)) //Don't really need this but I figured I'd write it anyways
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
//Somehow there are no default min or max functions, so, we writing our own boys.


void calc_energy(struct rgb_img *im, struct rgb_img **grad) {


    read_in_img(&im, "../3x4.bin");
    int width = im->width;
    int height = im->height;

    //do edge cases first
    //then main loop from 1 to len-1

    for(int i = 0; i < height; i++){ //This is for the entire row j = 0
        int curPix[3], pixUp[3], pixDown[3], pixLeft[3], pixRight[3];

        for(int k = 0; k <3; k++) {
            curPix[k] = get_pixel(im, i, 0, k);
            pixUp[k] = get_pixel(im, i - 1, 0, k);
            pixDown[k] = get_pixel(im, i + 1, 0, k);
            pixLeft[k] = get_pixel(im, i, width, k);
            pixRight[k] = get_pixel(im, i, 1, k);
        }
        int Rx, Gx, Bx, Ry, Gy, By;

        Rx = pixDown[0] - pixUp[0];
        Gx = pixDown[1] - pixUp[1];
        Bx = pixDown[2] - pixUp[2];

        Ry = pixRight[0] - pixLeft[0];
        Gy = pixRight[1] - pixLeft[1];
        By = pixRight[2] - pixLeft[2];

        //calculate energy
        int deltaX = Rx*Rx + Gx*Gx + Bx*Bx;
        int deltaY = Ry*Ry + Gy*Gy + By*By;
        int energy = sqrt(deltaX + deltaY);

        uint8_t res = energy/10; //Is this right?? I think so but not totally sure... //I think this is right now

        set_pixel(*grad, i, 0, res, 0,0);

    }

    for(int i = 0; i < height; i++){ //j = width
        int curPix[3], pixUp[3], pixDown[3], pixLeft[3], pixRight[3];

        for(int k = 0; k <3; k++) {
            curPix[k] = get_pixel(im, i, width, k);
            pixUp[k] = get_pixel(im, i - 1, width, k);
            pixDown[k] = get_pixel(im, i + 1, width, k);
            pixLeft[k] = get_pixel(im, i, width - 1, k);
            pixRight[k] = get_pixel(im, i, 0, k);
        }
        int Rx, Gx, Bx, Ry, Gy, By;

        Rx = pixDown[0] - pixUp[0];
        Gx = pixDown[1] - pixUp[1];
        Bx = pixDown[2] - pixUp[2];

        Ry = pixRight[0] - pixLeft[0];
        Gy = pixRight[1] - pixLeft[1];
        By = pixRight[2] - pixLeft[2];

        //calculate energy
        int deltaX = Rx*Rx + Gx*Gx + Bx*Bx;
        int deltaY = Ry*Ry + Gy*Gy + By*By;
        int energy = sqrt(deltaX + deltaY);

        uint8_t res = energy/10; //Is this right?? I think so but not totally sure... //I think this is right now

        set_pixel(*grad, i, width, res, 0,0);
    }

    for(int j = 0; j < width; j++){ //i == 0
        int curPix[3], pixUp[3], pixDown[3], pixLeft[3], pixRight[3];

        for(int k = 0; k <3; k++) {
            curPix[k] = get_pixel(im, 0, j, k);
            pixUp[k] = get_pixel(im, height, j, k);
            pixDown[k] = get_pixel(im, 1, j, k);
            pixLeft[k] = get_pixel(im, 0, j - 1, k);
            pixRight[k] = get_pixel(im, 0, j + 1, k);
        }
        int Rx, Gx, Bx, Ry, Gy, By;

        Rx = pixDown[0] - pixUp[0];
        Gx = pixDown[1] - pixUp[1];
        Bx = pixDown[2] - pixUp[2];

        Ry = pixRight[0] - pixLeft[0];
        Gy = pixRight[1] - pixLeft[1];
        By = pixRight[2] - pixLeft[2];

        //calculate energy
        int deltaX = Rx*Rx + Gx*Gx + Bx*Bx;
        int deltaY = Ry*Ry + Gy*Gy + By*By;
        int energy = sqrt(deltaX + deltaY);

        uint8_t res = energy/10; //Is this right?? I think so but not totally sure... //I think this is right now

        set_pixel(*grad, 0, j, res, 0,0);


    }

    for(int j = 0; j < width; j++){ //i == height
        int curPix[3], pixUp[3], pixDown[3], pixLeft[3], pixRight[3];

        for(int k = 0; k <3; k++) {
            curPix[k] = get_pixel(im, height, j, k);
            pixUp[k] = get_pixel(im, height - 1, j, k);
            pixDown[k] = get_pixel(im, 0, j, k);
            pixLeft[k] = get_pixel(im, height, j - 1, k);
            pixRight[k] = get_pixel(im, height, j + 1, k);
        }
        int Rx, Gx, Bx, Ry, Gy, By;

        Rx = pixDown[0] - pixUp[0];
        Gx = pixDown[1] - pixUp[1];
        Bx = pixDown[2] - pixUp[2];

        Ry = pixRight[0] - pixLeft[0];
        Gy = pixRight[1] - pixLeft[1];
        By = pixRight[2] - pixLeft[2];

        //calculate energy
        int deltaX = Rx*Rx + Gx*Gx + Bx*Bx;
        int deltaY = Ry*Ry + Gy*Gy + By*By;
        int energy = sqrt(deltaX + deltaY);

        uint8_t res = energy/10; //Is this right?? I think so but not totally sure... //I think this is right now

        set_pixel(*grad, height, j, res, 0,0);
    }


    for(int i = 1; i < (height-1); i++){
        for(int j = 1; j < (width-1); j++){

            /**
            * New method of storing RGB: By pixel lmao
            * 0th is Red
            * 1st is Green
            * 2nd is Blue
             */

           int curPix[3], pixUp[3], pixDown[3], pixLeft[3], pixRight[3];

           for(int k = 0; k <3; k++) {
               curPix[k] = get_pixel(im, i, j, k);
               pixUp[k] = get_pixel(im, i - 1, j, k);
               pixDown[k] = get_pixel(im, i + 1, j, k);
               pixLeft[k] = get_pixel(im, i, j - 1, k);
               pixRight[k] = get_pixel(im, i, j + 1, k);
           }
            int Rx, Gx, Bx, Ry, Gy, By;

            Rx = pixDown[0] - pixUp[0];
            Gx = pixDown[1] - pixUp[1];
            Bx = pixDown[2] - pixUp[2];

            Ry = pixRight[0] - pixLeft[0];
            Gy = pixRight[1] - pixLeft[1];
            By = pixRight[2] - pixLeft[2];

            //calculate energy
            int deltaX = Rx*Rx + Gx*Gx + Bx*Bx;
            int deltaY = Ry*Ry + Gy*Gy + By*By;
            int energy = sqrt(deltaX + deltaY);

            uint8_t res = energy/10; //Is this right?? I think so but not totally sure... //I think this is right now

            set_pixel(*grad, i, j, res, 0,0);
       }

   }


}



void dynamic_seam(struct rgb_img *grad, double **best_arr){
    
}








/**
int min_compare_three(double a, double b, double c){
   if(a <= b){
       if(a <= c) return 1;
       return 3;
   }
   if( b <= c) return 2;
   return 3;
}

void calc_energy(struct rgb_img *im, struct rgb_img **grad) {

   read_in_img(&im, "../3x4.bin");
   int width = im->width;
   int height = im->height;

   for(int i = 0; i < width; i++){
       for(int j = 0; j < height; j++){

           /**
            * New method of storing RGB: By pixel lmao
            * 0th is Red
            * 1st is Green
            * 2nd is Blue

           int pix[3], pixUp[3], pixDown[3], pixLeft[3], pixRight[3];

           if(i == 0){ //Maybe there's a better way to do this, maybe not. suck my dick (not you Hassan you're the best)
               for (int k = 0; k < 3; k++) {
                   pix[k] = get_pixel(im, i, j, k);
                   pixUp[k] = get_pixel(im, height-1, j, k);
                   pixDown[k] = get_pixel(im, i + 1, j, k);
                   pixLeft[k] = get_pixel(im, i, j - 1, k);
                   pixRight[k] = get_pixel(im, i, j + 1, k);
               }
           } else if(j == 0){
               for (int k = 0; k < 3; k++) {
                   pix[k] = get_pixel(im, i, j, k);
                   pixUp[k] = get_pixel(im, i - 1, j, k);
                   pixDown[k] = get_pixel(im, i + 1, j, k);
                   pixLeft[k] = get_pixel(im, i, width-1, k);
                   pixRight[k] = get_pixel(im, i, j + 1, k);
               }
           } else if(i == width){
               for (int k = 0; k < 3; k++) {
                   pix[k] = get_pixel(im, i, j, k);
                   pixUp[k] = get_pixel(im, i - 1, j, k);
                   pixDown[k] = get_pixel(im, 0, j, k);
                   pixLeft[k] = get_pixel(im, i, j - 1, k);
                   pixRight[k] = get_pixel(im, i, j + 1, k);
               }
           } else if(j == height){
               for (int k = 0; k < 3; k++) {
                   pix[k] = get_pixel(im, i, j, k);
                   pixUp[k] = get_pixel(im, i - 1, j, k);
                   pixDown[k] = get_pixel(im, i + 1, j, k);
                   pixLeft[k] = get_pixel(im, i, j - 1, k);
                   pixRight[k] = get_pixel(im, i, 0, k);
               }
           }
           else {
               for (int k = 0; k < 3; k++) {
                   pix[k] = get_pixel(im, i, j, k);
                   pixUp[k] = get_pixel(im, i - 1, j, k);
                   pixDown[k] = get_pixel(im, i + 1, j, k);
                   pixLeft[k] = get_pixel(im, i, j - 1, k);
                   pixRight[k] = get_pixel(im, i, j + 1, k);
               }
           }

           int Rx, Gx, Bx, Ry, Gy, By;

           Rx = pixDown[0] - pixUp[0];
           Gx = pixDown[1] - pixUp[1];
           Bx = pixDown[2] - pixUp[2];

           Ry = pixRight[0] - pixLeft[0];
           Gy = pixRight[1] - pixLeft[1];
           By = pixRight[2] - pixLeft[2];


           //calculate energy
           int deltaX = Rx*Rx + Gx*Gx + Bx*Bx;
           int deltaY = Ry*Ry + Gy*Gy + By*By;
           int energy = sqrt(deltaX + deltaY);

           uint8_t res = energy/10; //Is this right?? I think so but not totally sure...

           set_pixel(*grad, i, j, res, 0,0);
       }
   }
}

void dynamic_seam(struct rgb_img *grad, double **best_arr){
   int width = grad->width;
   int height = grad->height;

   best_arr = (double **)malloc(sizeof(double) * (width * height));

   for(int i = width; i < width; i++){
       best_arr[i*width] = MIN(best_arr[(i-1)*width], best_arr[(i-1)*width+1]) + get_pixel(grad, i,0,0);
       for(int j = 1; j < height-1; j++){
           best_arr[i*width + j] = MIN(best_arr[(i-1)*width + j], MIN(best_arr[(i-1)*width + j - 1], best_arr[(i-1)*width + j +1])) + get_pixel(grad, i,j,0);
       }
       best_arr[i*width + width - 1] = MIN(best_arr[(i-1)*width + width], best_arr[(i-1)*width + width - 1]) + get_pixel(grad, i, width, 0);
   }
}



void old_dynamic_seam(struct rgb_img *grad, double **best_arr){
   //Made using a 2d array, and apparently the project says we shouldn't do that:/. Once i get this method working maybe I'll revamp it to use the 2d array

   int width = grad->width;
   int height = grad->height;
   double count = 0;

   int len = 0;
   len = sizeof(double *) * height + sizeof(double) * width * height;
   best_arr = (double **)malloc(len); //Array is Malloc'ed

   double *ptr = (double *)(best_arr + height);


    //Test code to add dummy variables to best arr array
   for(int i = 0; i < height; i++){
       best_arr[i] = (ptr + width * i);
       for(int j = 0; j < width; j++){
           best_arr[i][j] = ++count;
       }
   }


   //for any given pixel
   //Compare the three directly above the pixel (wrap around?), find the lowest and add it to score.

   for(int j = 0; j < width; j++){
       best_arr[0][j] = get_pixel(grad, 0,j,0);
   }
   for(int i = 1; i < height; i++){
       best_arr[i][0] = MIN(best_arr[i-1][0], best_arr[i-1][1]) + get_pixel(grad, i, 0, 0);
       best_arr[i][width] = MIN(best_arr[i-1][width], best_arr[i-1][width-1]) + get_pixel(grad, i,0,0);
   }
   for(int i = 1; i < height; i++){
       for(int j = 1; j < width-1; j++){
           best_arr[i][j] = MIN(best_arr[i-1][j], MIN(best_arr[i-1][j-1], best_arr[i-1][j+1])) + get_pixel(grad, i,j,0);
       }
   }

   /*
   //test code to print best arr array
   for (int i = 0; i < height; i++) {
       for (int j = 0; j < width; j++) {
           printf("%f ", best_arr[i][j]);
       }
       printf("\n");
   }

}

void recover_path(double *best, int height, int width, int **path){
   *path = malloc(sizeof(int) * height);
   double temp = 256;
   int temp_width = 0;
   for(int i = 0; i < width; i++){
       if(best[i] < temp) {
           temp_width = i;
           temp = best[i];
       }
   }
   for(int i = 1; i < height; i++){
       double a = best[i*width + temp_width + 1];
       double b = best[i*width + temp_width];
       double c = best[i*width + temp_width + 1];
       int min_case = min_compare_three(a,b,c);
       switch(min_case){
           case 1:
               //A is smallest
               temp_width++;
               break;
           case 2:
               //B is smallest
               break;
           case 3:
               //C is smallest
               temp_width--;
               break;
           default:
               printf("Something is broken here... idk how this happened...");
       }
       *path[i] = temp_width;
   }
}


void old_recover_path(double *best, int height, int width, int **path){
   *path = malloc(sizeof(int) * height);
   double temp = 256;
   int temp_index = 0;
   for(int i = 0; i < width; i++){
       if(best[i][0] < temp){
           temp_index = i;
           temp == best[i][0];
       }
   }
   *path[0] = (int)temp;
   for(int i = 1; i < height; i++){






   }
   //gist of it is: find the min of first row, that is the starting point.
   //then, for all next rows, compare next row pixel (left, center, right), min gets added to path.
}

int main() {
   printf("Hello, World!");

   struct rgb_img *im;
   create_img(&im, 4, 3); // do these values need to be hardcoded?

   struct rgb_img *grad;

   create_img(&grad, 3, 4);

   calc_energy(im,  &grad);
   printf("tempy\n");

   print_grad(grad);
   double** temp;
   dynamic_seam(grad, temp);




}

//
// Created by Nicholas on 2023-03-22.
//
