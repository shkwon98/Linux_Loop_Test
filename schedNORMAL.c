#include <stdio.h>
#include <time.h>

void time_norm(struct timespec *ts)
{
    if (ts->tv_nsec >= 1000000000)
    {
        ts->tv_nsec -= 1000000000;
        ts->tv_sec++;
    }
}

int main()
{

    double start_time;
    double end_time = 0;
    struct timespec time_line;

    while (1)
    {
        start_time = end_time;
        clock_gettime(CLOCK_MONOTONIC, &time_line);
        end_time = time_line.tv_nsec;

        for (int i = 0; i < 150000; i++)
        {
            int j = 0;
            j++;
        }

        printf("%lf ms since last wake up\n", (end_time - start_time) / 1000000.0);
    }

    return 0;
}
