#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Record
{
    long next;
    char* value;
    long previous;
};

struct List {
    struct Record *data;
    int length;
};

/**
 * @brief Inserts the given record at the end of the list of strings
 * 
 * @param records 
 * @param newRecord 
 * @param maxCharaters 
 */
void insertItem(struct List *records, char* newRecord, int maxCharaters);

/**
 * @brief finds the value at the given index and returns it
 * 
 * @param records 
 * @param index 
 * @return char* 
 */
char* findItem(struct List *records, int index);

/**
 * @brief deletes the item at the given index in records
 * 
 * @param records 
 * @param index 
 */
void deleteItem(struct List *records, int index);

/**
 * @brief prints the linked list
 * 
 * @param records 
 */
void printList(struct List *records);

/**
 * @brief Create a Heap Allocated String object
 * 
 * @param str 
 * @param maxCharaters 
 * @return char* 
 */
char* createHeapAllocatedString(char * str, int maxCharaters);


/**
 * @brief The main function
 * 
 * @return int 
 */
int main(){
    printf("hello world");
    struct List data;
    int maxSize = 20;
    char *strings[20] = {"Hello World", "Hi World", "Bonjour Monde"};
    int noOfStrings = 3;

    for(int i = 0; i < noOfStrings; i++){
        insertItem(&data, *(strings+i), maxSize);
    }

    printf("the linked list: \n");
    printList(&data);

    for(int i=0; i < noOfStrings; i++){
        printf("Item at %d is %s", i, findItem(&data, i));
    }

    for(int i=0; i < noOfStrings; i++){
        deleteItem(&data, i);
        printf("the linked list after deleting index %d: \n", i);
        printList(&data);
    }    

    return 0;
}

void insertItem(struct List *records, char* newRecord, int maxCharaters){
    struct Record last;
    // last.next = (int) NULL;
    last.value = createHeapAllocatedString(newRecord, maxCharaters);
    // last.previous = (int) NULL;

    if(records->length > 0){
        int lastIndex = records->length - 1;
        last.previous = (long)(records->data) + lastIndex;
    }

    records->length++;
}

char* findItem(struct List *records, int index){
    return (records->data + index)->value;
}

void deleteItem(struct List *records, int index){
    if(records->length == 0 || index >= records->length){
        fprintf(stderr, "index %d is out of range", index);
    } else {
        struct Record *item = (records->data) + index;
        struct Record *previousItem;
        struct Record *nextItem;

        if(index > 0){
            previousItem = records->data + (index - 1);
        }

        if(index < (records->length - 1)){
            nextItem = records->data + (index + 1);
        }

        if(previousItem != NULL){
            previousItem->next = (long) nextItem;
        }

        if(nextItem != NULL){
            nextItem->previous = (long) previousItem;
        }

        records->length--;
    }
}

void printList(struct List *records){
    int lastIndex = records->length - 1;

    printf("{");

    for(int i = 0; i <= lastIndex; i++){
        printf("%s", (records->data + i)->value);
        if(i < lastIndex){
            printf(", ");
        }
    }

    printf("}");
}

char* createHeapAllocatedString(char * str, int maxCharaters){
    char *string = malloc(maxCharaters * sizeof(char));

    if(string == NULL){
        fprintf(stderr, "failed to allocate required memeory\n");
    } else {
        strcpy(string, str);
    }

    return string;
}