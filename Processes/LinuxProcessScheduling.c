#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_OF_PROCESSES 4

// looking at logging process time

long int getDifferenceInMilliSeconds(struct timeval start, struct timeval end);
long int getDifferenceInMicroSeconds(struct timeval start, struct timeval end);
void example();
void task4();
void task5();

int main(int argc, char **argv) {
    task5();
    return 0;
}

// determine the time taken to fork the process and running it
void task4() {
    int status;
    pid_t pid;
    struct timeval startTime, currentTime;

    gettimeofday(&startTime, NULL);
    for(int i=0; i<NUM_OF_PROCESSES; i++) {
        //gettimeofday(&startTime, NULL);
        pid=fork();
        gettimeofday(&currentTime, NULL);
        int time = getDifferenceInMicroSeconds(startTime, currentTime);
        if(pid<0) {
            printf("fork() error");
        } else if(pid>0) {
            printf("Hello from the parent process\n");
        } else if(pid==0) {
            printf("Hello from the child %d with pid %d at time %d\n", i, getpid(), time);
            return;
        }
        //waitpid(pid, &status, WUNTRACED);
    }
    waitpid(pid, &status, WUNTRACED);
    printf("Bye from the parent!\n");
    return;
}


void task5() {
    int status;
    pid_t pid;
    struct timeval baseTime, currentTime;
    long int times[NUM_OF_PROCESSES];
    //printf("Hello from the parent process\n");
    while(1) {
        gettimeofday(&baseTime, NULL);
        for(int i=0; i<NUM_OF_PROCESSES; i++) {
            pid=fork();
            gettimeofday(&currentTime, NULL);
            times[i] = getDifferenceInMilliSeconds(baseTime, currentTime);
        }
        for(int i=0; i<NUM_OF_PROCESSES; i++) {
            printf(" %d : %ld", i, times[i]);
        }
        printf("\n");
    }
    printf("Bye from the parent!\n");
    return;
}

// shows the difference in milli and microp seconds of two points in the program
void example() {
    int i;
    struct timeval startTime, currentTime;
    gettimeofday(&startTime, NULL);
    sleep(1);
    gettimeofday(&currentTime,NULL);
    printf("Difference in milli-seconds %ld\n",
       getDifferenceInMilliSeconds(startTime, currentTime));
    printf("Difference in micro-seconds %ld\n",
       getDifferenceInMicroSeconds(startTime, currentTime));
}

long int getDifferenceInMilliSeconds(struct timeval start, struct timeval end) {
    int seconds = end.tv_sec - start.tv_sec;
    int useconds = end.tv_usec - start.tv_usec;
    int mtime = (seconds * 1000 + useconds / 1000.0);
    return mtime;
}

long int getDifferenceInMicroSeconds(struct timeval start, struct timeval end) {
    int seconds = end.tv_sec - start.tv_sec;
    int useconds = end.tv_usec - start.tv_usec;
    int mtime = (seconds * 1000000 + useconds);
    return mtime;
}
