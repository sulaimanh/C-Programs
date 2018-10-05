//  Program 4: KindredSpirits.c
//
//  KindredSpirits
//
//
#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

// - Completed
// - This helper function will count the amount of nodes.
int countNodes(node *root){
    return (root == NULL) ? 0 : 1 + countNodes(root->left) + countNodes(root->right);
}

// - Completed
int isReflection(node *a, node *b){
    // - If a and b are NULL, then we will return 1 and they are Kindred Spirits.
    // - If only one of them are NULL, then we will return 1 and they are not
    //      Kindred Spirits
	if (a == NULL && b == NULL)
		return 1;

	else if (a == NULL || b == NULL)
		return 0;

    // - If the data at a and b are not the same, then we will return 0 and they
    //      are not Kindred Spirits
	else if (a->data != b->data)
		return 0;

	return isReflection(a->left, b->right) || isReflection(a->right, b->left);
}

// - Completed
node *makeReflection(node *root){
    if (root == NULL)
        return NULL;

    node *tree = malloc(sizeof(node));
    if(tree == NULL)
        return NULL;
    tree->data = root->data;
    tree->left = tree->right = NULL;
    
    if (root->right != NULL)
        tree->left = makeReflection(root->right);

    if (root->left != NULL)
        tree->right = makeReflection(root->left);

    return tree;
}

// - Completed
// - In this function, we will traverse through the tree using preorder traversal.
void preOrder(node *root, int *preArray, int *index){
    if (root == NULL)
    return;
    
    preArray[(*index)++] = root->data;
    preOrder(root->left, preArray, index);
    preOrder(root->right, preArray, index);
    return;
}

// - Completed
// - In this function, we will traverse through the tree using postorder
//      traversal.
void postOrder(node *root, int *postArray, int *index){
    if(root == NULL)
    return;
    
    postOrder(root->left, postArray, index);
    postOrder(root->right, postArray, index);
    postArray[(*index)++] = root->data;
    return;
}

// - Completed
// - In this function, we will be comparing the pre and post order arrays, and
//      determine whether they are Kindred Spirits or not. We will return 0 if
//      they are the same and 1 if they are not
int comparePrePost(int *preArray, int *postArray, int counter){
    int i;
    
    for(i = 0; i < counter; i++){
        if(preArray[i] != postArray[i])
        return 0;
    }
    
    return 1;
}

// - Completed
int kindredSpirits(node *a, node *b){
    int sum1, sum2;
    int index;
    int counter;
    
    // - If both a and b are NULL, then we will return 1 and the trees are
    //      KindredSpirits.
    //   If only one of them are NULL, then we will return 0 and the trees are
    //      not Kindred Spirits.
    //   If the amount of nodes in a and b are not the same, then they are not
    //      Kindred Spirits, and we will return 0.
    if(a == NULL && b == NULL)
        return 1;
    else if(a == NULL || b == NULL)
        return 0;
    counter = countNodes(a);
    if(counter != countNodes(b))
        return 0;
    
    // - In postArray, I will store the numbers by traversing through the tree
    //      using postorder traversal
    int *postArray = malloc(sizeof(int) * counter);
    // - Check if malloc failed
    if(postArray == NULL)
        return 0;
    
    // - In preArray, I will store the numbers by traversing through the tree
    //      using preorder traversal
    int *preArray = malloc(sizeof(int) * counter);
    // - Check if malloc failed
    if(preArray == NULL)
        return 0;
    
    // - We will traverse node 'a' using preorder traversal and insert the element
    //      into the array "preArray".
    index = 0;
    preOrder(a, preArray, &index);
    
    // - We will traverse node 'b' using postorder traversal and insert the element
    //      into the array "postArray".
    index = 0;
    postOrder(b, postArray, &index);
    
    sum1 = comparePrePost(preArray, postArray, counter);

    // - We will traverse node 'b' using preorder traversal and insert the element
    //      into the array "preArray".
    index = 0;
    preOrder(b, preArray, &index);
    // - We will traverse node 'a' using preorder traversal and insert the element
    //      into the array "preArray".
    index = 0;
    postOrder(a, postArray, &index);
    
    sum2 = comparePrePost(preArray, postArray, counter);

    free(postArray);
    free(preArray);
    
    return (sum1 || sum2);
}

// - Completed
double difficultyRating(void){
    return 2.5;
}

// - Completed
double hoursSpent(void){
    return 6.5;
}
