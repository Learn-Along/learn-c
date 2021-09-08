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
#define ERROR_LOG_FATAL(...) fprintf(stderr,  __VA_ARGS__); return NULL;
#define FREE_IF_DEFINED(ptr) if(ptr != NULL){free(ptr); ptr = NULL;}

#define HW_INDEX_ERROR 1
#define HW_MEM_ALLOC_ERROR 2

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
 * @brief Initialize the list with default values
 * 
 * @param records the list to be initialized
 */
void __initializeList(List *records);

/**
 * @brief Creates a new record on the heap
 * 
 * @param previous the previous record for this record
 * @param value the value of this record
 * @param next the next record after current record
 * @return _Record* 
 */
_Record* __createRecord(_Record* previous, char* value, _Record* next);

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
 * @brief converts the list to a string representation
 * 
 * @param records the doubly-linked list to be printed
 */
char* toString(List *records);

/**
 * @brief Create a Heap Allocated String object
 * 
 * @param str the sring to be copied to the heap
 * @param maxCharaters maximum number of characters the string must have
 * @return char*
 */
char* __createHeapAllocatedString(char* str, size_t maxCharaters);

/**
 * @brief Concatenates a string src to dest and returns dest, expanding its memory if there is need
 * 
 * @param dest the desitnation string whose pointer is to be returned
 * @param src the source string that is to be concatenated to the dest string
 * @param currentMaxStrLength the maximum number of characters already permissible in dest
 * @return char* 
 */
char* __concatString(char* dest, char* src, size_t currentMaxStrLength);

/**
 * @brief Quotes a given string with single quotes
 * 
 * @param str 
 * @return char* 
 */
char* __quoteHeapString(char* str);

#endif /* HELLO_WORLD_H */
