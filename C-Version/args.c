//
// Created by richa on 2026-03-01.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "args.h"

int parse_args(int argc, char **argv, Args *out)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <image.bmp> [--width N] [--height N]\n", argv[0]);
        return 0;
    }

    out->filepath = argv[1];
    out->outWidth = 0;
    out->outHeight = 0;

    for (int i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "--width") == 0 && i + 1 < argc)
        {
            out->outWidth = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "--height") == 0 && i + 1 < argc)
        {
            out->outHeight = atoi(argv[++i]);
        }
    }

    return 1;
}