#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

// the configured options and settings for hello world
#define helloworld_VERSION_MAJOR @helloworld_VERSION_MAJOR@
#define helloworld_VERSION_MINOR @helloworld_VERSION_MINOR@
#define helloworld_VERSION_PATCH @helloworld_VERSION_PATCH@

typedef struct
{
    long next;
    char* value;
    long previous;
} Record;

typedef struct {
    Record *data;
    int length;
} List;

/**
 * @brief Inserts the given record at the end of the list of strings
 * 
 * @param records 
 * @param newRecord 
 * @param maxCharaters 
 */
void insertItem(List *records, char* newRecord, int maxCharaters);

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
 * @brief prints the linked list
 * 
 * @param records 
 */
void printList(List *records);

/**
 * @brief Create a Heap Allocated String object
 * 
 * @param str 
 * @param maxCharaters 
 * @return char* 
 */
char* createHeapAllocatedString(char * str, int maxCharaters);

#endif /* HELLO_WORLD_H */
