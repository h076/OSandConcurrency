#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void example();
void task1(int);

int main(int argc, char **argv) {
    if(argc == 2) {
        task1(atoi(argv[1]));
    }
}

void example() {
    pid_t pid = 0;
    // fork will create a child process, copy of the parent
    // the child will have a returned PID of 0
    // if fork cannot create a child then -1 is returned
    pid = fork();
    if(pid < 0) {
        printf("Could not create process\n");
        exit(1);
    } else if(pid == 0) {
        sleep(1);
        printf("Hello from the child process\n");
    } else if(pid > 0) {
        printf("Hello from the parent process\n");
    }
    printf("this code will be executed by both the child process and parent\n");
}

void task1(int NUMBER_OF_PROCESSES) {
    printf("%d\n", NUMBER_OF_PROCESSES);
    for(int i=0; i<NUMBER_OF_PROCESSES; i++) {
        fork();
        printf("instance %d, my PID is %d\n", i, getpid());
    }
}
