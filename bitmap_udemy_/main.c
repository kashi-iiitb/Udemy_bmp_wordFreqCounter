#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

int main(int argc, char* argv[]){

    //program_name <width> <height>
    if(argc!= 3){
        printf("Error: Incorrect Number of arguments!!\n");
        return -1;
    }
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);


    int padding = (4 - (width * sizeof(struct rgbPixel))%4) % 4;
    int rowSize = width*sizeof(struct rgbPixel) + padding;
    int imgSize = height*rowSize;


    BITMAPINFOHEADER bih = {
        .size = sizeof(BITMAPINFOHEADER),
        .width = width,
        .height = height,
        .planes = 1,
        .bpp = 24,
        .compression = 0,
        .imgSize = imgSize,
        .xppm = 0,
        .yppm = 0,
        .colorsUsed =0,
        .impColors = 0
    };

    BITMAPFILEHEADER bfh = {
        .FileSignature = 0x4d42,
        .fileSize = imgSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER),
        .reserved = 0,
        .dataOffset = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
    };
    

    FILE *filePtr;
    filePtr = fopen("bitmap.bmp", "wb");
    if(!filePtr){
        printf("Error: Unable to Open the file!!\n");
        return -1;
    }

    fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, filePtr);
    fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, filePtr);
    struct rgbPixel* rowDataPtr = (struct rgbPixel*) malloc(sizeof(struct rgbPixel)*width);

    for(int j=0; j<height; j++){
        for(int i=0; i<width; i++){
            rowDataPtr[i].red = 255;
            rowDataPtr[i].green = 0;
            rowDataPtr[i].blue = 255;
        }
        fwrite(rowDataPtr, sizeof(PIXEL), width, filePtr);
        for(int k=0; k<padding; k++){
            uint8_t pad_byte=0;
            fwrite(&pad_byte, sizeof(uint8_t), 1, filePtr);
        }
    }

    fclose(filePtr);

}