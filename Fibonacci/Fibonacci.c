//  Program 3: Fibonacci.c
//
//  Fibonacci
//
//  Created by Sulaiman Hamouda on 2/27/17.
//

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "Fibonacci.h"


// - HELPER FUNCTION: This function will create and return a HugeInteger. I
//      created this, because I do not want to have to keep using malloc
//      throughout my whole program.
HugeInteger *hugeCreate (int length){
    int i;
    HugeInteger *retval = malloc(sizeof(HugeInteger));
    
    if (retval == NULL)
        return NULL;
    
    retval-> digits = malloc(sizeof(int) * length);
    if(retval->digits == NULL){
        free(retval);
        return NULL;
    }
    
    for (i = 0; i < length; i++)
        retval->digits[i] = 0;
    
    retval->length = length;
    
    return retval;
}

// - Completed
HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q){
    int sum, carryOver;
    int i, x;
    HugeInteger *newPointer;
    
    // - If p or q is NULL, then we will return NULL
    if(p == NULL || q == NULL)
        return NULL;
    
    // - Here, we are going to set x equal to the largest length
    x = p->length+1;
    if(p->length < q->length)
        x = q->length+1;
    
    // - Going to hugeCreate, to create a HugeInteger of size x
    newPointer = hugeCreate(x);
    
    // - In this for loop, we will be adding the numbers together.
    carryOver = 0;
    for(i = 0; i < newPointer->length; i++){
        
        if(i < p->length){
            if(i < q->length)
                sum = p->digits[i] + q->digits[i] + carryOver;
            else
                sum = p->digits[i] + carryOver;
        }
        else if(i < q->length)
            sum = q->digits[i] + carryOver;
        else
            sum = carryOver;
        newPointer->digits[i] = sum % 10;
        carryOver = sum / 10;
    }
    
    // - In this if statement, we are checking whether the last element in the
    //      array is a zero, if it is, then we will trim the size to one less.
    if(newPointer->digits[newPointer->length-1] == 0)
        newPointer->length = newPointer->length - 1;
    
    return newPointer;
}


// - Completed
HugeInteger *hugeDestroyer(HugeInteger *p){
    // - Return NULL if p is NULL
    if(p == NULL)
        return NULL;
    
    // - First, we need to free the array in the HugeInteger Struct, then we free
    //          the pointer p.
    free(p->digits);
    free(p);

    return NULL;
}


// - Completed
HugeInteger *parseString(char *str){
    HugeInteger *newPointer;
    int i;
    
    // - Return NULL if str is NULL
    if(str == NULL)
        return NULL;
    
    // - If str equals '\0', then we will set digits and length and return.
    if(str[0] == '\0'){
        newPointer = hugeCreate(1);
        newPointer->digits[0] = 0;
        return newPointer;
    }
    
    // - Going to hugeCreate, to create a HugeInteger
    newPointer = hugeCreate(strlen(str));
    
    // - In this for loop, we are converting the number from string format, to
    //         to HugeInteger format.
    for(i = 0; i < newPointer->length; i++)
        newPointer->digits[newPointer->length-1-i] = str[i] - '0';
    
    return newPointer;
}

// - Completed
HugeInteger *parseInt(unsigned int n){
    int i;
    unsigned int copyN = n;
    int length = 0;
    
    HugeInteger *newPointer;
    
    if(n == 0){
        newPointer = hugeCreate(1);
        newPointer->digits[0] = 0;
        return newPointer;
    }
    
    // - In this while loop, we are calculating how many digits are in the number
    //      n. We copied n into copyN
    while(copyN != 0){
        length++;
        copyN/=10;
    }
    
    // - Going to hugeCreate, to create a HugeInteger
    newPointer = hugeCreate(length);
    
    // - Here, we will be inserting each number to its right index.
    for(i = 0; i < newPointer->length; i++){
        newPointer->digits[i] = (n % 10);
        n/=10;
    }
    
    return newPointer;
}


// - Completed
unsigned int *toUnsignedInt(HugeInteger *p){
    unsigned int i, num = 0, power = 1;
    unsigned int *newUnsignedInt;
    
    if(p == NULL)
        return NULL;
    
    // - Here, we are dynamically allocating space for an unsigned int.
    newUnsignedInt = malloc(sizeof(unsigned int));
    
    // - Check whether malloc failed
    if(newUnsignedInt == NULL)
        return NULL;

    // - Here, we are converting the integer represented by p to an unsigned int.
    *newUnsignedInt = 0;
    for(i = 0; i < p->length; i++){
        num = p->digits[i] * power;
        power = power * 10;
        
        if((UINT_MAX - *newUnsignedInt) < num){
            free(newUnsignedInt);
            return NULL;
        }
        else
            *newUnsignedInt = *newUnsignedInt + num;
    }
    
    return newUnsignedInt;
}

// - Completed
HugeInteger *fib(int n){
    int i;
    HugeInteger *array[3];
    HugeInteger *pointer;
    
    // - if n were 1, we would allocate an array of length 1, and then the
    //      array[1] = 1 line would be writing off the end of our array. So,
    //      we need to have this if statement.
    if(n < 2){
        pointer = hugeCreate(1);
        pointer->digits[0] = n;
        return pointer;
    }
    
    // Set the base cases / initial conditions.
    array[0] = hugeCreate(1);
    array[0]->digits[0] = 0;
    array[1] = hugeCreate(1);
    array[1]->digits[0] = 1;
    
    // Now build up the rest of the Fibonacci sequence through F(n).
    for (i = 2; i <= n; i++){
        array[2] = hugeAdd(array[0],array[1]);
        array[0] = array[1];
        array[1] = array[2];
    }
    
    return array[2];
}

// - Completed
double difficultyRating(void){
    return 2.0;
}

// - Completed
double hoursSpent(void){
    return 8.0;
}
