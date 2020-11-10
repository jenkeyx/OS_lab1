#define _GNU_SOURCE
#include <sys/mman.h>
#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>


#define memSize 140
#define threadNum 70

void* readInThread(void* memPointer, FILE* name){fread(memPointer,1,memSize,name);}

void fillMemory() {
    //аллоцируем память и получаем указатель на ее начало
    void* allocPointer = malloc(memSize);
    //определяем рандомный поток
    FILE* urandom = fopen("dev/random","r");
    //создаем 70 потоков и заполняем их символами из urandom
    pthread_t symbolThread[threadNum];
    for (int i = 0; i < threadNum; i++) pthread_create(&symbolThread, NULL, readInThread(allocPointer, urandom), NULL);
    for (int i = 0; i < threadNum; i++) pthread_join(symbolThread[i], NULL);
    fclose(urandom);
}
int main() {
    fillMemory();
    return 0;
}

