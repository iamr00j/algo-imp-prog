#include "graph.h"
#include <limits.h>

typedef struct heap_node *heap_ptr;

struct heap_node{
    int index;
    int distance; //distance from source
};

typedef struct{
    int size; //size of heap
    heap_ptr *array; //binary tree in an array form
    int *position; //position of node in the array
} Heap;

//function to create a new node
heap_ptr newNode(int index, int distance){
    
    heap_ptr newnode = (heap_ptr) malloc(sizeof(heap_ptr));
    if(newnode == NULL){
        fprintf(stderr,"Malloc error!\n");
    }
    newnode -> index = index;
    newnode -> distance = distance;
    
    return newnode;
}

//function to swap parent and child
void swap(heap_ptr *A, heap_ptr *B){
    
    heap_ptr temp = *A;
    *A = *B;
    *B = temp;
}

//function to move node up the heap if it is smaller than parent
void heapifyUp(Heap *current, int index){
    
    int i = current -> position[index];
    heap_ptr thisnode = current -> array[i];/*
    printf("0 parent: %d\n", parent);
    printf("1 current: %p\n", current);
    printf("2 thisnode: %p\n", thisnode);
    printf("3 current->array: %p\n", current->array);
    printf("7 thisnode->distance: %d\n", thisnode->distance);
    printf("6 current->position:%d\n", *current->position);
    printf("4 current->array[parent]: %p\n", current->array[parent]);
    printf("5 current->array[parent]->distance: %i\n", current->array[parent]->distance);*/
    
    while(i > 1 && current -> array[i/2] -> distance > thisnode -> distance){
        //swap parent and child
        heap_ptr temp = current -> array[i/2];
        swap(&current->array[i/2], &current->array[i]);
        current->position[index] = i/2;
        current->position[temp->index] = i;
        i = i/2;
    }
}

//function to rearrange heap
void rearrangeHeap(Heap *current, int index){
    int smallest = index;
    int left = 2*index;
    int right = 2*index+1;
    
    if(current -> size > right && current -> array[right] !=NULL &&
        current -> array[right] -> distance < current -> array[left] -> distance){
        smallest = right;
    }
    
    if(current -> size > left && current -> array[left] !=NULL &&
        current -> array[left] -> distance < current -> array[right] -> distance){
        smallest = left;
    }
    
    if(smallest != index){
        heap_ptr smallestnode = current -> array[smallest];
        heap_ptr indexnode = current->array[index];
        swap(&current->array[smallest], &indexnode);
        current->position[indexnode->index]=smallest;
        current->position[smallestnode ->index] = index;
        
        rearrangeHeap(current, smallest);
    }
}

//function to insert heap
void insertHeap(Heap *current, heap_ptr node){
    
    int i = current -> size + 1;
    current -> array[i] = node;
    current -> position[node ->index] = i;
    current -> size = i;
    
    heapifyUp(current, node ->index);
}

//function to remove root, replace it with last node
heap_ptr removeMin(Heap *current){
    
    int maximum = current -> size;
    
    if(current -> size == 0){
        printf("heap is empty\n");
        return NULL;
    }
    
    heap_ptr root = current -> array[1];
    heap_ptr last = current -> array[maximum];
    current -> array [1] = last;
    current -> position[last->index] = 1;
    current -> array[current->size] = NULL;
    current -> size = current -> size - 1; //decrease heap size 
    current -> position[root->index] = 0;
    
    rearrangeHeap(current, 1);
    
    return root;
}

void updateDistance(Heap *current, int index, int distance){
    
    int currentPosition = current ->position[index];
    heap_ptr thisnode = current ->array[currentPosition];
    thisnode -> distance = distance;
    
    heapifyUp(current, index); //move up if smaller than parent
}

void dijkstra(Graph *mygraph, int source){
    
    int maximum = mygraph -> MaxSize;
    int visited[maximum];
    int distance[maximum];
    
    Heap *thisheap = (Heap *)malloc(sizeof(Heap));
    if(thisheap == NULL)
        fprintf(stderr, "Malloc error!\n");
    
    thisheap -> array = (heap_ptr *)malloc((maximum +1)*sizeof(struct heap_node));
    if(thisheap->array== NULL)
        fprintf(stderr, "Malloc error!\n");

    thisheap -> position = (int *)malloc((maximum +1)*sizeof(int));
    if(thisheap -> position == NULL)
        fprintf(stderr, "Malloc error!\n");
    
    thisheap -> size = 0;
    
    for(int i=0; i<maximum; i++){
        if(i==source){
            distance[i]=0;
        }
        else{
            distance[i] = INT_MAX;
        }
        visited[i]=0;
        heap_ptr currentnode = newNode(i, distance[i]);
        insertHeap(thisheap, currentnode);
    }
    
    while(thisheap->size > 0){
        heap_ptr thisnode = removeMin(thisheap);
        int thisindex = thisnode -> index;
        visited[thisindex] = 1;
        
        List *thislist = mygraph -> table[thisindex].outlist;
        while(thislist != NULL){
            int currentindex = thislist -> index;
            int currentposition = thisheap -> position[currentindex];
            
            if(currentposition !=0 && thisnode -> distance != INT_MAX){
                int currentdistance = thisnode -> distance + 1;
                
                if(currentdistance < thisheap -> array[currentposition] -> distance){
                    distance[currentindex] = currentdistance;
                    updateDistance(thisheap, currentindex, currentdistance);
                }
            }
            
            thislist = thislist -> next;
        }
    }
    
    printf("SOURCE NODE: %d\n", source);
    for(int i = 1; i < maximum; i++){
        if(distance[i]<6){
            printf("The distance from NODE %d to NODE %d is %d\n", source, i, distance[i]);
        }
    }
    
    for(int i = 1; i < maximum; i++){
        if(distance[i] == INT_MAX){
            printf("NODE %d is not reachable from NODE %d\n", i, source);
        }
    }   
    
    for(int i = 1; i < maximum; i++){
        if(distance[i]>6 && distance[i] < INT_MAX){
            printf("The distance from NODE %d to NODE %d is %d\nNot a small world!\n", source, i, distance[i]);
        }
    }
}
