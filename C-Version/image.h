//
// Created by richa on 2026-03-01.
//

#ifndef C_VERSION_IMAGE_H
#define C_VERSION_IMAGE_H

#include <stdint.h>

typedef struct
{
    int width;
    int height;
    int channels; // 3 = RGB, 4 = RGBA
    uint8_t *data; // top-to-bottom, RGB(A)
} Image;

Image image_from_bmp(uint8_t *bmpData, int width, int height, int channels);
void image_free(Image *img);

#endif //C_VERSION_IMAGE_H