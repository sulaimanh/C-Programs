//  COP 3502, Spring 2017
//  Varg.c
//  Programming Assignment #1: Varg
//


#include <stdio.h>
#include <stdarg.h>
#include "Varg.h"


// - This function takes a single non-negative integer, n,
//      followed by a list of exactly n lowercase,
//      alphabetic characters
// - RESTRICTION: You are not allowed to store any of the
//      input arguments. You are only allowed to
//      read through them once.
// - Return the most frequently occurring character in the
//      list.
char mostFrequentChar(int n, ...);

// - This function takes as its input a list of characters.
//      The function is guaranteed to receive at least
//      one argument. The last argument passed to the
//      function will always be the ‘\0’ character. All
//      other characters in the list will be lowercase,
//      alphabetic characters
// - RESTRICTION: Same restriction as mostFrequentChar
//      method
// - Return the most frequently occurring character in the
//      list.
char fancyMostFrequentChar(char c, ...);

// - This will be returning the rate of difficulty of this
//      assignment
double difficultyRating(void);

// - This will be returning the amount of hours I spent on
//      this assignment
double hoursSpent(void);


char mostFrequentChar(int n, ...){
    
    int p, freq[26], count = 0, i, j;
    char letter = '\0';
    
    // - Set every space in the freq array equal to 0
    for(i = 0; i < 26; i++){
        freq[i]=0;
    }
    
    // - argu is going to hold the list of arguments to
    //      this function
    va_list argu;
    
    // - Now, argu will be initialized. Starts with the
    //      first variable (int n) passed to this function
    va_start(argu,n);
    
    // - If the first variable (n) equals 0, then the null
    //      character will be returned
    if(n == 0){
        return '\0';
    }
    
    // - In this for loop, we go through the number of
    //    characters which are passed to this function (n).
    // - As the for loop traverses, the number of times
    //      each letter occurs is being recorded into the
    //      freq array.
    // - In the if statement, we will determine which
    //      letter occurs the most.
    // - In the variable 'count', we will store the number
    //      of times the most frequent letter occurred.
    // - In the variable 'letter', we will store the most
    //      occurred letter
    for(j = 0; j < n; j++){
        p = va_arg(argu,int);
        freq[p-'a']++;
        
        if(freq[p-'a'] > count){
            count = freq[p-'a'];
            letter = p;
        }
    }
    
    // - This frees up any lingering memory associated with
    //      the argp variable and helps ensure that we
    //      don't have any memory leaks emanating from this
    //      function.
    va_end(argu);
    
    // - We will now return the most frequently occurred
    //      letter
    return letter;
}


char fancyMostFrequentChar(char c, ...){
    
    char p, letter = c;
    int i, count=0, freq[26];
    
    // - argu is going to hold the list of arguments to
    //      this function
    va_list argu;
    
    // - Now, argu will be initialized. Starts with the
    //      first variable (char c)
    va_start(argu,c);
    
    // - Set every space in the freq array equal to 0
    for(i = 0; i < 26; i++){
        freq[i] = 0;
    }

    // - if the first arguement passed is the null
    //      character, then that will be returned ('\0').
    if(c == '\0'){
        return '\0';
    }
    else{
        count = freq[c-'a']+1;
        freq[c-'a']++;
    }
    
    // - In the while loop, we keep getting letters from
    //      the arg list until we see a '\0'.
    // - In the if statement, we will determine which
    //      letter occurs the most.
    // - In the variable 'count', we will store the number
    //      of times the most frequent letter occurred.
    // - In the variable 'letter', we will store the most
    //      occurred letter
    while((p = va_arg(argu, int)) != '\0'){
        freq[p-'a']++;
        
        if(freq[p-'a'] > count){
            count = freq[p-'a'];
            letter = p;
        }
    }
    
    
    // - This frees up any lingering memory associated with
    //      the argp variable and helps ensure that we
    //      don't have any memory leaks emanating from this
    //      function.
    va_end(argu);
    
    // - It will now return the most frequently occurred
    //      letter
    return letter;
}

double difficultyRating(void){
    return 2.5;
}

double hoursSpent(void){
    return 5;
}
