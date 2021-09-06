#include <stdlib.h>
#include <stdio.h>
#include "hello_world.h"

/**
 * @brief The main function
 * 
 * @return int 
 */
int main(){
    List data;
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