#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "a2defs.h"
#include "tnode.h"

#define NL "\n"


struct tnode *createNode (char *data){
    struct tnode *temp = talloc();
    data = rmNL(data);
    temp->data = data;
    temp->lleaf = NULL;
    temp->rleaf = NULL;

    if(strlen(temp->data) == 0){
        perror("Corrupted File Empty line for data");
        exit(-1);
    }
    /* sets node/leaf flag */
    if (data[strlen(data)- 1] == '?'){
        temp->type = 1;
    }
    else{
        temp->type = 0;
    }
    return temp;
}

struct tnode *talloc(){          /* allocates space for a node */
    return (struct tnode *) safeAlloc(sizeof(struct tnode));
}

struct tnode *createTree(FILE *file){
    char *string = (char*)stringInput(file);
    
    /* base case */
    if (string == NULL){
        return NULL;
    }

    /* might want to remove this 
    string = (char*) realloc(string, strlen(string) * sizeof(char)); */
    struct tnode *temp = createNode(string);

    if (temp->type == 1){
        temp->lleaf = createTree(file);
        temp->rleaf = createTree(file);
    }
    return temp;
};

void preorder(struct tnode *node, FILE *file, int cnt){
    if (node == NULL){
        return;
    }

    if (cnt != 0){
            fputc('\n', file);
        }
    cnt++;      
    fputs(node->data, file);
    preorder(node->lleaf, file, cnt);
    preorder(node->rleaf, file, cnt);
    return;
}

void freeTree(struct tnode *node){
    /* uses postorder traversal to free tree */
    if (node == NULL){
        return;
    }

    freeTree(node->lleaf);
    freeTree(node->rleaf);

    free(node->data);
    free(node);
}

void checkValid(struct tnode *node){
    if (node == NULL){
        return (void)NULL;
    }

    checkValid(node->lleaf);
    checkValid(node->rleaf);


    if (node->type == 1 && (!(node->lleaf)|| !(node->rleaf))){
        printf("Corrupted File: Question node has a NULL leaf node.\n");
        exit(-1);
    }
    if (node->type == 0 && ((node->lleaf)|| (node->rleaf))){
        printf("Node: %s\nLleaf: %s\nRleaf: %s\n", node->data, node->lleaf, node->rleaf);
        printf("Corrupted File: Answer node has a non-NULL leaf.\n");
        exit(-1);
    }

}

char *stringInput(FILE *file){
    size_t size = sizeof(char) * LINELEN;
    char *string = (char*)safeAlloc(size);
    getline(&string, &size, file);
    return string;
}


