//http://syllabus.cs.manchester.ac.uk/ugt/2017/COMP26120/lab/ex9.html

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

typedef struct node *tree_ptr;
struct node 
{
  Key_Type element; // only data is the key itself
  tree_ptr left, right;
  // add anything else that you need
  int depth; //height of node
};

struct table 
{
  tree_ptr head; // points to the head of the tree
  // add anything else that you need
  int depth;//heigh of node
  int num_nodes; //number of nodes
  int num_strcmp;//number of strcmp calls
};

/* function to malloc space for data structures, initialise fields to */
Table initialize_table(/*ignore parameter*/) 
{
  Table newtable = malloc(sizeof(struct table));
  if (newtable == NULL)
    fprintf(stderr, "Malloc error!\n");
  
  newtable -> head = NULL;
  newtable -> depth = 0;
  newtable -> num_nodes =0;
  newtable -> num_strcmp =0;
  
  return newtable;
}

/* function to allocates a new node with the given key and NULL left and right pointers */
tree_ptr new_node(Key_Type element){
  tree_ptr newnode = malloc(sizeof(*newnode));
  if (newnode == NULL)
    fprintf(stderr, "Malloc error!\n");
  
  newnode -> element = element; 
  newnode -> left = NULL;
  newnode -> right = NULL;
  newnode -> depth = 1;
  return newnode;
}
    
//function to update depth of tree
int maxDepth(tree_ptr current){
  
  if (current == NULL || (current -> left == NULL && current -> right == NULL))
    return 1;
  else if (current -> left == NULL)
    return current -> right -> depth + 1;
  else if (current -> right == NULL)
    return current -> left -> depth + 1;
  else if (current -> left -> depth > current -> right -> depth)
    return current -> depth = current -> left -> depth + 1;
  else
    return current -> depth = current -> right -> depth + 1;  
}

/* Mode "1", returns unbalanced tree. 
    Function to insert a new node with given key in BST and return new root of subtree */
tree_ptr insertnode1(Key_Type element, Table thistable, tree_ptr thistree){
  
  Key_Type element_copy = strdup(element);
  //if the tree is empty, return a new node
  // if tree is empty set element copy as root and copy into table 
  if (thistree == NULL){
    thistable -> num_nodes = thistable -> num_nodes + 1; // insert at the end
    return new_node(element_copy);
  }
    
  //Otherwise, recur down the tree. Equal keys are not allowed in BST
  if (strcmp(element_copy, thistree -> element) == 0)
    thistable->num_strcmp = thistable->num_strcmp+1; 
    return thistree;
  
  if(strcmp(element_copy, thistree->element) > 0){
    thistree-> right = insertnode1(element_copy, thistable, thistree->right);
  }
  
  else{
    thistree-> left = insertnode1(element_copy, thistable, thistree->left);
  }
  
  thistable -> num_nodes = thistable -> num_nodes + 1;
  thistable-> num_strcmp = thistable->num_strcmp+1;
  thistree-> depth = maxDepth(thistree);
  
  return thistree;
}

Table insert(Key_Type element,Table thistable){
  thistable->head = insertnode1(element, thistable, thistable->head);
  thistable->depth = thistable -> head -> depth;
  
  return thistable;
}

/* function to right rotate subtree */
tree_ptr rightRotate(tree_ptr y){
  tree_ptr x = y -> left;
  tree_ptr T2 = x -> right;
  
  x->right =y;
  y->left = T2;
  
  y->depth = maxDepth(y);
  x->depth = maxDepth(x);
  return x;
}

/* function to left rotate subtree */
tree_ptr leftRotate(tree_ptr x){
  tree_ptr y = x -> left;
  tree_ptr T2 = y -> right;
  
  y->left = x;
  x->right = T2;
  
  x->depth = maxDepth(x);
  y->depth = maxDepth(y);
  
  return y;
}

/* get height difference between left and right child of tree_ptr */
int get_heightdiff(tree_ptr thistree){
  
  if(thistree == NULL)
    return 0;
  else if(thistree->left == NULL)
    return 0-(thistree->right->depth);
  else if(thistree->right == NULL)
    return (thistree->left->depth);
  else
    return (thistree->left->depth) - (thistree->right->depth);
}

/* Mode 2, returns AVL tree. 
    Function to insert a new node with given key in BST and return new root of subtree */
tree_ptr insertnode2(Key_Type element, Table thistable, tree_ptr thistree){
  
  Key_Type element_copy = strdup(element);
  //if the tree is empty, return a new node
  if (thistree == NULL){
    thistable -> num_nodes = thistable -> num_nodes + 1;
    return new_node(element_copy);
  }
    
  //Otherwise, recur down the tree. Equal keys are not allowed in BST
  if (strcmp(element_copy, thistree -> element) == 0)
    thistable->num_strcmp = thistable->num_strcmp+1;
    return thistree;
  
  if(strcmp(element_copy, thistree->element) > 0){
    thistree-> right = insertnode2(element_copy, thistable, thistree->right);
  }
  
  else{
    thistree-> left = insertnode2(element_copy, thistable, thistree->left);
  }
  
  thistable -> num_nodes = thistable -> num_nodes + 1;
  thistable-> num_strcmp = thistable->num_strcmp+1;
  
  //Update height of tree 
  thistree-> depth = maxDepth(thistree);
  
  int heightdiff = get_heightdiff(thistree);
  
  //Left Left case
  if(heightdiff >1 && strcmp(element, thistree->left->element)<0)
    return rightRotate(thistree);
  //Right Right case
  if(heightdiff<-1 && strcmp(element, thistree->right->element)>0)
    return leftRotate(thistree);
  //Left Right case
  if(heightdiff >1 && strcmp(element, thistree->left->element)>0){
    thistree->left = leftRotate(thistree->left);
    return rightRotate(thistree);
  }
  //Right Left case
  if(heightdiff <-1 && strcmp(element, thistree->right->element)<0){
    thistree->right = rightRotate(thistree->right);
    return leftRotate(thistree);
  }
  
  return thistree;
}

Table insert2(Key_Type element,Table thistable){
  thistable->head = insertnode2(element, thistable, thistable->head);
  thistable->depth = thistable -> head -> depth;
  
  return thistable;
}

Boolean find_node(Key_Type element, tree_ptr thistree){
  if(thistree == NULL)
    return 0;
  else{
    if(strcmp(element, thistree->element)==0)
      return 1;
    else if(strcmp(element, thistree->element)>0)
      return find_node(element, thistree->right);
    else
      return find_node(element, thistree->left);
  }
}

Boolean find(Key_Type element, Table thistable){ 
  
  if(thistable->head == NULL)
    return 0;
  else
    return find_node(element, thistable->head);
}

Boolean find2(Key_Type element, Table thistable){ 
  
  if(thistable->head == NULL)
    return 0;
  else
    return find_node(element, thistable->head);
}

void print_node(tree_ptr thistree){
  
  if(thistree!=NULL){
    print_node(thistree->left);
    if(thistree->left !=NULL && thistree->right !=NULL)
      printf("%s\n", thistree->element);
    print_node(thistree->right);
  }
}

void print_table(Table thistable){
  
  if(thistable->head == NULL)
    return;
  
  print_node(thistable->head);
}

void print_stats(Table thistable){
  printf("The height of the tree is %d\n", thistable -> depth);
  printf("The total number of elements in the tree is %d\n", thistable->num_nodes);
  printf("The average number of strcmp calls per element is %.2f.\n", (float) thistable->num_strcmp/thistable->num_nodes);
}
