#include "tstrings.h"
#include <stdlib.h>

int size_of(const char *value) {
    if (value == NULL) {
        return 0;
    }

    int count = 0;
    
    while (value[count] != '\0') {
        count++;
    }

    return count;
}

int calc_blocks_of(int string_length) {
    return (string_length / BLOCK_SIZE) + 1;
}

char *alloc_string_value(int blocks) {
    return (char*) malloc(BLOCK_SIZE * blocks * sizeof(char));
}

String *create_string(const char *value) {
    String *str = (String*) malloc(sizeof(String));

    str->length = size_of(value);
    str->blocks = calc_blocks_of(str->length);
    str->value = alloc_string_value(str->blocks);

    for (int i = 0; i < str->length; i++) {
        str->value[i] = value[i];
    }

    return str;
}

String *create_empty_string() {
    return create_string("");
}

String *append(String *s1, String *s2) {
    int new_length = s1->length + s2->length;

    if (s1->blocks * BLOCK_SIZE <= new_length) {
        int new_blocks = calc_blocks_of(s1->length + s2->length);

        s1->value = (char*) realloc(s1->value, new_blocks * BLOCK_SIZE * sizeof(char));
        s1->blocks = new_blocks;
    }

    for (int i = 0; i < s2->length; i++) {
       s1->value[s1->length + i] = s2->value[i]; 
    }

    s1->length = new_length;
    return s1;
}


String *substring(String *str, int start, int end) {
    int length = end - start + 1;

    String *res = (String*) malloc(sizeof(String));

    res->length = length;
    res->blocks = calc_blocks_of(length);
    res->value = alloc_string_value(res->blocks);

    for (int i = 0; i < length; i++) {
        res->value[i] = str->value[start + i];
    }

    return res;
}
