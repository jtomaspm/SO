#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


void* rool_dice(void *){
    int value = rand() % 20 + 1;
    int* result = (int*) malloc(sizeof(int));
    *result = value;

    return (void*) result;
}


int main(int argc, char* argv[]){
    srand((unsigned int)time(NULL));
    int* res;
    pthread_t th;

    if (pthread_create(&th, NULL, &rool_dice, NULL) != 0) {
        return 1;
    }

    if (pthread_join(th, (void**) &res) != 0) {
        return 1;
    }

    printf("Result: %d\n", *res);
    free(res);

    return 0;
}
