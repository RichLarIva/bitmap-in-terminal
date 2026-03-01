//
// Created by richa on 2026-03-01.
//

#include <stdio.h>
#include "render.h"

ThreadReturn THREAD_CALL render_worker(void *arg)
{
    RenderTask *t = arg;
    Image *img = t->img;

    for (int y = t->yStart; y < t->yEnd; y++)
    {
        float srcY = (float)y / t->outH * img->height;
        char *row = t->outBuf + y * t->rowStride;
        char *p = row;

        for (int x = 0; x < t->outW; x++)
        {
            float srcX = (float)x / t->outW * img->width;
            uint8_t *pix = img->data +
                ((int)srcY * img->width + (int)srcX) * img->channels;

            p += sprintf(p, "\033[48;2;%d;%d;%dm ", pix[0], pix[1], pix[2]);
        }

        p += sprintf(p, "\033[0m\n");
    }

    return 0;
}
