#include "head.h"

//get time [nanosecond]
int64_t get_time_ns(){
#ifdef __WINDOWS__
    static LARGE_INTEGER freq;
    static bool initialized = false;
    if (!initialized) {
        QueryPerformanceFrequency(&freq);
        initialized = true;
    }

    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);

    return (int64_t)((t.QuadPart * 1000000000LL) / freq.QuadPart);
#else
    struct::timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * int64_t(1'000'000'000) + t.tv_nsec;
#endif
}
