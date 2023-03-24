#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "c_img.h"




void calc_energy(struct rgb_img *im, struct rgb_img **grad) {

    read_in_img(&im, "../3x4.bin");

    for(int i = 0; i < im->width; i++){
        for(int j = 0; j < im->height; i++){

            int Rs[5], Gs[5], Bs[5];

            /**
             * Layout of colour Arrays
             * 0 - Current Pixel
             * 1 - Pixel Above
             * 2 - Pixel Below
             * 3 - Pixel To the Left
             * 4 - Pixel to the Right
             */
            Rs[0] = get_pixel(im, i,j,0); //Not totally sure it's important
            Rs[1] = get_pixel(im, i-1, j, 0);
            Rs[2] = get_pixel(im, i+1, j, 0);
            Rs[3] = get_pixel(im, i, j-1, 0);
            Rs[4] = get_pixel(im, i, j+1, 0);

            Gs[0] = get_pixel(im, i,j,0); //Not totally sure it's important
            Gs[1] = get_pixel(im, i-1, j, 1);
            Gs[2] = get_pixel(im, i+1, j, 1);
            Gs[3] = get_pixel(im, i, j-1, 1);
            Gs[4] = get_pixel(im, i, j+1, 1);

            Bs[0] = get_pixel(im, i,j,2); //Not totally sure it's important
            Bs[1] = get_pixel(im, i-1, j, 2);
            Bs[2] = get_pixel(im, i+1, j, 2);
            Bs[3] = get_pixel(im, i, j-1, 2);
            Bs[4] = get_pixel(im, i, j+1, 2);

            //calculate deltas
            int Rx, Gx, Bx, Ry, Gy, By; //The difference in RGB values in the pixels above & below, and left & right

            Rx = Rs[2] - Rs[1];
            Gx = Gs[2] - Gs[1];
            Bx = Bs[2] - Bs[1];

            Ry = Rs[4] - Rs[3];
            Gy = Gs[4] - Gs[3];
            By = Bs[4] - Bs[3];



            //calculate energy
            int deltaX = Rx*Rx + Gx*Gx + Bx*Bx;
            int deltaY = Ry*Ry + Gy*Gy + By*By;
            int res = sqrt(deltaX + deltaY);

            //*grad->//got to do something w. this

            //Problem with grad... set pixel is breaking, andy said its because grad is not initialized...
            set_pixel(*grad, i, j, res, 0,0);
        }
    }
}

int main() {
    printf("Hello, World!");

    struct rgb_img *im;
    create_img(&im, 3, 4); // do these values need to be hardcoded?


    struct rgb_img *grad = malloc(sizeof(struct rgb_img));

    calc_energy(im,  &grad);
    printf("tempy");

    print_grad(grad);




}

//
// Created by Nicholas on 2023-03-22.
//
