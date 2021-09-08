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
    char* strings[] = {"Hello World", "Hi World", "Bonjour Monde"};
    int noOfStrings = sizeof(strings) / sizeof(char*);

    for(int i = 0; i < noOfStrings; i++){
        appendItem(&data, strings[i]);
    }

    printf("the linked list: \n \"%s\"\n", toString(&data));

    for(int i=0; i < noOfStrings; i++){
        printf("Item at %d is '%s'\n", i, findItem(&data, i));
    }

    for(int i=noOfStrings - 1; i >= 0; i--){
        deleteItem(&data, i);
        printf("the linked list after deleting index %d: \n\"%s\"\n", i, toString(&data));
    }

    return 0;
}