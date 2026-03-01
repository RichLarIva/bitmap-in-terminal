//
// Created by richa on 2026-03-01.
//

#ifndef C_VERSION_BMP_H
#define C_VERSION_BMP_H

#include <stdint.h>

#pragma pack(push, 1)
typedef struct
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BMP_FILEHEADER;

typedef struct
{
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMP_INFOHEADER;
#pragma pack(pop)

uint8_t *bmp_load(const char *path, int *width, int *height, int *channels);

#endif //C_VERSION_BMP_H