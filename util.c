
/**
* @file		util.c
* @brief	The implementation file for functions declared in util.h
* @author	Igor Bandurovych
* @year		2016
*/

#include "util.h"
#include "myheap.h"
#include <stdio.h>	/*<* printf*/

#define BYTE_IS_BUSY(info, offset)\
    ( *((info) + (offset) / 4) >>  2 * ((offset) % 4) & 1 )

void my_map(void)
{
    size_t data_size = heap_size();
    unsigned char* data = (unsigned char*)heap_start();
    unsigned char* info = (unsigned char*)info_start();
    size_t counter = 0;
    size_t block;
    char is_busy;
    printf("relative\treal address\tstate\tsize\n");
    while (counter != data_size)
    {
        is_busy = BYTE_IS_BUSY(info, counter);
        printf("0x%x\t\t0x%x\t%s", counter, data + counter,
            (is_busy) ? "busy\t" : "free\t");
        ++counter;
        block = 1;
        while (BYTE_IS_BUSY(info, counter) == is_busy && counter < data_size)
        {
            ++counter;
            ++block;
        }
        printf("%d\n", block);
    }
    printf("\n");
}
