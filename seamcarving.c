#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "c_img.h"
#include <limits.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y)) //Don't really need this but I figured I'd write it anyways
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
//Somehow there are no default min or max functions, so, we writing our own boys.


int min_compare_three(double a, double b, double c){
    if(a <= b){
        if(a <= c) return 1;
        return 3;
    }
    if( b <= c) return 2;
    return 3;
}

double min(double a, double b){
    if(a <= b){
        return a;
    }
    return b;
}

double min_three(double a, double b, double c){
    double d = min(a, b);
    return min(c, d);
}

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


/*
void calc_energy(struct rgb_img *im, struct rgb_img **grad) {

    read_in_img(&im, "../3x4.bin");
    int width = im->width;
    int height = im->height;

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){


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
} */

void dynamic_seam(struct rgb_img *grad, double **best_arr){
    int width = grad->width;
    int height = grad->height;

    printf("Width: %d Height: %d \n", width, height);

    *best_arr = (double *)malloc(sizeof(double) * (width * height));

    //double count= 0; //code to assign dummy variables (can be removed (probably))
    //for(int i = 0; i < width * height; i++){
    //    (*best_arr)[i] = ++count;
    //}

    //New Code

    //Copy top row direct from grad
    //remaining rows:
        //do leftmost column, middle columns, and then rightmost column.

    for(int x = 0; x < width; x++){
        (*best_arr)[x] = get_pixel(grad, 0,x,0);
    }

    int x = 0;
    int index;
    int indexAbove;
    int temp;

    for(int y = 1; y < height; y++){
        x=0;
        index = y*width + x;
        indexAbove = y*(width) -width + x;
        temp = get_pixel(grad, y,x,0);
        (*best_arr)[index] = MIN((*best_arr)[indexAbove], (*best_arr)[indexAbove +1]) +temp;
        for(x = 1; x < (width-1); x++){
            //middle cols
            index = y*width + x;
            indexAbove = y*(width) -width + x;
            temp = get_pixel(grad, y,x,0);
            (*best_arr)[index] = MIN((*best_arr)[indexAbove], MIN((*best_arr)[indexAbove -1], (*best_arr)[indexAbove +1])) + temp;
        }
        index = y*width + x;
        indexAbove = y*(width) -width + x;
        temp = get_pixel(grad, y,x,0);
        (*best_arr)[index] = MIN((*best_arr)[indexAbove], (*best_arr)[indexAbove -1]) + temp;
    }

    /* Old ode

    for(int i = 1; i < height; i++){
        *temp = get_pixel(grad, i, 0, 0);
        printf("Pixel Grabbed...");
        (*best_arr)[i*width] = MIN((*best_arr)[(i-1)*width], (*best_arr)[(i-1)*width+1]) + *temp;
        printf("First bit of code ran ok\n");
        for(int j = 1; j < width-1; j++){
            *temp = get_pixel(grad, i,j,0);
            printf("Pixel Grabbed...");
            (*best_arr)[i*width + j] = MIN((*best_arr)[(i-1)*width + j], MIN((*best_arr)[(i-1)*width + j - 1], (*best_arr)[(i-1)*width + j +1])) + *temp;
            printf("Inner bit of code ran ok\n");
        }
        *temp = get_pixel(grad, i, width, 0);
        printf("Pixel Grabbed...");
        (*best_arr)[i*width + width - 1] = MIN((*best_arr)[(i-1)*width + width], (*best_arr)[(i-1)*width + width - 1]);
        printf("Outer bit of code ran ok\n");
    }*/

    //test code to print best arr

    for(int y = 0; y < height; y++){
        for(int j = 0; j < width; j++){
            printf("%f ", (*best_arr)[y*width+j]);
        }
        printf("\n");
    }

    /*
    for(int i = 0; i < height; i++){
        for(int j = 0; j < height; j++){
            printf("%f ",(*best_arr)[i*width + j]);
        }
        printf("\n");
    } */
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
    } */

}

void recover_path(double *best, int height, int width, int **path){ //I think this works??might not need to do anything for this.
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
        double a = best[i*width + temp_width - 1];
        double b = best[i*width + temp_width];
        double c = best[i*width + temp_width + 1];
        switch(min_compare_three(a,b,c)){
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
        if(best[i] < temp){
            temp_index = i;
            temp == best[i];
        }
    }
    *path[0] = (int)temp;
    for(int i = 1; i < height; i++){






    }
    //gist of it is: find the min of first row, that is the starting point.
    //then, for all next rows, compare next row pixel (left, center, right), min gets added to path.
}

void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path){
    //create and malloc dest image (same dimensions as source)
    //Go through path and set that pixel in dest
    int width = src->width;
    int height = src->height;

    create_img(dest, height, width);


    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            //Do something here
        }
    }


}



int main() {

    struct rgb_img *grad;
    struct rgb_img im;
    struct rgb_img *p_im = &im;
    read_in_img(&p_im, "../3x4.bin"); //I had to rename it to this for it to work with CLion, to make it work
                                                    // on replit get rid of the "../" and it should work like a charm.


    //Test Infrastructure - REMOVE WHEN SUBMITTING
    printf("Width: %d\nHeight: %d\n\n", (int)p_im->width, (int)p_im->height);
    square_gradient(p_im, 0, 1);
    calc_energy(p_im, &grad);
    printf("\nGrad:\n");
    print_grad(grad);

    double *best_arr;

    dynamic_seam(grad, &best_arr);

    return 0;
    // End of Test Infrastructure - REMOVE WHEN SUBMITTING
    //Infruastructire?? Say that 3 times fast and you'll summon Raymond from his office in GB
}

//
// Created by Nicholas on 2023-03-22.
//
