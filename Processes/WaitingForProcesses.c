#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_OF_PROCESSES 4

int example();
void task();

int main(int argc, char **argv) {
    //example();
    task();
    return 0;
}

int example() {
    int i, status;
    pid_t pid;
    printf("Hello from parnet process with PID of %d\n", getpid());
    pid = fork();
    if(pid<0) {
        printf("fork() error\n");
    }else if(pid==0){
        sleep(1);
        printf("Hello from the child process with PID of %d\n", getpid());
        return 0;
    }
    // waitpid will ensure the parent process waits until child process has been carried out
    // must pass the childs pid as a parameter
    waitpid(pid, &status, WUNTRACED);
    printf("Child process has finished\n");
    return 0;
}

void task() {
    int status;
    pid_t pid;
    //printf("Hello from the parent process\n");
    for(int i=0; i<NUM_OF_PROCESSES; i++) {
        pid=fork();
        if(pid<0) {
            printf("fork() error");
        } else if(pid>0) {
            printf("Hello from the parent process\n");
        } else if(pid==0) {
            printf("Hello from the child %d with pid %d\n", i, getpid());
            return;
        }
        //waitpid(pid, &status, WUNTRACED);
    }
    waitpid(pid, &status, WUNTRACED);
    printf("Bye from the parent!\n");
    return;
}
