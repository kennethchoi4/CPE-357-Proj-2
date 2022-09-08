#ifndef NODE_H
#define NODE_H

struct tnode{    
    char *data;             /* points to question or answer */
    struct tnode *lleaf;     /* left leaf node */
    struct tnode *rleaf;     /* right leaf node */
    int type;               /* tells us if child or node */
};

struct tnode *talloc();

struct tnode *createNode (char*);

struct tnode *createTree(FILE*);

void preorder(struct tnode*, FILE*, int);

char *stringInput(FILE*);

#endif 