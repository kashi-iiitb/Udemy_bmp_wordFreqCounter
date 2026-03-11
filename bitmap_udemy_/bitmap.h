#ifndef _BITMAP_FILE_HEADER_H
#define _BITMAP_FILE_HEADER_H
#include <stdint.h>

#pragma pack(push,1)

typedef struct bitmapFileHeader{
    uint16_t FileSignature;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
} BITMAPFILEHEADER;

typedef struct bitmapInfoHeader{
    
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t imgSize;
    uint32_t xppm;
    uint32_t yppm;
    uint32_t colorsUsed;
    uint32_t impColors;

} BITMAPINFOHEADER;

typedef struct rgbPixel{
    uint8_t blue;
    uint8_t green;
    uint8_t red;    
    

}PIXEL;

#pragma pack(pop)
#endif
