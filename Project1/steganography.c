/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include "imageloader.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// Determines what color the cell at the given row/col should be. This should
// not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col) {
	Color *ans = malloc(sizeof(Color));
    if(image->image[row][col].B % 2 == 0){
		ans->R = 0;
		ans->G = 0;
		ans->B = 0;
		return ans;
	}else{
		ans->R = 0;
		ans->G = 0;
		ans->B = 255;
		return ans;
	}
}

// Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image) {
    Image *ans = malloc(sizeof(Image));
    ans->rows = image->rows;
	ans->cols = image->cols;
	Color **c = malloc(sizeof(Color*) * (image->rows));
	for(int i = 0 ; i < image->rows ; i++){
		c[i] = malloc(sizeof(Color) * (image->cols));
	}
    ans->image = c;
    for (int i = 0; i < image->rows; i++) {
        for (int j = 0; j < image->cols; j++) {
			Color *pixel = evaluateOnePixel(image, i, j);
			ans->image[i][j] = *pixel;
			free(pixel);
        }
    }
	return ans;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with
printf) a new image, where each pixel is black if the LSB of the B channel is 0,
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not
necessarily with .ppm file extension). If the input is not correct, a malloc
fails, or any other error occurs, you should exit with code -1. Otherwise, you
should return from main with code 0. Make sure to free all memory before
returning!
*/
int main(int argc, char **argv) {
    Image *image;
    char *filename;
    if (argc != 2) {
        printf("usage: %s filename\n", argv[0]);
        printf("filename is an ASCII PPM file (type P3) with maximum value "
               "255.\n");
        exit(-1);
    }
    filename = argv[1];
    image = readData(filename);
    Image *ans = steganography(image);
	writeData(ans);
    freeImage(ans);
	freeImage(image);
}
