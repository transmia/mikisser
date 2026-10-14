#include <stdbool.h>
#include <stdint.h>
#include "../thirdparty/raylib.h"

#include "include/clock.h"

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define Rectangle WIN_Rectangle
    #define CloseWindow WIN_CloseWindow
    #define ShowCursor WIN_ShowCursor
    #include <windows.h>
    #undef Rectangle
    #undef CloseWindow
    #undef ShowCursor
#else
    #include <time.h>
#endif

static int hz = 0;
static volatile bool running = false;
static uint64_t next_tick = 0;
static uint64_t tick_interval = 0;

#ifdef _WIN32
static LARGE_INTEGER clock_frequency;

static uint64_t clock_now_ns(void) {
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return (uint64_t)((now.QuadPart * 1000000000ULL) / clock_frequency.QuadPart);
}

static void clock_sleep_ns(uint64_t ns) {
    if (ns >= 2000000ULL)
        Sleep((DWORD)(ns / 1000000ULL));
}
#else
static uint64_t clock_now_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

static void clock_sleep_ns(uint64_t ns) {
    struct timespec ts = {
        .tv_sec = (time_t)(ns / 1000000000ULL),
        .tv_nsec = (long)(ns % 1000000000ULL)
    };

    nanosleep(&ts, NULL);
}
#endif

bool clock_init(uint32_t frequency_hz) {
    if (frequency_hz == 0) {
        clock_shutdown();
        return false;
    }

#ifdef _WIN32
    QueryPerformanceFrequency(&clock_frequency);
#endif

    hz = frequency_hz;
    tick_interval = 1000000000ULL / (uint64_t)frequency_hz;
    next_tick = clock_now_ns() + tick_interval;
    running = true;
    return true;
}

void clock_shutdown(void) {
    running = false;
    hz = 0;
    tick_interval = 0;
}

bool clock_set_frequency(uint32_t frequency_hz) {
    if (frequency_hz == 0) {
        return false;
    }

    hz = frequency_hz;
    tick_interval = 1000000000ULL / (uint64_t)frequency_hz;
    next_tick = clock_now_ns() + tick_interval;
    return true;
}

uint32_t clock_get_frequency(void) {
    return hz;
}

uint64_t clock_get_time_us(void) {
    return clock_now_ns() / 1000ULL;
}

void clock_sleep_us(uint64_t duration_us) {
    clock_sleep_ns(duration_us * 1000ULL);
}

bool clock_wait(void) {
    if (WindowShouldClose())
        running = false;

    if (!running)
        return false;

    uint64_t now;

    while (running) {
        now = clock_now_ns();

        if (now >= next_tick)
            break;

        clock_sleep_ns(next_tick - now);
    }

    if (!running)
        return false;

    next_tick += tick_interval;

    if (now > next_tick + tick_interval * 4)
        next_tick = now + tick_interval;

    return true;
}
