#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct rgb_img {
    int width;
    int height;
    int *data;
} rgb_img;

//Hassan I forgot we actually need a way to read in images and stuff, can you figure out how to do that?
//Once you get that up and going lmk and I'll knock out part 1


void calc_energy(struct rgb_img *im, struct rgb_img **grad) {
    //printf("calc_energy");
    int width = im -> width;
    int height = im -> height;

    int Rx, Gx, Bx, Ry, Gy, By; //The difference in RGB values in the pixels above & below, and left & right

    int deltaX = Rx*Rx + Gx*Gx + Bx*Bx;
    int deltaY = Ry*Ry + Gy*Gy + By*By;
    int res = sqrt(deltaX + deltaY);




    **grad = (rgb_img) {width, height, malloc(sizeof(int) * width * height)};

}



//
// Created by Nicholas on 2023-03-22.
//
