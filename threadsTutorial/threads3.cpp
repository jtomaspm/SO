#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int mails = 0;
pthread_mutex_t mutex;


void* routine(void*){
    for(int i = 0; i < 10000000; i++){
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t th[6];
    int arr_len= sizeof(th)/sizeof(th[0]);

    //initialise mutex
    pthread_mutex_init(&mutex, NULL);

    int i;
    for(i=0; i < arr_len; i++){
        if(pthread_create(&th[i], NULL, &routine, NULL) != 0){
            return 1;
        }
        printf("thread nr: %d, started\n", i);
    }
    
    for(i=0; i < arr_len; i++){
        if(pthread_join(th[i], NULL) != 0){
            return 1;
        }
        printf("thread nr: %d, ended\n", i);
    }

    //Destroy mutex (free memory)
    pthread_mutex_destroy(&mutex);

    printf("Number of mails: %d\n", mails);

    return 0;
}
