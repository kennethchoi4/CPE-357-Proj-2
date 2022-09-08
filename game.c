#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "a2defs.h"
#include "tnode.h"

#define QM "?"

void game(struct tnode *head){
    int firstNode = 0;
    struct tnode *curNode = head;
    size_t size = sizeof(char) * LINELEN;
    do{
        if (strlen(curNode->data) == 0){
            perror("Corrupt File: first question is empty!");
            exit(-1);

        }

        if (curNode->type == 0){
            /* root node is a answer */
            break;
        }

        printf("%s", curNode->data);
        char *input = (char*) safeAlloc(size);
        getline(&input, &size, stdin);

        /* handles yes input */
        if (input[0] == 'y' || input[0] == 'Y'){
            curNode = curNode->rleaf;
            free(input);
        }  
        else{
            curNode = curNode->lleaf;
            free(input);
        } 
    }while(curNode->lleaf != NULL || curNode->rleaf != NULL);
    

    printf("Is it %s?", curNode->data);

    /* reached answer node */
    char *input = (char*) safeAlloc(size);
    getline(&input, &size, stdin);

    /* prevent empty string input */
    while(input[0] == '\n'){
        getline(&input, &size, stdin);
    }

    if (input[0] == 'y' || input[0] == 'Y'){
    /* answer guess is correct */        
            printf("\nMy I am clever. :) Thanks for playing\n");
            free(input);
    }  
    else{
            /*remove newline for input due to print output*/ 
            input = rmNL(input);

            printf("\nHow disappointing.\nWhat it is(with article)? ");
            char *answer = stringInput(stdin);
            /* prevent empty string input */
            while(answer[0] == '\n'){
                getline(&answer, &size, stdin);
            }    
            answer = rmNL(answer);

            printf("\nWhat is a yes/no question that will distinguish %s from %s?\n? ", answer, curNode->data);
            char *question = stringInput(stdin);
            /* prevent empty string input */
            while(question[0] == '\n'){
                getline(&question, &size, stdin);
            }
            question = rmNL(question);

            printf("\nWhat is the answer to the question for %s?", answer);
            char *response = stringInput(stdin);
            /* prevent empty string input */
            while(response[0] == '\n'){
                getline(&response, &size, stdin);
            }
            response = rmNL(response);
            

            /* change the leaves before the data in order to preserve the data pointer 
            char *temp = curNode->data; */

            if (response[0] == 'y' || response[0] == 'Y'){
                /* edit node so that response is rleaf of question */
                curNode->rleaf = createNode(answer);
                curNode->lleaf = createNode(curNode->data);
            }
            else{
                /* edit ndoe so that response is lleaf of question */
                curNode->rleaf = createNode(curNode->data);
                curNode->lleaf = createNode(answer);
            }
            if ((question[strlen(question) - 1]) != '?'){
                question = strcat(question, QM);
            }
            curNode->data = question;
            printf("I'll get it next time, I'm sure. Thanks for playing.");
            free(response);
            free(input);
    } 
    return;
}