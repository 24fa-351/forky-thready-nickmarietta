#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

#include "forky.h"

unsigned int randomTime()
{
    return (rand() % 8) + 1;
}

void run_patterns(int numOfThings, int pattern)
{
    switch (pattern)
    {
    case 1:
        printf("Running pattern 1\n");
        pattern1(numOfThings);
        break;
    case 2:
        printf("Running pattern 2\n");
        pattern2(numOfThings);
        break;
    }
}

// in the picture, this is forking multiple processes from the main (fork ALL processes before waiting for any of them)
void pattern1(int numOfThings)
{
    for (int ix = 0; ix < numOfThings; ix++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            printf("Process %d with PID: %d beginning!\n", ix, getpid());
            sleep(randomTime());
            printf("Process %d with PID: %d ending!\n", ix, getpid());
            exit(0);
        }
    }
    // wait for all of the children to finish
    for (int ix = 0; ix < numOfThings; ix++)
    {
        wait(NULL);
    }
    printf("Main process with PID: %d ending!\n", getpid());
}

// in the picture, this is forking a single process from the main and then passing it on to the next process
void pattern2(int numOfThings)
{
    for (int ix = 1; ix <= numOfThings; ix++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            printf("Process %d with PID: %d beginning!\n", ix, getpid());
            sleep(randomTime());

            // end the process being passed
            if (ix == numOfThings)
            {
                printf("Process %d with PID: %d ending!\n", ix, getpid());
                exit(0);
            }
            // create the next process with the previous process
            printf("Process %d now creating Process %d\n", ix, ix + 1);
        }
        else
        {
            wait(NULL);
            printf("Process %d with PID: %d ending!\n", ix, getpid());
            exit(0);
        }
    }
    printf("Main process with PID: %d ending!\n", getpid());
}