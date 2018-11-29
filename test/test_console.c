#include <array.h>
#include <conio.h>
#include <stdio.h>
#include <model/array_ext.h>
#include "test_console.h"

void printE(void* e) {
    printf("%d,", *((int*)e));
}

int comp(void* e1, void* e2) {
    return *((int*)e1) - *((int*)e2);
}

int mainConsole() {
    Array* a;
    array_new(&a);
    int i = 0;
    int* e;
    while (i != -1) {
        e = malloc(sizeof(int));
        scanf("%d", &i);
        *e = i;
        log_debug("%d", *e);
        array_add_sorted(a, e, comp);
        array_map(a, printE);
        printf("\n");
    }
}