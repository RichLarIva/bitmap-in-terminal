//
// Created by richa on 2026-03-01.
//

#ifndef C_VERSION_THREAD_H
#define C_VERSION_THREAD_H

#ifdef _WIN32
#include <windows.h>
typedef HANDLE Thread;
typedef DWORD ThreadReturn;
#define THREAD_CALL WINAPI
#else
#include <pthread.h>
typedef pthread_t Thread;
typedef void *ThreadReturn;
#define THREAD_CALL
#endif

typedef ThreadReturn (THREAD_CALL *ThreadFunction)(void *arg);

int thread_create(Thread *t, ThreadFunction function, void *arg);
void thread_join(Thread t);

#endif //C_VERSION_THREAD_H