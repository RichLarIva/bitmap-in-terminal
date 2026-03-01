//
// Created by richa on 2026-03-01.
//

#include <stdlib.h>
#include <string.h>
#include "image.h"

Image image_from_bmp(uint8_t *bmpData, int width, int height, int channels)
{
    Image img;
    img.width = width;
    img.height = height;
    img.channels = channels;
    img.data = malloc(width * height * channels);

    int srcRowSize = ((width * channels + 3) & ~3);      // padded source
    int dstRowSize = width * channels;                   // tight destination

    for (int y = 0; y < height; y++)
    {
        uint8_t *srcRow = bmpData + (height - 1 - y) * srcRowSize;
        uint8_t *dstRow = img.data + y * dstRowSize;

        for (int x = 0; x < width; x++)
        {
            uint8_t *src = srcRow + x * channels;
            uint8_t *dst = dstRow + x * channels;

            dst[0] = src[2]; // R
            dst[1] = src[1]; // G
            dst[2] = src[0]; // B

            if (channels == 4)
            {
                dst[3] = src[3]; // A
            }
        }
    }

    return img;
}

void image_free(Image *img)
{
    free(img->data);
    img->data = NULL;
}