#ifdef _WIN32
#include <windows.h>
#else
#include <unisted.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"
#include "bmp.h"
#include "image.h"
#include "thread.h"
#include "render.h"

// Detect number of logical CPU threads
int get_cpu_threads(void)
{
#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return (int)sysinfo.dwNumberOfProcessors;
#else
    long n = sysconf(_SC_NPROCESSORS_ONLN);
    return (int)(n > 0 ? n : 1);
#endif
}


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

    // Allocate output buffer
    int maxSeqLen = 32;
    int rowStride = outW * maxSeqLen + 16;
    char *buffer = malloc(outH * rowStride);
    if (!buffer)
    {
        fprintf(stderr, "!Out of memory!\n");
        return 1;
    }

    // Determine optimal thread count
    int cpuThreads = get_cpu_threads();
    int numThreads = cpuThreads;

    if (numThreads > outH)
        numThreads = outH;
    if (numThreads < 1)
        numThreads = 1;

    Thread threads[64];
    RenderTask tasks[64];

    int rowsPerThread = (outH + numThreads - 1) / numThreads;

    // Launch worker threads
    for (int i = 0; i < numThreads; i++)
    {
        tasks[i].yStart = i * rowsPerThread;
        tasks[i].yEnd = (i + 1) * rowsPerThread;

        if (tasks[i].yEnd > outH)
            tasks[i].yEnd = outH;

        tasks[i].outW = outW;
        tasks[i].outH = outH;
        tasks[i].img = &img;
        tasks[i].outBuf = buffer;
        tasks[i].rowStride = rowStride;

        thread_create(&threads[i], render_worker, &tasks[i]);
    }

    // wait for all threads
    for (int i = 0; i < numThreads; i++)
    {
        thread_join(threads[i]);
    }

    // Print final product
    for (int y = 0; y < outH; y++)
        fputs(buffer + y * rowStride, stdout);

    free(buffer);
    image_free(&img);

    printf("\033[38;2;%d;%d;%dmHere is your bitmap!\n", 255, 0, 0);
    return 0;
}