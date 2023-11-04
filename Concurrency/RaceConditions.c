#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void * withdrawFunds(void *);
void * addFunds(void *);

int balance = 100;
pthread_t pWithdrawFunds, pWithdrawFunds2, pAddFunds;

int main(int argc, char **argv) {
    while(1) {
        pthread_create(&pWithdrawFunds, NULL, withdrawFunds, NULL);
        pthread_create(&pWithdrawFunds2, NULL, withdrawFunds, NULL);
        pthread_create(&pAddFunds, NULL, addFunds, NULL);
        printf("balance = %d \n", balance);
        if(balance<0) {
            break;
        }
    }
    return 0;
}

void * withdrawFunds(void * p) {
    if(balance>=10) {
        balance -= 10;
    }
}

void * addFunds(void * p) {
    balance++;
}
