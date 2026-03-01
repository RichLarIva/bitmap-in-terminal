#ifdef _WIN32
#include <windows.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "bmp.h"
#include "image.h"

int main(int argc, char **argv)
{
#ifdef _WIN32
    // Enable UTF-8 in Windows console
    system("chcp 65001 > nul");

    // Enable Ansi escape sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    mode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
    SetConsoleMode(hOut, mode);
#endif

    Args args;
    if (!parse_args(argc, argv, &args))
    {
        return 1;
    }

    int w, h, ch;
    uint8_t *bmpRaw = bmp_load(args.filepath, &w, &h, &ch);
    if (!bmpRaw)
    {
        return 1;
    }

    Image img = image_from_bmp(bmpRaw, w, h, ch);
    free(bmpRaw);


    int outW = args.outWidth > 0 ? args.outWidth : img.width;
    int outH = args.outHeight > 0 ? args.outHeight : img.height;
    // Rendering block
    for (int y = 0; y < outH; y++)
    {
        float srcY = (float)y / outH * img.height;
        for (int x = 0; x < outW; x++)
        {
            float srcX = (float)x / outW * img.width;

            uint8_t *pixel = img.data + ((int)srcY * img.width + (int)srcX) * img.channels;
            // █ <- this character is used to print blocks
            printf("\033[38;2;%d;%d;%dm█", pixel[0], pixel[1], pixel[2]);

        }
        printf("\n");
    }

    printf("Here is your bitmap!");
    image_free(&img);
    return 0;
}