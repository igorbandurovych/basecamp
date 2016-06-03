
/**
* @file		myheap.h
* @brief	The header file for functions to work with myheap
* @author	Igor Bandurovych
* @year		2016
*/

#ifndef MYHEAP_H
#define MYHEAP_H

#ifndef NULL
#define NULL ((void*)0)
#endif	/*NULL*/

#define SIZE_OF_KB (1024)			/**< size of 1 KB (in bytes) */
#define SIZE_OF_MB (1024 * 1024)	/**< size of 1 MB (in bytes) */

/**
* @brief	This function initializes myheap
* @param	[in]		size Size of myheap's data segment (in bytes)
* @warning	This function shall be called only once before heap_destroy() is called.
* @return	void
*/
void heap_init(const size_t size);

/**
* @brief	This function returns size of heap
* @return	size of heap is returned
*/
size_t heap_size(void);

/**
* @brief	This function allocates memory for size bytes in myheap
* @param	[in]		size Number of bytes to be allocated
* @return	pointer to allocated memory
* @return	NULL (if memory haven't been allocated)
*/
void* my_malloc(const size_t size);

/**
* @brief	This function releases a block of memory in myheap
* @param	[in]		data Pointer to block that is released
* @warning	This function shall be called with pointer to memory allocated by my_malloc
* @return	void
*/
void my_free(void* data);

/**
* @brief	This function returns pointer to start of heap
* @return	pointer to start of heap is returned
*/
void* heap_start(void);

/**
* @brief	This function returns pointer to start of service part
* @return	pointer to start of service part is returned
*/
void* info_start(void);

/**
* @brief	This function releases memory allocated by myheap
* @warning	This function shall be called only once after heap_init is called
* @return	void
*/
void heap_destroy(void);

#endif /*MYHEAP_H*/
