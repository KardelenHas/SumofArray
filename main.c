#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[16] = { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220 };

void* routine(void* arg) {
    int index = *(int*)arg;
    int sum = 0;
    for (int j = 0; j < 16; j++) {
        sum += primes[index + j];
    }
    printf("Local sum: %d\n", sum);
    *(int*)arg = sum;
    return arg;
}

int main(int argc, char* argv[]) {
    pthread_t th[1];
    int i;
    for (i = 0; i < 1; i++) {
        int* a = malloc(sizeof(int));
        *a = i * 1;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("sum failed");
        }
    }
    int globalSum = 0;
    for (i = 0; i < 1; i++) {
        int* r;
        if (pthread_join(th[i], (void**) &r) != 0) {
            perror("sum failed");
        }
        globalSum += *r;
        free(r);
    }
    printf("Global sum: %d\n", globalSum);
    return 0;
}
