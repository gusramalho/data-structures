#ifndef TSTRINGS_H
#define TSTRINGS_H

#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 64

typedef struct tstring {
    char* value;
    int length;
    int blocks;
} String;

String *create_empty_string();

String *create_string(const char *value);

String *append(String *s1, String *s2);

String *substring(String *str, int start, int end);

#endif // DEBUG
