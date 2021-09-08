#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hello_world.h"

__thread int globalErrorNumber;

void insertItem(List *records, char* value, int index){
    _Record newRecord;
    _Record* previousRecord = NULL;
    _Record* nextRecord = NULL;
    int noOfRecords = records->length;
    int lastIndex = noOfRecords - 1;

    if(index > lastIndex || index < 0){
        reportError(HW_INDEX_ERROR);
        return;
    }

    _Record* currentRecordPtr = records->data;
    int count = 0;
    int previousIndex = index - 1;
    while(currentRecordPtr != NULL && count <= index){
        _Record cachedRecord = *currentRecordPtr;

        // get and set the previous record
        if(count == previousIndex){
            previousRecord = currentRecordPtr;
            previousRecord->next = &newRecord;
        }

        // get and set the next record
        if(count == index){
            nextRecord = currentRecordPtr;
            nextRecord->previous = &newRecord;
        }

        currentRecordPtr = cachedRecord.next;
        count++;
    }

    // set up the new record    
    newRecord.next = nextRecord;
    newRecord.value = __createHeapAllocatedString(value, strlen(value) + 1);
    newRecord.previous = previousRecord;

    // reset the list
    if(index == 0){
        records->data = &newRecord;
    }
    records->length++;
}

void appendItem(List *records, char* value){
    int lastIndex = records->length - 1;
    _Record* previousRecord;
    _Record newRecord = {
        .next = NULL,
        .previous = NULL,
        .value = __createHeapAllocatedString(value, strlen(value) + 1),
    };

    _Record* currentRecordPtr = records->data;
    int count = 0;
    while(currentRecordPtr != NULL && count <= lastIndex){
        // get and set the previous record
        if(count == lastIndex){
            previousRecord = currentRecordPtr;
            previousRecord->next = &newRecord;
        }

        currentRecordPtr = currentRecordPtr->next;
        count++;
    }

    if(records->length == 0){
        records->data = &newRecord;
    }

    newRecord.previous = previousRecord;
    records->length++;
}

char* findItem(List *records, int index){
    _Record* item;
    _Record* firstItem = records->data;
    int lastIndex = records->length - 1;

    if(index > lastIndex || index < 0){
        reportError(HW_INDEX_ERROR);
        return NULL;
    }

    _Record* currentRecordPtr = records->data;
    for (int i = 0; i < index; i++)
    {
        currentRecordPtr = currentRecordPtr->next;
    }
    
    return currentRecordPtr->value;
}

void deleteItem(List *records, int index){
    _Record *previousItem = NULL;
    _Record *nextItem = NULL;
    _Record *item = NULL;
    int listLength = records->length;

    // ensure the memory is also freed
    if(listLength == 0 || index >= listLength || index < 0){
        reportError(HW_INDEX_ERROR);
        return;
    }

    _Record* currentRecordPtr = records->data;
    int count = 0;
    int previousIndex = index - 1;
    int nextIndex = index + 1;
    while ((count <= (index + 1)) && currentRecordPtr != NULL)
    {
        // get the item before this index
        if(count == previousIndex){
            previousItem = currentRecordPtr;
        }

        // get the item
        if(count == index){
            item = currentRecordPtr;
        }

        // get the item after the given index
        if(count == nextIndex){
            nextItem = currentRecordPtr;
        }

        currentRecordPtr = currentRecordPtr->next;
        count++;
    }
    
    // reset the previous item
    if(previousItem != NULL){
        previousItem->next = nextItem;
    }

    // reset the next item
    if(nextItem != NULL){
        nextItem->previous = previousItem;
    }

    // delete the current item
    if(item != NULL){
        free(item->value);
    }

    records->length--;
    
}

void freeList(List *records){
    _Record* currentRecordPtr = records->data;

    while(currentRecordPtr != NULL){
        FREE_IF_DEFINED(currentRecordPtr->value);
        currentRecordPtr = currentRecordPtr->next;
    }
}

char* toString(List *records){
    int lastIndex = records->length - 1;
    size_t maxBufferStrLength = 300;
    char* bufferStr = __createHeapAllocatedString("{", maxBufferStrLength);
    if(bufferStr == NULL){
        ERROR_LOG_FATAL("toString: Memory allocation failure adding '}': %s\n", bufferStr);              
    }

    _Record* currentRecordPtr = records->data;
    int count = 0;
    char* separator = ", ";
    size_t charsInSeparator = strlen(separator);

    while (currentRecordPtr != NULL)
    {
        size_t currentValueLength = strlen(currentRecordPtr->value);
        size_t bufferStrLength = strlen(bufferStr);
        char* value = __createHeapAllocatedString(currentRecordPtr->value, currentValueLength);
        if(value == NULL){
            ERROR_LOG_FATAL("toString: Memory allocation failure for value: %s\n", value);              
        }

        // add separator
        if(count < lastIndex){
            value = __concatString(value, ", ", currentValueLength);
            if(value == NULL){
                ERROR_LOG_FATAL("toString: Memory allocation failure for value + separator: '%s'\n", bufferStr); 
            }

            currentValueLength += 2;
        }  

        bufferStr = __concatString(bufferStr, value, maxBufferStrLength);
        if(bufferStr == NULL){
            ERROR_LOG_FATAL("toString: Memory allocation failure for buffer: '%s'\n", bufferStr); 
        }

        size_t newBufferStrLength = bufferStrLength + currentValueLength;
        maxBufferStrLength = maxBufferStrLength > newBufferStrLength? maxBufferStrLength: newBufferStrLength;

        currentRecordPtr = currentRecordPtr->next;
        count++;
    }
      
    strcat(bufferStr, "}");
    bufferStr = __concatString(bufferStr, "}", maxBufferStrLength);
    if(bufferStr == NULL){
        ERROR_LOG_FATAL("toString: Memory allocation failure adding '}': '%s'\n", bufferStr); 
    }

    return bufferStr;
}

char* __createHeapAllocatedString(char * str, size_t maxCharaters){
    size_t strLength = strlen(str);
    size_t maxStrLength = strLength > maxCharaters? strLength: maxCharaters;
    // +1 accounts for the \0 terminator of the string
    size_t maxBytes = (maxStrLength * sizeof(char)) + 1;
    char *string = (char*) malloc(maxBytes);

    if(string == NULL){
        reportError(HW_MEM_ALLOC_ERROR);
        return NULL;
    }

    return strcpy(string, str);
}

char* __concatString(char* dest, char* src, size_t currentMaxStrLength){
    size_t newStrLength = strlen(dest) + strlen(src);

    if(newStrLength > currentMaxStrLength){
        dest = (char*) realloc(dest, newStrLength);
    }

    if(dest == NULL){
        reportError(HW_MEM_ALLOC_ERROR);
        return NULL; 
    }

    return strcat(dest, src);
}

