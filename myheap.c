/**
* @file		myheap.c
* @brief	The implementation file for functions declared in myheap.h
*
* @author	Igor Bandurovych
* @year		2016
*/

#include "myheap.h"

#include <stdlib.h>
#include <string.h>	/*<* memset*/

#define BYTE_IS_BUSY(offset)\
    ( *(manager.info + (offset) / 4) & 1 << 2 * ((offset) % 4) )

#define SET_AS_BUSY_WITHOUT_END(offset)\
    ( *(manager.info + (offset) / 4) |= 3 << 2 * ((offset) % 4) )

#define SET_AS_BUSY_END_OF_BLOCK(offset)\
    ( *(manager.info + (offset) / 4) &= ~(1 << ( 2 * ((offset) % 4) + 1) ) )

#define IS_NOT_END_OF_BLOCK(offset)\
    ( *(manager.info + (offset) / 4) & 1 << ( 2 * ((offset) % 4) + 1 ) )

#define SET_AS_FREE(offset)\
    ( *(manager.info + (offset) / 4) &= ~(3 << 2 * ((offset) % 4)) )


static struct
{
    unsigned char* info;		/*pointer to start of info segment*/
    unsigned char* data;		/*pointer to start of data segment*/
    unsigned char* free_mem;	/*pointer to the first block of free memory*/
    size_t size;				/*max memory that can be used*/
} manager;

void heap_init(const size_t size)
{
    if (size)	/*size != 0*/
    {
        heap_destroy();	/*removing previously allocated memory*/
        div_t info_size = div((int) size, 4);
        size_t additional_byte = info_size.rem ? 1 : 0;
        manager.info = (unsigned char*) malloc(info_size.quot + additional_byte);
        memset(manager.info, 0, info_size.quot + additional_byte);	/*setting whole info segment to 0*/
        manager.data = (unsigned char*) malloc(size);
        manager.size = (manager.info != NULL && manager.data != NULL) ? size : 0;
        if (!manager.size)	/*init failed*/
        {
            if (manager.data)
            {
                free(manager.data);
            }
            if (manager.info)
            {
                free(manager.info);
            }
        }
        manager.free_mem = manager.data;
    }
}

size_t heap_size(void)
{
    return manager.size;
}

void* my_malloc(const size_t size)
{
    if (manager.free_mem == manager.data + manager.size || size > manager.size || !size)
    {
        return NULL;	/*if no free memory left, requested size bigger than size of data segment or size == 0*/
    }
    unsigned char* result = manager.free_mem;
    size_t bytes_found = 0;
    size_t offset = manager.free_mem - manager.data;
    while (bytes_found != size)
    {
        /*if (2 * offset)-th bit of info segment is 0 (offset-th byte in data segment is free) */
        if (!BYTE_IS_BUSY(offset) && offset < manager.size)
        {
            ++bytes_found;
            ++offset;
        }
        else
        {
            bytes_found = 0;
            /*while (2 * offset)-th bit of info segment is 1 (offset-th byte in data segment is busy)
              and it is possible to allocate memory in myheap*/
            while (BYTE_IS_BUSY(offset) && offset < manager.size)
            {
                ++offset;
            }
            if (offset == manager.size)
            {
                return NULL;	/*allocation is impossible, no space for requested amount of memory*/
            }
            result = manager.data + offset;
        }
    }

    size_t counter = offset - 1;


    /*setting all allocated bytes in info segment as busy*/
    while (bytes_found--)
    {
        SET_AS_BUSY_WITHOUT_END(counter);
        --counter;
    }

    /*point the end of memory block (10)*/
    SET_AS_BUSY_END_OF_BLOCK(offset - 1);

    /*find pointer to the first block of free memory (if memory allocated at free_mem)*/
    if (result == manager.free_mem)
    {
        while (BYTE_IS_BUSY(offset) && offset < manager.size)
        {
            ++offset;
        }
        manager.free_mem = manager.data + offset;
    }
    return result;
}

void my_free(void* data)
{
    unsigned char* data_to_free = (unsigned char*) data;

    /*data doesn't belong to heap*/
    if (data_to_free < manager.data || data_to_free > manager.data + manager.size)
    {
        return;
    }
    const size_t start_offset = data_to_free - manager.data;
    size_t offset = start_offset;

    //finding end of block
    while (IS_NOT_END_OF_BLOCK(offset) && ++offset != manager.size) continue;

    /*setting all allocated bytes in info segment as free*/
    while (offset != start_offset)
    {
        SET_AS_FREE(offset);
        --offset;
    }

    /*always free first byte of sequence!*/
    SET_AS_FREE(start_offset);

    /*change pointer to the first block of free memory (if flags removed before free_mem)*/
    if (data_to_free < manager.free_mem)
    {
        manager.free_mem = data_to_free;
    }
}

void* heap_start(void)
{
    return manager.data;
}

void* info_start(void)
{
    return manager.info;
}

void heap_destroy(void)
{
    if (manager.size)	/*manager.size != 0*/
    {
        free(manager.info);
        free(manager.data);
    }
}
