#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hello_world.h"

void insertItem(List *records, char* newRecord, int maxCharaters){
    Record last;
    // last.next = (int) NULL;
    last.value = createHeapAllocatedString(newRecord, maxCharaters);
    // last.previous = (int) NULL;

    if(records->length > 0){
        int lastIndex = records->length - 1;
        last.previous = (long)(records->data) + lastIndex;
    }

    records->length++;
}

char* findItem(List *records, int index){
    return (records->data + index)->value;
}

void deleteItem(List *records, int index){
    if(records->length == 0 || index >= records->length){
        fprintf(stderr, "index %d is out of range", index);
    } else {
        Record *item = (records->data) + index;
        Record *previousItem;
        Record *nextItem;

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

void printList(List *records, FILE* stream){
    int lastIndex = records->length - 1;
    
    if(stream == NULL){
        stream = stdin;
    }

    fprintf(stream, "{");

    for(int i = 0; i <= lastIndex; i++){
        fprintf(stream,"%s", (records->data + i)->value);
        if(i < lastIndex){
            fprintf(stream, ", ");
        }
    }

    fprintf(stream, "}");
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