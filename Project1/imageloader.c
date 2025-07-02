/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include "imageloader.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Opens a .ppm P3 image file, and constructs an Image object.
// You may find the function fscanf useful.
// Make sure that you close the file with fclose before returning.
Image *readData(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        // 如果文件打开失败，fp会是NULL
        perror("错误：无法打开文件"); // perror会打印出具体的系统错误信息，比如
                                      // "No such file or directory"
        exit(1);
    }
    Image *ans = malloc(sizeof(Image));
    char P3[10];
    uint32_t row, col;
    int x;
    fscanf(fp, "%s", P3);
    fscanf(fp, "%d %d", &col, &row);
    fscanf(fp, "%d", &x);
    ans->rows = row;
    ans->cols = col;
	Color **c = malloc(sizeof(Color*) * row);
	for(int i = 0 ; i < row ; i++){
		c[i] = malloc(sizeof(Color) * col);
	}
    ans->image = c;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            uint8_t R, G, B;
            fscanf(fp, "%hhd %hhd %hhd", &R, &G, &B);
            Color x = {R, G, B};
            ans->image[i][j] = x;
        }
    }
    fclose(fp);
    return ans;
}

// Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the
// image's data.
void writeData(Image *image) {
	// exit(1);
    printf("P3\n");
    printf("%d %d\n", image->cols, image->rows);
    printf("255\n");
    for (int i = 0; i < image->rows; i++) {
        for (int j = 0; j < image->cols; j++) {
            printf("%3d %3d %3d", image->image[i][j].R, image->image[i][j].G,
                   image->image[i][j].B);
            if (j != image->cols - 1) {
                printf("   ");
            } else {
                printf("\n");
            }
        }
    }
}

// Frees an image
void freeImage(Image *image) { 
	for(int i = 0 ; i < image->rows ; i++){
		free(image->image[i]);
	}
	free(image->image);
	free(image); 
}
