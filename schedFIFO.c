// Compiler flags: gcc -O0 name.c -o name -Wall -lm -lpthread

#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>

#define PERIOD 1000000  // Control Period (1000000 ns = 1 ms)
#define SEC_IN_NANOSEC 1000000000

void time_norm(struct timespec *ts)
{
    while (ts->tv_nsec >= SEC_IN_NANOSEC)
    {
        ts->tv_nsec -= SEC_IN_NANOSEC;
        ts->tv_sec++;
    }
}

void *thread_func(void *data)
{
    double start_time;
    double end_time = 0;
    struct timespec time_line;

    while (1)
    {
        start_time = end_time;
        clock_gettime(CLOCK_MONOTONIC, &time_line);
        end_time = time_line.tv_nsec;

        // Add the time you want to sleep
        time_line.tv_nsec += PERIOD;

        // Normalize the time to account for the second boundary
        time_norm(&time_line);

        // Print Period in [ms]...
        printf("%lf ms since last wake up\n", (end_time - start_time) / 1000000.0);


         /* WRITE YOUR CODE BELOW */
        for (int i = 0; i < 150000; i++)
        {
            int j = 0;
            j++;
        }


        // Wait until next period...
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &time_line, NULL);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    struct sched_param param;
    pthread_attr_t attr;
    pthread_t thread;
    int ret;

    /* Lock memory */
    if (mlockall(MCL_CURRENT | MCL_FUTURE) == -1)
    {
        printf("mlockall failed: %m\n");
        exit(-2);
    }

    /* Initialize pthread attributes (default values) */
    ret = pthread_attr_init(&attr);
    if (ret)
    {
        printf("init pthread attributes failed\n");
        goto out;
    }

    /* Set a specific stack size  */
    ret = pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    if (ret)
    {
        printf("pthread setstacksize failed\n");
        goto out;
    }

    /* Set scheduler policy and priority of pthread */
    ret = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    if (ret)
    {
        printf("pthread setschedpolicy failed\n");
        goto out;
    }
    param.sched_priority = 80;
    ret = pthread_attr_setschedparam(&attr, &param);
    if (ret)
    {
        printf("pthread setschedparam failed\n");
        goto out;
    }
    /* Use scheduling parameters of attr */
    ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    if (ret)
    {
        printf("pthread setinheritsched failed\n");
        goto out;
    }

    /* Create a pthread with specified attributes */
    ret = pthread_create(&thread, &attr, thread_func, NULL);
    if (ret)
    {
        printf("create pthread failed\n");
        goto out;
    }

    /* Join the thread and wait until it is done */
    ret = pthread_join(thread, NULL);
    if (ret)
        printf("join pthread failed: %m\n");

out:
    return ret;
}
