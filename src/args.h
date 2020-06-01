#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdarg.h>

typedef struct args {
    struct args *next;

    char *key,
         *val,
         *std;
} args;

args *args_create(char *key, char *val, char *std);


void args_free(args **a);


int args_append(args *a, args *newa);


args *args_parse(int argc, char *argv[]);

char *args_get(char *key);
