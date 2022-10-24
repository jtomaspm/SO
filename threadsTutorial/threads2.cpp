#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int mails = 0;
pthread_mutex_t mutex;


void* routine(void*){
    for(int i = 0; i < 1000000; i++){
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t t1, t2;

    //initialise mutex
    pthread_mutex_init(&mutex, NULL);

    if(pthread_create(&t1, NULL, &routine, NULL)){
        return 1;
    }
    if(pthread_create(&t2, NULL, &routine, NULL)){
        return 1;
    }
    if(pthread_join(t1, NULL)){
        return 1;
    }
    if(pthread_join(t2, NULL)){
        return 1;
    }

    //Destroy mutex (free memory)
    pthread_mutex_destroy(&mutex);

    printf("Number of mails: %d\n", mails);

    return 0;
}
