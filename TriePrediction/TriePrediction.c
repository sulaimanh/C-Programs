//  TriePrediction.c
//  Programming Assignment #5: TriePrediction
//
//  Created by Sulaiman Hamouda on 4/11/17.
//  Copyright © 2017 Sulaiman Hamouda. All rights reserved.
//

#include <stdio.h>
#include "TriePrediction.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// - I did not write this function. Taken from notes.
// Helper function called by printTrie()
void printTrieHelper(TrieNode *root, char *buffer, int k)
{
    int i;
    
    if (root == NULL)
        return;
    
    if (root->count > 0)
        printf("%s (%d)\n", buffer, root->count);
    
    buffer[k + 1] = '\0';
    
    for (i = 0; i < 26; i++)
    {
        buffer[k] = 'a' + i;
        
        printTrieHelper(root->children[i], buffer, k + 1);
    }
    
    buffer[k] = '\0';
}

// - I did not write this function. Taken from notes.
// If printing a subtrie, the second parameter should be 1; otherwise, if
// printing the main trie, the second parameter should be 0.
void printTrie(TrieNode *root, int useSubtrieFormatting)
{
    char buffer[1026];
    
    if (useSubtrieFormatting)
    {
        strcpy(buffer, "- ");
        printTrieHelper(root, buffer, 2);
    }
    else
    {
        strcpy(buffer, "");
        printTrieHelper(root, buffer, 0);
    }
}

// - Completed
// - Suggested Method
TrieNode *createTrieNode(){
    int i;
    TrieNode *trie = malloc(sizeof(TrieNode));
    
    // - Need to set count to 0
    trie->count = 0;
    // - Need to sent subtrie to NULL
    trie->subtrie = NULL;
    
    // - Need to set every child to NULL
    for (i = 0; i < 26; i++){
        trie->children[i] = NULL;
    }
    
    return trie;
}

// - Completed
// - Suggested method.
char *stripPunctuators(char *str){
    int length = strlen(str);
    char buffer[MAX_CHARACTERS_PER_WORD + 1];
    int i, j;
    
    // - Here, we will go through the entire string and store only characters
    //      which are alphabets.
    j = 0;
    for(i = 0; i < length; i++){
        if(isalpha(str[i])){
            buffer[j] = tolower(str[i]);
            j++;
        }
    }
    // - Need to set the NULL character
    buffer[j] = '\0';
    
    // - Copy buffer into str.
    strcpy(str, buffer);
    
    return str;
}

// - Completed
// - I took this function from the class notes.
// - Suggested method
TrieNode *insertString(TrieNode *root, char *str){
    int i, index, len = strlen(str);
    TrieNode *temp;
    
    if (root == NULL)
        root = createTrieNode();
    
    // temp starts at the root node and spells
    // out the string being inserted as he/she jumps from node to node. (The
    // temp is acting as a temp pointer.)
    temp = root;
    
    for (i = 0; i < len; i++)
    {
        index = tolower(str[i]) - 'a';
        
        // Before the temp can move forward to the next node, (s)he needs to
        // make sure that node actually exists. If not, create it!
        if (temp->children[index] == NULL)
            temp->children[index] = createTrieNode();
        
        // Now the temp is able to jump forward.
        temp = temp->children[index];
    }
    
    // When we break out of the for-loop, the temp should be at the terminal
    // node that represents the string we're trying to insert.
    temp->count++;
    
    return root;
}



// - Completed
// - Helper Functions: createTrieNode(), insertString() and stripPunctuators()
TrieNode *buildTrie(char *filename){
    TrieNode *root;
    TrieNode *temp;
    int size;
    char buffer1[MAX_CHARACTERS_PER_WORD + 1], buffer2[MAX_CHARACTERS_PER_WORD + 1];
    
    FILE *ifp;
    
    if ((ifp = fopen(filename, "r")) == NULL){
        fprintf(stderr, "Failed to open \"%s\" in buildTrie().\n", filename);
        return NULL;
    }
    // - We will first scan in the first word into buffer1.
    fscanf(ifp, "%s", buffer1);
    
    // - buffer2 will hold the previous word
    strcpy(buffer2,buffer1);

    // - Here, we will create the trie node
    root = createTrieNode();
    
    // - We will strip the punctuation
    strcpy(buffer1,stripPunctuators(buffer1));
    
    // - We will now insert buffer1 into the trie
    root = insertString(root, buffer1);
    
    // - In this while loop, we will take care of inserting into our trie and
    //      subtrie
    while(fscanf(ifp, "%s", buffer1) != EOF){
        
        temp = root;
        
        size = strlen(buffer2);
        // - In this if statement, we are going to check for punctation at the
        //      end of the sentence
        if(buffer2[size - 1] != '!' && buffer2[size-1] != '?' && buffer2[size-1] != '.'){
            
            // - Going to the last node within root in order to insert buffer1
            //      into subtrie of buffer2
            temp = getNode(temp, buffer2);
            strcpy(buffer2, buffer1);
            strcpy(buffer2, stripPunctuators(buffer2));
            // - We will now enter buffer1 into the subtrie
            temp->subtrie = insertString(temp->subtrie, buffer2);

        }
        
        // - We will copy buffer1 into buffer2
        strcpy(buffer2, buffer1);
        
        // - Stripping the punctuation from buffer1 in order to insert it into
        //      the trie
        strcpy(buffer1,stripPunctuators(buffer1));
        // - Inserting buffer1 into root
        root = insertString(root, buffer1);
        
    }
    
    fclose(ifp);
    
    return root;
}

// - Completed
TrieNode *destroyTrie(TrieNode *root){
    int i;
    
    // This for loop will run 26 times for each non-Null children TrieNode
    for(i = 0; i < 26; i++){
        // - If root->children[i] does not equal null, then we will
        //      recursively call destroyTrie, and pass root->child[i]
        //      in order to check whether that trie node has any non-Null
        //      child TrieNodes. We will continue doing this for every
        //      single TrieNode. It will go all the way to the last child
        //      TrieNode and it will start to free each TrieNode backwards.
        if (root->children[i] != NULL)
            destroyTrie(root->children[i]);
    }
    // - Here, we will free every subtrie TrieNode
    if (root->subtrie != NULL)
        destroyTrie(root->subtrie);
    
    free(root);
    
    return NULL;
}

// - Completed
// - Helper Functions: stripPunctuators()
TrieNode *getNode(TrieNode *root, char *str){
    int i, j, length;
    char buffer[MAX_CHARACTERS_PER_WORD+1];
    TrieNode *temp;
    
    // - If root or str is NULL, we will return NULL
    if(root == NULL || str == NULL)
        return NULL;
    
    temp = root;
    // - We will first copy str into buffer
    strcpy(buffer,str);
    // - We will now strip any punctation and store it back into buffer.
    strcpy(buffer, stripPunctuators(buffer));
    length = strlen(buffer);
    
    
    // - In this for loop we will be looking for
    for(i = 0; i < length; i++){
        if(temp->children[buffer[i] - 'a'] != NULL){
            temp = temp->children[buffer[i] - 'a'];
        }
        else
            return NULL;
    }
    
    // - If count equals 0, then we will return NULL.
    if(temp->count == 0)
        return NULL;
    
    return temp;
}

// - Completed
// - Helper function
void mostFrequentHelper(TrieNode *root, char *buffer, int j, int *counter, char *str){

    int i;
    
    // - Base case
    if (root == NULL)
        return;
    
    // - If root->count is greater than counter, then we will set counter equal
    //      to root->count.
    // - We will also copy buffer into str.
    if (root->count > *counter){
        *counter = root->count;
        strcpy(str, buffer);
    }
    
    // - Need to set the NULL character
    buffer[j + 1] = '\0';
    
    // - Here, we will recursively call mostFrequentHelper within this for
    //      loop in order to go through the whole trie.
    for (i = 0; i < 26; i++){
        buffer[j] = i + 'a';
        mostFrequentHelper(root->children[i], buffer, j + 1, counter, str);
    }
    
    // - Need to set the NULL character
    buffer[j] = '\0';
    
    return;
}

// - Completed
// // - Helper Functions: mostFrequentHelper()
void getMostFrequentWord(TrieNode *root, char *str){

    int counter, j;
    char buffer[MAX_CHARACTERS_PER_WORD + 1];
    
    // - If root is NULL, then I will copy the empty string into str and return.
    if(root == NULL){
        strcpy(str, "");
        return;
    }
    
    if(str != ""){
        strcpy(str,"");
    }
    
    counter = 0;
    j = 0;
    // - We are now going to go to mostFrequentHelper in order to find the most
    //      frequent word in the trie.
    mostFrequentHelper(root, buffer, j, &counter, str);
    
    // - Here, we will check if counter equals 0. If true, then str will be
    //      equal to the empty string.
    if (counter == 0)
        strcpy(str, "");
    
    
    return;
}

// - Completed
// - Helper Functions: stripPunctuators()
int containsWord(TrieNode *root, char *str){
    int i, length;
    char buffer[MAX_CHARACTERS_PER_WORD + 1];
    int *strInt;
    
    if(root == NULL || str == NULL)
        return 0;
    
    // - We will first copy str into buffer
    strcpy(buffer,str);
    // - We will now strip any punctation and store it back into buffer.
    strcpy(buffer,stripPunctuators(buffer));

    length = strlen(buffer);
    
    // - In this for loop, I will check if the trie contains str.
    for(i = 0; i < length; i++){
        if(root->children[buffer[i]-'a'] != NULL){
            root = root->children[buffer[i]-'a'];
        }
        else{
            return 0;
        }
    }
    // - If count equals 0, then we will return NULL.
    if(root->count == 0)
        return 0;

    return 1;
}

// - Completed
// - Helper function for prefixCount
int prefixCounterHelper(TrieNode *root){
    int sum, i;
    
    // - If root equals NULL, we will return 0
    // - Base case
    if(root == NULL)
        return 0;
    
    // - In this for loop, we will keep count of the amount of strings
    sum = 0;
    // - We will keep track of the count
    sum += root->count;
    for(i = 0; i < 26; i++){
        if (root->children[i] != NULL)
            sum += prefixCounterHelper(root->children[i]);
    }
    return sum;
    
}

// - Completed
// - Helper function for prefixCount
int prefixEmptyString(TrieNode *root){
    int i, sum;
    
    // - Base case
    if (root == NULL)
        return 0;
    
    // - If root->count is greater than 0, then we will add it to sum.
    sum = 0;
    if (root->count > 0)
        sum += root->count;
    
    // - Here, we will be counting how many words are in the trie
    for (i = 0; i < 26; i++)
    {
        if(root->children[i] != NULL)
            sum += prefixEmptyString(root->children[i]);
    }

    return sum;
}

// - Completed
// - Helper Functions: stripPunctuators(), prefixEmptyString() and
//                      prefixCounterHelper
int prefixCount(TrieNode *root, char *str){
    TrieNode *temp;
    int length, i, currIndex, sum;
    
    // - If root is NULL, then we will return 0
    if(root == NULL)
        return 0;
    // - If str is NULL, then we will return 0
    if(str == NULL)
        return 0;
    
    // - Setting temp equal to root, inorder to not change the root.
    temp = root;
    
    // - If str is equal to the empty string, then we will go into another
    //      function and count how many words are in the trie.
    if(strcmp(str,"") == 0){
        return prefixEmptyString(temp);
    }
    
    // - In this for loop, we will go to the last node str[i] - 'a'
    length = strlen(str);
    for(i = 0; i < length; i++){
        currIndex = tolower(str[i]) - 'a';
        if(temp->children[currIndex] != NULL)
            temp = temp->children[currIndex];
        else
            return 0;
    }
    // - Here, we will go to another method and pass in temp.
    sum = prefixCounterHelper(temp);
    
    return sum;
    
}

// - Completed
double difficultyRating(void){
    return 4.0;
}

// - Completed
double hoursSpent(void){
    return 13.0;
}


int main(int argc, char **argv) {
   
    char buffer[MAX_CHARACTERS_PER_WORD + 1];
    int n, i;
    TrieNode *root, *temp;
    FILE *ifp;
    
    if(argc < 3)
    {
        fprintf(stderr, "Proper syntax: %s <corpus file> <input file> \n", argv[0]);
        return 0;
    }
    
    // - We will build a trie.
    root = buildTrie(argv[1]);
    
    if ((ifp = fopen(argv[2], "r")) == NULL)
    {
        fprintf(stderr, "Failed to open \"%s\" in buildTrie().\n", argv[2]);
        return 1;
    }
    
    // - Here, we will check what is passed in the corpus file.
    while (fscanf(ifp, "%s", buffer) != EOF) {
        temp = root;
        // - If buffer is equal to "!" then we will print the trie.
        if(strcmp(buffer, "!") == 0){
            printTrie(temp,0);
        }
        // - This is the text prediction command
        else if(strcmp(buffer, "@") == 0){
            fscanf(ifp, "%s", buffer);
            fscanf(ifp, "%d", &n);
            
            // - Here, we will print buffer
            printf("%s", buffer);
            
            // - In this for loop, we will call getMostFrequentWord in order
            //      to find the most frequent subtrie.
            for(i=0; i < n; i++){
                
                temp = getNode(root, buffer);
                
                // - If temp is equal to NULL, we will break out the for loop.
                if(temp == NULL)
                    break;
                // - If temp->subtrie is equal to NULL, we will break out the
                //      for loop.
                if(temp->subtrie == NULL)
                    break;
                
                getMostFrequentWord(temp->subtrie, buffer);
                
                // - Here, we will print out buffer. This will also take care
                //      of any leading white space as well.
                printf(" %s", buffer);
            }
            
            printf("\n");
            
        
            
        }
        // - If buffer is in the trie, I will print the string, followed
        //      by a printout of its subtrie contents
        else{
            // - Here, we will check if buffer is in the trie.
            temp = getNode(temp, buffer);
            // - If temp does not equal NULL, then we will print the string and
            //      check if it has a subtrie
            if(temp != NULL){
                printf("%s\n",buffer);
                
                // - If temp->subtrie equals NULL, then we will print out
                //      "(EMPTY)". Otherwise, we will print out the subtrie.
                if(temp->subtrie == NULL)
                    printf("(EMPTY)\n");
                else
                    printTrie(temp->subtrie, 1);
            }
            else{
                printf("%s\n",buffer);
                printf("(INVALID STRING)\n");
            }
        }
    }
    
    // - Need to destroy root.
    destroyTrie(root);
    // - Need to close the file pointer.
    fclose(ifp);

    return 0;
}
