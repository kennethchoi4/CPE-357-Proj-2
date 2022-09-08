#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "a2defs.h"

#define LINELEN 80

FILE *safeOpen(char *file, char *mode){
    FILE *fptr; 
    if ((fptr = fopen(file, mode)) == NULL){
        safeClose(fptr);
        perror("No such file or directory");
    }
    return fptr;
}

void safeClose(FILE *file){
    int status;
    if ((status = fclose(file)) == EOF){
        perror("Error when closing file");
    }
    return;
}


void *safeAlloc(size_t size){
    void *ptr;
    if ((ptr = calloc(LINELEN, size)) == NULL){
        exit(-1);
    }
    return ptr;
}

void *safeRealloc(void *ptr, size_t size){
    if ((ptr = (void*)realloc(ptr, size)) == NULL){
        exit(-1);
    }
    return ptr;
}
char *rmNL(char *ogptr){
    char *ptr = NULL;
    ptr = strstr(ogptr, "\n");

    while(ptr != NULL){
        strncpy(ptr, "", 1);   
        ptr = strstr(ogptr, "\n");
    }

    free(ptr);
    ptr = NULL;
    return ogptr;


}

    