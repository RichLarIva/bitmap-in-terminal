//
// Created by richa on 2026-03-01.
//

#include "thread.h"

int thread_create(Thread *t, ThreadFunction function, void *arg)
{
#ifdef _WIN32
    *t = CreateThread(NULL, 0, function, arg, 0, NULL);
    return *t != NULL;
#else
    return pthread_create(t, NULL, function, arg) == 0;
#endif
}

void thread_join(Thread t)
{
#ifdef _WIN32
    WaitForSingleObject(t, INFINITE);
    CloseHandle(t);
#else
    pthread_join(t, NULL);
#endif
}