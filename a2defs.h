#ifndef A2DEFS_H
#define A2DEFS_H

#define QA "qa.db"
#define READ  "r"
#define WRITE  "w"
#define APPENDP "a+"
#define LINELEN 80

FILE *safeOpen(char*, char*);

void safeClose(FILE*);

void *safeAlloc(size_t);

void *safeRealloc(void*, size_t);

char *rmNL(char*);

#endif 