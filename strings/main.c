#include <stdio.h>
#include <stdlib.h> 
#include "tstrings.h"

void print_string(String *str) {
    printf("Value: %s\n", str->value);
    printf("Blocks: %d\n", str->blocks);
    printf("Length: %d\n\n", str->length);
}

int main() {
    String *s1 = create_empty_string();
    String *s2 = create_string("Gustavo");
    String *s3 = create_string("blablabla");
    
    print_string(s1);
    print_string(s2);
    print_string(s3);
    return 1;
}
