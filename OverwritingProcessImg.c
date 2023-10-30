#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void example();
void task();

int main(int argc, char **argv) {
    if(argc==2) {
        task(atoi(argv[1]));
    }
    return 0;
}

void example() {
    int status;
    pid_t pid = fork();
    if(pid==-1) {
        printf("fork() error\n");
    }else if(pid==0) {
        execl("/bin/ps", "ps", "-1", 0);
        printf("This code should not run");
    }
}

void task(int NUMBER_OF_PROCESSES) {
    printf("%d\n", NUMBER_OF_PROCESSES);
    for(int i=0; i<NUMBER_OF_PROCESSES; i++) {
        fork();
        execl("/bin/ps", "ps", "1", -1);
        printf("instance %d, my PID is %d\n", i, getpid());
    }
}
