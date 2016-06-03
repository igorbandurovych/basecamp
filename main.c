#include "myheap.h"
#include "util.h"
#include <stdio.h>

int main(void)
{
    heap_init(25);
    printf("heap_init(25)\n");
    my_map();

    char* x0 = my_malloc(20);
    printf("x0 = my_malloc(20) = 0x%x\n", x0);
    my_map();

    char* x8 = my_malloc(6);
    printf("x8 = my_malloc(6) = 0x%x\n", x8);
    my_map();

    char* x9 = my_malloc(5);
    printf("x9 = my_malloc(5) = 0x%x\n", x9);
    my_map();

    my_free(x0);
    printf("my_free(x0)\n");
    my_map();

    char* x1 = my_malloc(1);
    printf("x1 = my_malloc(1) = 0x%x\n", x1);
    my_map();

    char* x2 = my_malloc(4);
    printf("x2 = my_malloc(4) = 0x%x\n", x2);
    my_map();

    char* x3 = my_malloc(1);
    printf("x3 = my_malloc(1) = 0x%x\n", x3);
    my_map();

    my_free(x2);
    printf("my_free(x2)\n");
    my_map();

    char* x4 = my_malloc(5);
    printf("x4 = my_malloc(5) = 0x%x\n", x4);
    my_map();

    char* x5 = my_malloc(4);
    printf("x5 = my_malloc(4) = 0x%x\n", x5);
    my_map();

    char* x6 = my_malloc(9);
    printf("x6 = my_malloc(9) = 0x%x\n", x6);
    my_map();

    my_free(x3);
    printf("my_free(x3)\n");
    my_map();

    char* x7 = my_malloc(2);
    printf("x7 = my_malloc(2) = 0x%x\n", x7);
    my_map();

    heap_destroy();

    return 0;
}
