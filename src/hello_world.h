#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include <stdio.h>

// the configured options and settings for hello world
#define helloworld_VERSION_MAJOR @helloworld_VERSION_MAJOR@
#define helloworld_VERSION_MINOR @helloworld_VERSION_MINOR@
#define helloworld_VERSION_PATCH @helloworld_VERSION_PATCH@

extern __thread int globalErrorNumber;
#define reportError(err) (globalErrorNumber = (err))
#define hw_errono (globalErrorNumber)

#define HW_INDEX_ERROR 1

typedef struct _Record {
    struct _Record* next;
    char* value;
    struct _Record* previous;
} _Record;

typedef struct List {
    _Record *data;
    int length;
} List;

/**
 * @brief Inserts the given record at the given index of the list of strings
 * 
 * @param records doubly linked list of records
 * @param value new value to be inserted
 * @param index index where the value is to be inserted
 */
void insertItem(List *records, char* value, int index);

/**
 * @brief Appends the given value to the end of the list
 * 
 * @param records doubly linked list of records
 * @param value new value to be appended to the end of the records
 */
void appendItem(List *records, char* value);

/**
 * @brief finds the value at the given index and returns it
 * 
 * @param records 
 * @param index 
 * @return char* 
 */
char* findItem(List *records, int index);

/**
 * @brief deletes the item at the given index in records
 * 
 * @param records 
 * @param index 
 */
void deleteItem(List *records, int index);

/**
 * @brief Frees up memory for the list. Call this when the list is no longer needed.
 * 
 * @param records the doubly linked list which is to be removed from memory
 */
void freeList(List *records);

/**
 * @brief prints the linked list
 * 
 * @param records the doubly-linked list to be printed
 * @param stream the stream file descriptor pointor to which to output the data
 */
void printList(List *records, FILE* stream);

/**
 * @brief Create a Heap Allocated String object
 * 
 * @param str the sring to be copied to the heap
 * @param maxCharaters maximum number of characters the tring must have
 * @return char*
 */
char* __createHeapAllocatedString(char * str, int maxCharaters);

#endif /* HELLO_WORLD_H */
