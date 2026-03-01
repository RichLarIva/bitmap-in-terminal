//
// Created by richa on 2026-03-01.
//

#ifndef C_VERSION_RENDER_H
#define C_VERSION_RENDER_H

#include "image.h"
#include "thread.h"

typedef struct
{
    int yStart, yEnd;
    int outW, outH;
    Image *img;
    char *outBuf; // global output buffer
    int rowStride; // bytes per rendered row
} RenderTask;

ThreadReturn THREAD_CALL render_worker(void *arg);

#endif //C_VERSION_RENDER_H