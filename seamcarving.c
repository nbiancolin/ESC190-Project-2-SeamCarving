#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "c_img.h"




void calc_energy(struct rgb_img *im, struct rgb_img **grad) {


    int Rx, Gx, Bx, Ry, Gy, By; //The difference in RGB values in the pixels above & below, and left & right

    int deltaX = Rx*Rx + Gx*Gx + Bx*Bx;
    int deltaY = Ry*Ry + Gy*Gy + By*By;
    int res = sqrt(deltaX + deltaY);



}

int main() {
    printf("Hello, World!");

    struct rgb_img *im;
    create_img(&im, 3, 3); // do these values need to be hardcoded?



}

//
// Created by Nicholas on 2023-03-22.
//
