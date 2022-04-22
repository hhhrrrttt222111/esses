#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  
#include <pthread.h> 

#define NUM_PHIL 5

int chopsticks[NUM_PHIL];


void *phil_behaviour(void* id) {   
    int phil_num = *((int*)id);

    while(1) {

        printf("Philosopher %d is THINKING\n", phil_num+1);
        sleep(1);
        
        printf("Philosopher %d is Hungry\n", phil_num+1);

        while(1) {
            if(chopsticks[phil_num] == 1)
                continue;            

            if(chopsticks[(phil_num+1)%NUM_PHIL] == 1)
                continue;

            chopsticks[phil_num] = 1;
            chopsticks[(phil_num+1)%NUM_PHIL] = 1;

            printf("Philosopher %d picks #%d and #%d chopsticks up\n", phil_num+1, phil_num+1, 1 + ((phil_num+1)%NUM_PHIL));

            printf("Philosopher %d is Eating Food\n", phil_num+1);
            sleep(1);

            chopsticks[phil_num] = 0;
            chopsticks[(phil_num+1)%NUM_PHIL] = 0;
            
            printf("Philosopher %d puts #%d and #%d chopsticks down\n", phil_num+1, phil_num+1, 1 + ((phil_num+1)%NUM_PHIL));
            break;
        }
    }
}

void *phil_behaviour_rev(void* id) {
    int phil_num = *((int*)id);

    while(1) {

        printf("Philosopher %d is THINKING\n", phil_num+1);
        sleep(1);

        printf("Philosopher %d is Hungry\n", phil_num+1);

        while(1) {

            if(chopsticks[(phil_num+1)%NUM_PHIL] == 1)
                continue;

            if(chopsticks[phil_num] == 1)
                continue;            
            
            chopsticks[(phil_num+1)%NUM_PHIL] = 1;
            chopsticks[phil_num] = 1;

            printf("Philosopher %d picks #%d and #%d chopsticks up\n", phil_num+1, phil_num+1, 1 + ((phil_num+1)%NUM_PHIL));

            printf("Philosopher %d is Eating Food\n", phil_num+1);
            sleep(1);

            chopsticks[phil_num] = 0;
            chopsticks[(phil_num+1)%NUM_PHIL] = 0;
            
            printf("Philosopher %d puts #%d and #%d chopsticks down\n", phil_num+1, phil_num+1, 1 + ((phil_num+1)%NUM_PHIL));

            break;
        }
    }
}

int main(int argc, char const *argv[]) {

    pthread_t thread_ids[NUM_PHIL];
    int phil_nums[NUM_PHIL];

    for (int i = 0; i < NUM_PHIL; i++) {
        phil_nums[i] = i;
    }


    for (int i = 0; i < NUM_PHIL; i++) {
        chopsticks[i] = 0;
    }

    for (int i = 0; i < NUM_PHIL-1; i++) {
        pthread_create(&thread_ids[i], NULL, phil_behaviour, (void*)&phil_nums[i]); 
    }


    pthread_create(&thread_ids[NUM_PHIL-1], NULL, phil_behaviour_rev,(void*) &phil_nums[NUM_PHIL-1]); 

    for (int i = 0; i < NUM_PHIL; i++) {
        pthread_join(thread_ids[i], NULL); 
    }

    exit(0);
}