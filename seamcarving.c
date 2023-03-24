#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "c_img.h"
#include <limits.h>




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
             */
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
    double count = 0;

    int len = 0;
    len = sizeof(double *) * height + sizeof(double) * width * height;
    best_arr = (double **)malloc(len); //Array is Malloc'ed

    double *ptr = (double *)(best_arr + height);

    /*
     //Test code to add dummy variables to best arr array
    for(int i = 0; i < height; i++){
        best_arr[i] = (ptr + width * i);
        for(int j = 0; j < width; j++){
            best_arr[i][j] = ++count;
        }
    }

     //test code to print best arr array
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%f ", best_arr[i][j]);
        }
        printf("\n");
    }



    /*
    double tc[width][height]; //Miight have to switch height and width, idk
    *tc = malloc(sizeof(double) * (width * height));
    *best_arr = &tc;
    tc[0][0] = get_pixel(grad, 0,0,0); //all data in grad is stored in the red or 0 col

    *best_arr = &tc;
    */
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
