//
// Created by helio on 06.05.23.
//


#include <stdio.h>
#include <stdlib.h>

#ifdef DMALLOC
#include "dmalloc.h"
#endif

void *foo() {
    char *p = (char*) malloc(1023);
    p[1023] = '\0';
    return p;
}

int main() {
    foo();
    return 0;
}