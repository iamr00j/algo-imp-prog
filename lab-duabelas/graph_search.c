#include "graph.h"
/* Good luck */
#define DFS
#undef BFS

#ifdef DFS 
void visit(Graph *mygraph, int index, int *dfsnum){
    dfsnum[index] = 1;
    List *current = mygraph -> table[index].outlist;
    while(current != NULL){
        if(dfsnum[current -> index] == 0)
            visit(mygraph, current -> index, dfsnum);
        current = current -> next;
    }
    printf("NODE %d %s\n", index, mygraph -> table[index].name);
}

//DFS traversal of the vertices reachable from v.
//Function uses recursive visit()
void dfs(Graph *mygraph, int index){
    
    int maximum = mygraph -> MaxSize;
    int dfsnum[maximum];
    int i = 0;
    
    for(i = 0; i < maximum; i++){
        dfsnum[i] = 0;
    }
    
    visit(mygraph, index, dfsnum);
    
}
#endif

//function to returns first object for the queue
int getFirst(int *searchQ, int qSize){
    
    int i = 0;
    int first = searchQ[0];
    
    for(i = 0; i < qSize - 1; i++)
        searchQ[i] = searchQ[i+1];
    searchQ[qSize - 1] = 0;

    return first;
}

//function to add first object to the queue
void addFirst(int *searchQ, int qSize, int object){

    int i = 0;
    for(i = 0; i < qSize; i++)
        searchQ[i+1] = searchQ [i];
    searchQ[0] = object;
}

void dfs_bfs(Graph *mygraph, int index){
    
    int maximum = mygraph -> MaxSize;
    int bfsnum[maximum];
    int searchQ[maximum];
    int qSize = 1;
    int i = 0;
    int j = 0;
    
    searchQ[0] = index;
    
    for(i = 0; i < maximum; i++){
        bfsnum[i] = 0;
    }
    
    while(qSize > 0){
        #ifdef BFS
        i = getFirst(searchQ, qSize);
        #endif
    
        #ifdef DFS
        while(searchQ [j] == 0){
            j++;
        }
        i = searchQ[j];
        #endif
        
        if(bfsnum[i]==0){
            bfsnum[i] = 1;
            qSize--;
            List *thislist = mygraph -> table[i].outlist;
            while(thislist != NULL){
                if(bfsnum[thislist -> index] == 0){
                    
                #ifdef BFS
                    searchQ[qSize] = thislist -> index;
                #endif
                #ifdef DFS
                    addFirst(searchQ, qSize, thislist -> index);
                #endif
                    qSize++;
                }
                thislist = thislist -> next;
            }
            if(i!=0){
                printf("NODE %d\t%s\n", i, mygraph->table[i].name);
            }
        }
    }
}
