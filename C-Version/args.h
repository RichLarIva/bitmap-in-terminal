//
// Created by richa on 2026-03-01.
//

#ifndef C_VERSION_ARGS_H
#define C_VERSION_ARGS_H

typedef struct {
    const char *filepath;
    int outWidth;
    int outHeight;
} Args;

int parse_args(int argc, char **argv, Args *out);


#endif //C_VERSION_ARGS_H