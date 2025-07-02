/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include "imageloader.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>


// Determines what color the cell at the given row/col should be. This function
// allocates space for a new Color. Note that you will need to read the eight
// neighbors of the cell in question. The grid "wraps", so we treat the top row
// as adjacent to the bottom row and the left column as adjacent to the right
// column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule) {
    Color *ans = malloc(sizeof(Color));
	
    int aliveR = 0, aliveG = 0, aliveB = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (image
                    ->image[(row + i + image->rows) % image->rows]
                           [(col + j + image->cols) % image->cols]
                    .R == 255) {
                aliveR++;
            }
            if (image
                    ->image[(row + i + image->rows) % image->rows]
                           [(col + j + image->cols) % image->cols]
                    .G == 255) {
                aliveG++;
            }
            if (image
                    ->image[(row + i + image->rows) % image->rows]
                           [(col + j + image->cols) % image->cols]
                    .B == 255) {
                aliveB++;
            }
        }
    }
    if (image->image[row][col].R && (rule >> (9 + aliveR) & 1)){
		ans->R = 255;
	}else if((!image->image[row][col].R) && (rule >> (aliveR) & 1)){
		ans->R = 255;
	}else{
		ans->R = 0;
	}
    if (image->image[row][col].G && (rule >> (9 + aliveG) & 1)){
		ans->G = 255;
	}else if((!image->image[row][col].G) && (rule >> (aliveG) & 1)){
		ans->G = 255;
	}else{
		ans->G = 0;
	}    
	if (image->image[row][col].B && (rule >> (9 + aliveB) & 1)){
		ans->B = 255;
	}else if((!image->image[row][col].B) && (rule >> (aliveB) & 1)){
		ans->B = 255;
	}else{
		ans->B = 0;
	}
    return ans;
}

// The main body of Life; given an image and a rule, computes one iteration of
// the Game of Life. You should be able to copy most of this from
// steganography.c
Image *life(Image *image, uint32_t rule) {
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
			Color *pixel = evaluateOneCell(image, i, j , rule);
			ans->image[i][j] = *pixel;
			free(pixel);
        }
    }
	return ans;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then
prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this
will be a string. You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you
should exit with code -1. Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/


int main(int argc, char **argv) {
    Image *image;
    char *filename;
	
    if (argc != 3) {
        printf("usage: %s filename\n", argv[0]);
        printf("filename is an ASCII PPM file (type P3) with maximum value "
               "255.\n");
        exit(-1);
    }
	uint32_t rule = (uint32_t)strtol(argv[2], NULL, 0);


    filename = argv[1];
    image = readData(filename);
    Image *ans = life(image , rule);
	writeData(ans);
    freeImage(ans);
	freeImage(image);
}
