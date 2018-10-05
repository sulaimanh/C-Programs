//  COP 3502, Spring 2017
//  SmartArray.c
//  Programming Assignment #2: SmartArray
//
//  Created by Sulaiman Hamouda on 1/28/17.
//  Copyright © 2017 Sulaiman Hamouda. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SmartArray.h"
#include <math.h>

SmartArray *createSmartArray(int length);
SmartArray *destroySmartArray(SmartArray *smarty);
SmartArray *expandSmartArray(SmartArray *smarty, int length);
SmartArray *trimSmartArray(SmartArray *smarty);
char *put(SmartArray *smarty, char *str);
char *get(SmartArray *smarty, int index);
char *set(SmartArray *smarty, int index, char *str);
char *insertElement(SmartArray *smarty, int index, char *str);
int removeElement(SmartArray *smarty, int index);
int getSize(SmartArray *smarty);
void printSmartArray(SmartArray *smarty);
double difficultyRating(void);
double hoursSpent(void);


// - Completed
SmartArray *createSmartArray(int length){
    int i;
    
    // - We allocate the struct dynamically.
    SmartArray *smarty = malloc(sizeof(SmartArray *));
    
    // - Check whether malloc() was successful.
    if (smarty == NULL)
        return NULL;
        
    // - Set size equal to zero since there is nothing in the array
    smarty->size = 0;
    
    // - We will make space for smarty->array
    // - In this if - else statement, we will set the capacity to either 10 or
    //          'length'... Whichever is the larger value
    // - We will set every element in smarty->array to NULL
    if(length > DEFAULT_INIT_LEN){
        smarty->array = malloc(sizeof(char *) * length);
        smarty->capacity = length;
        for(i = 0; i < length; i++){
            smarty->array[i]=NULL;
        }
    }
    else{
        smarty->array = malloc(sizeof(char *) * DEFAULT_INIT_LEN);
        smarty->capacity = DEFAULT_INIT_LEN;
        for(i=0;i<DEFAULT_INIT_LEN;i++){
            smarty->array[i]=NULL;
        }
    }

    printf("-> Created new SmartArray of size %d.\n", smarty->capacity);
    
    return smarty;
}

// - Completed
SmartArray *destroySmartArray(SmartArray *smarty){
    int i;
    if(smarty == NULL)
        return NULL;
    
    // - Free the individual arrays that hold the strings
    // - Free the array that held the pointers to all those other arrays
    for (i = 0; i < smarty->size; i++)
        free(smarty->array[i]);
    free(smarty->array);
    free(smarty);
    
    return NULL;
}

// - Completed
SmartArray *expandSmartArray(SmartArray *smarty, int length){
    int i;
    char **newArray = malloc(sizeof(char *) * length);
    
    // - Check whether malloc() was successful.
    if (newArray == NULL)
        return NULL;
    
    if(length<=smarty->capacity || smarty == NULL)
        return smarty;
    
    for(i=0; i < smarty->capacity; i++)
        newArray[i] = smarty->array[i];
    
    // - This is the size that capacity will get .
    smarty->capacity = length;
    
    // - Initializing everything in newArray equal to NULL
    for(i = smarty->size ; i < smarty->capacity; i++)
        newArray[i] = NULL;
    
    // - Freeing the array
    free(smarty->array);
    
    // - Setting smarty->array equal to the address of newArray.
    smarty->array=newArray;
    
    printf("-> Expanded SmartArray to size %d.\n", smarty->capacity);
    
    return smarty;
}

// - Completed
SmartArray *trimSmartArray(SmartArray *smarty){
    int i;
    
    char **newArray = malloc(sizeof(char *) *smarty->size);
    
    // - Check whether malloc() was successful OR if smarty->array equals NULL
    if (newArray == NULL || smarty->array == NULL)
        return NULL;
    
    // - If capacity is equal to size, then I do not want to trim anything.
    //          Otherwise, make capacity equal to size.
    if(smarty->capacity == smarty->size)
        return smarty;
    else
        smarty->capacity = smarty->size;
    
    // - In this for loop, we will be copying the contents from smarty->array into
    //          newArray
    for(i = 0; i < smarty->size; i++)
        newArray[i] = smarty->array[i];
    
    // - Freeing smarty->array
    free(smarty->array);
    
    // - Setting smarty->array equal to the address of newArray
    smarty->array = newArray;
    
    printf("-> Trimmed SmartArray to size %d.\n", smarty->size);
    
    return smarty;
}

// - Completed
char *put(SmartArray *smarty, char *str){
    
    // - If smarty equals NULL, then we will return NULL.
    if(smarty == NULL)
        return NULL;
    // - If str equals NULL, then we will return NULL.
    if(str == NULL)
        return NULL;
    // - If capacity is equal to size, then we need to expand the array
    if(smarty->capacity == smarty->size){
        expandSmartArray(smarty, smarty->capacity * 2 + 1);
    }
    
    // - We are allocating space for str in order to put it into smarty.
    smarty->array[smarty->size] = malloc(sizeof(char) * (strlen(str)+1));
    
    // - Check whether malloc() was successful.
    if (smarty->array[smarty->size] == NULL)
        return NULL;
    
    // - Here, we are copying str into smarty.
    strcpy(smarty->array[smarty->size],str);
    
    // - After we put str into smarty, we need to increment size by one.
    smarty->size++;
    
    return smarty->array[smarty->size-1];
}

// - Completed
char *get(SmartArray *smarty, int index){
    if(smarty == NULL)
        return NULL;
    if(index >= smarty->capacity)
        return NULL;
    if(index<0)
        return NULL;
    
    return smarty->array[index];
}

// - Completed
char *set(SmartArray *smarty, int index, char *str){
    
    // - return NULL if any of the conditions below evaluate to true
    if(smarty->array[index] == NULL || str == NULL || smarty->array == NULL)
        return NULL;
    
    // - Here, we are freeing the string at position index
    free(smarty->array[index]);
    
    // - Here, we are allocating the proper amount of space to put the string str
    //           in it.
    smarty->array[index] = malloc(sizeof(char) * (strlen(str)+1));
    
    // - Check whether malloc() was successful.
    if (smarty->array[index] == NULL)
        return NULL;
    
    // - Here, we are copying str into position index
    strcpy(smarty->array[index], str);
    
    return smarty->array[index];
}

// - Completed
char *insertElement(SmartArray *smarty, int index, char *str){
    int i;

    if(str == NULL || smarty->array == NULL)
        return NULL;
    
    // - If the specified index is greater than the array's size, the element being
    //          inserted should be placed in the first empty position in the array
    if(index > smarty->size)
        index = smarty->size;
    
    // - If capacity is equal to size, then we need to expand the array
    if(smarty->capacity == smarty->size)
        expandSmartArray(smarty, smarty->capacity * 2 + 1);
    
    // - Any elements to the right of index are shifted one space to the right.
    // - In the for loop, we will be looping from size down to index. We will move
    //      each element to one space to the right.
    // - We will use malloc to create the appropriate amount of space to insert
    //      element at index i in index i+1
    if(smarty->array[index] != NULL){
        for(i = smarty->size-1; i >= index; i--)
            smarty->array[i+1] = smarty->array[i];
    }
    
    smarty->array[index] = malloc(sizeof(char) * (strlen(str)+1));
    
    // - Check whether malloc() was successful.
    if (smarty->array[index] == NULL)
        return NULL;
    
    // - Here, we will be copying str into smarty->array[index]
    strcpy(smarty->array[index], str);
    
    
    smarty->size++;
    
    return smarty->array[index];
}

// - Completed
int removeElement(SmartArray *smarty, int index){
    int i;
    
    if(smarty == NULL || index >= smarty->size)
        return 0;
    
    free(smarty->array[index]);
    for(i = index; i <= smarty->size ; i++){
        smarty->array[i] = smarty->array[i+1];
    }
    smarty->size--;
    
    return 1;
}

// - Completed
int getSize(SmartArray *smarty){
    if(smarty == NULL)
        return -1;
    
    return smarty->size;
}

// - Completed
void printSmartArray(SmartArray *smarty){
    int i;
    
    if(smarty == NULL || getSize(smarty) == 0){
        printf("(empty array)\n");
        return;
    }
    
    for(i = 0; i < smarty->size; i++){
        printf("%s\n" , smarty->array[i]);
    }
    
    return;
}

// - Completed
double difficultyRating(void){
    return 3;
}

// - Completed
double hoursSpent(void){
    return 6;
}
