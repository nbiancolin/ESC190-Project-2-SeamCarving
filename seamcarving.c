#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "c_img.h"
#define MIN(x, y) (((x) < (y)) ? (x) : (y))  //Somehow there are no default min or max functions, so, we writing our own boys.

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
            //printf("%d\t", dual_gradient);
        }
        //TEST PRINT STATEMENT - REMOVE WHEN SUBMITTING
        //printf("\n");
    }
}

void dynamic_seam(struct rgb_img *grad, double **best_arr){
    int width = grad->width;
    int height = grad->height;

    *best_arr = (double *)malloc(sizeof(double) * (width * height));

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
}

void recover_path(double *best, int height, int width, int **path){ //I think this works??might not need to do anything for this.
    *path = malloc(sizeof(int) * height);
    double temp = 256;
    int temp_width = 0;
    for(int i = 0; i < width; i++){ //finds minimum value for the first one, and sets that array.
        if(best[i] < temp) {
            temp_width = i;
            temp = best[i];
        }
    }
    (*path)[0] = temp_width;

    for(int y = 1; y < height; y++){

        double a = best[y*width + temp_width -1];
        double b = best[y*width + temp_width];
        double c = best[y*width + temp_width +1];
        if(temp_width == 0){
            if(c<b) temp_width++;
        } else if(temp_width == width){
            if(a<b) temp_width--;
        } else {
            switch (min_compare_three(a, b, c)) {
                case 1:
                    temp_width--;
                    break;
                case 2:
                    break;
                case 3:
                    temp_width++;
                    break;
                default:
                    printf("Idk how you managed to break this, but good job...");
                    break;
            }
        }
        (*path)[y] = temp_width;
    }
}

void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path){
    int width = src->width;
    int height = src->height;

    create_img(dest, height, width-1);
    int x = 0;
    for(int y = 0; y < height; y++){
        x = 0;
        while(x<path[y]) {
            int r = get_pixel(src, y, x,0);
            int g = get_pixel(src, y, x,1);
            int b = get_pixel(src, y, x,2);
            set_pixel(*dest, y, x,r,g,b);
            x++;
        }
        //x++;
        while(x < (width-1)){
            int r = get_pixel(src, y, x+1,0);
            int g = get_pixel(src, y, x+1,1);
            int b = get_pixel(src, y, x+1,2);
            set_pixel(*dest, y, x,r,g,b);
            x++;
        }
    }
}


/*
int main() {


    struct rgb_img *im;
    struct rgb_img *cur_im;
    struct rgb_img *grad;
    double *best;
    int *path;

    read_in_img(&im, "../HJoceanSmall.bin");

    for (int i = 0; i < 300; i++) {
        printf("i = %d\n", i);
        calc_energy(im, &grad);
        dynamic_seam(grad, &best);
        recover_path(best, grad->height, grad->width, &path);
        remove_seam(im, &cur_im, path);

        char filename[200];
        sprintf(filename, "img%d.bin", i);
        write_img(cur_im, filename);


        destroy_image(im);
        destroy_image(grad);
        free(best);
        free(path);
        im = cur_im;
    }
    destroy_image(im);
    printf("Hello World");

    return 0;
}
*/

    /* OLD TESTING CODE
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

    int *path;
    recover_path(best_arr, (int)p_im->height,(int)p_im->width, &path);

    return 0; */
    // End of Test Infrastructure - REMOVE WHEN SUBMITTING
    //Infruastructire?? Say that 3 times fast and you'll summon Raymond from his office in GB
//}

//
// Created by Nicholas on 2023-03-22.
//
