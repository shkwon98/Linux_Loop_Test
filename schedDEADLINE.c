// Compiler flags: gcc -O0 name.c -o name -Wall -lm -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include "schedDEADLINE.h"

static void time_diff(struct timespec *diff, struct timespec *stop, struct timespec *start)
{
    if (stop->tv_nsec < start->tv_nsec)
    {
/* here we assume (stop->tv_sec - start->tv_sec) is not zero */
        diff->tv_sec = stop->tv_sec - start->tv_sec - 1;
        diff->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
    }
    else
    {
        diff->tv_sec = stop->tv_sec - start->tv_sec;
        diff->tv_nsec = stop->tv_nsec - start->tv_nsec;
    }
}


void *rt_thread(void *data)
{
/* scheduler attributes */
    struct sched_attr attr;
    float period_ms = 1;

    printf("deadline rt_thread started [%ld]\n", gettid());

    /* set up sched_attr structure */
    attr.size = sizeof(attr);
    attr.sched_policy = SCHED_DEADLINE;
    attr.sched_flags = 0;
    attr.sched_nice = 0;
    attr.sched_priority = 0;
    attr.sched_runtime = 0.95 * period_ms * 1000 * 1000;
    attr.sched_period = attr.sched_deadline = period_ms * 1000 * 1000;

    /* set sched deadline */
    if (sched_setattr(gettid(), &attr, 0))
    {
        perror("sched_setattr");
        exit(1);
    }

    /* time measurements */
    struct timespec last, now, diff;
    clock_gettime(CLOCK_MONOTONIC, &last);

    /* loop starts */
    while (1)
    {

/* time measurements */
        clock_gettime(CLOCK_MONOTONIC, &now);
        time_diff(&diff, &now, &last);
        printf("%ld.%06ld ms since last wake up\n", diff.tv_sec * 1000 + diff.tv_nsec / 1000000, diff.tv_nsec % 1000000);
        last = now;


        /* WRITE YOUR CODE BELOW */
        for (int i = 0; i < 150000; i++)
        {
            int j = 0;
            j++;
        }


        sched_yield();
        //sched_wait_interval();
    }

    printf("deadline rt_thread dies [%ld]\n", gettid());
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t thread;

    printf("main thread started [%ld]\n", gettid());

    /* Create a pthread with specified attributes */
    pthread_create(&thread, NULL, rt_thread, NULL);
    sleep(10);

    /* Join the thread and wait until it is done */
    pthread_join(thread, NULL);

    printf("main thread dies [%ld]\n", gettid());
    return 0;
}
