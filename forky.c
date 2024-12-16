#include "forky.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

unsigned int randomTime() { return (rand() % 8) + 1; }

void run_patterns(int numOfThings, int pattern) {
    switch (pattern) {
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

// in the picture, this is forking multiple processes from the main (fork ALL
// processes before waiting for any of them)
void pattern1(int numOfThings) {
    for (int ix = 0; ix < numOfThings; ix++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("Process %d with PID: %d beginning!\n", ix, getpid());
            sleep(randomTime());
            printf("Process %d with PID: %d ending!\n", ix, getpid());
            exit(0);
        }
    }
    // wait for all of the children to finish
    for (int ix = 0; ix < numOfThings; ix++) {
        wait(NULL);
    }
    printf("Main process with PID: %d ending!\n", getpid());
}

// in the picture, this is forking a single process from the main and then
// passing it on to the next process
void pattern2(int numOfThings) {
    fprintf(stderr, "Process 0 (%d) beginning\n", getpid());

    int pid = fork();

    if (pid == 0) {
        printf("Child 1 (%d) created by process 0 (%d)\n", getpid(), getppid());
        printf("Process 1 (%d) beginning\n", getpid());

        sleep(1);

        if (numOfThings > 1) {
            pattern2helper(numOfThings, 2);
        }

        printf("Process 1 (%d) exiting\n", getpid());
        exit(0);
    }
}

// helper function for pattern2 in which it creates a child process
void pattern2helper(int current, int max) {
    int pid = fork();

    if (pid == 0) {
        printf("Child %d (%d) created by process %d (%d)\n", current, getpid(),
               current - 1, getppid());
        printf("Process %d (%d) beginning\n", current, getpid());

        // this is the "do stuff" part
        sleep(1);

        if (current < max) {
            pattern2helper(max, current + 1);
        }

        fprintf(stderr, "Process %d (%d) exiting\n", current, getpid());
        exit(0);
    } else {
        wait(NULL);
    }

    return;
}
    printf("Main process with PID: %d ending!\n", getpid());
}
