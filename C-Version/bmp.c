//
// Created by richa on 2026-03-01.
//

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

uint8_t *bmp_load(const char *path, int *width, int *height, int *channels)
{
    FILE *f = fopen(path, "rb");
    if (!f)
    {
        fprintf(stderr, "Could not open BMP file: %s\n", path);
        return NULL;
    }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    fread(&fileHeader, sizeof(fileHeader), 1, f);
    fread(&infoHeader, sizeof(infoHeader), 1, f);

    if (fileHeader.bfType != 0x4D42)
    {
        fprintf(stderr, "Not a valid BMP file.\n");
        fclose(f);
        return NULL;
    }

    *width = infoHeader.biWidth;
    *height = infoHeader.biHeight;
    *channels = infoHeader.biBitCount / 8;

    int rowSize = ((*width * *channels +3) & ~3);
    int dataSize = rowSize * (*height);

    uint8_t *data = malloc(dataSize);
    if (!data)
    {
        fclose(f); // no data so close this file loooooooo;
        return NULL;
    }

    fseek(f, fileHeader.bfOffBits, SEEK_SET);
    fread(data, dataSize, 1, f);
    fclose(f);

    return data;
}