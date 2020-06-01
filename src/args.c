#include "args.h"


args *args_create(char *key, char *val, char *std) {
    args *newA = malloc(sizeof(args));
    if (!newA) return NULL;
    
    unsigned long c_str_len = 0;
    
    newA->next = NULL;

    // Key
    c_str_len = strlen(key) + 1;
    newA->key = malloc(sizeof(char) * c_str_len);
    if (!newA->key) {
        free(newA);
        return NULL;
    }
    newA->key = memcpy(newA->key, key, c_str_len);
    
    // Value
    c_str_len = strlen(val) + 1;
    newA->val = malloc(sizeof(char) * c_str_len);
    if (!newA->val) {
        free(newA->key);
        free(newA);
        return NULL;
    }
    newA->val = memcpy(newA->val, val, c_str_len);
    
    // Standard value
    c_str_len = strlen(std) + 1;
    newA->std = malloc(sizeof(char) * c_str_len);
    if (!newA->std) {
        free(newA->key);
        free(newA->val);
        free(newA);
        return NULL;
    }
    newA->std = memcpy(newA->std, std, c_str_len);


    return newA;
}

void args_free(args **a) {
    if (a == NULL || *a == NULL) return;
    
    if ((*a)->next) { // Recursively free all following args
        args_free(&((*a)->next));
    }

    if ((*a)->key) free((*a)->key);
    if ((*a)->val) free((*a)->val);
    if ((*a)->std) free((*a)->std);

    free(*a);
    *a = NULL;
}

int args_append(args *a, args *newa) {
    if (a == NULL || newa == NULL) return 1;

    args *cArg = a;
    while (cArg->next) { // Traverse until end was found
        cArg = cArg->next;
    }
    
    cArg->next = newa;
    newa->next = NULL;

    return 0;
}


args *args_parse(int argc, char *argv[]) {
    args *parsed = args_create("mode", "normal", "normal");
    
    return parsed;
}


char *args_get(char *key) {
    // TODO get backup and return string given.
    return NULL;
}
