#include "graph.h"

//function returns true if the given index is not in the node's outlist
int not_in_outlist(Graph *mygraph, int source, int target)
{
    List *thislist = mygraph->table[source].outlist;
    while(thislist !=NULL){
        int thisindex = thislist -> index;
        if(thisindex == target){
            return 0;
        }
        thislist = thislist -> next;
    }
    return 1;
}

/*
CURRENT ← SOURCE;
while (TARGET not in CURRENT.OUTLIST) and (CURRENT.OUTLIST not empty)
add CURRENT to PATH
Let MAXOUT be the unvisited node in CURRENT.OUTLIST with largest out-degree
CURRENT ← MAXOUT;
endwhile
add CURRENT to PATH
*/
void heuristic(Graph *mygraph, int source, int target)
{
    int maximum = mygraph -> MaxSize;
    int visited[maximum];
    
    for(int i = 0; i < maximum; i++){
        visited[i] = 0;
    }
    
    int current = source;
    int path[maximum];
    int j = 0;
    
    while(not_in_outlist(mygraph, current, target) && mygraph->table[current].outlist != NULL)
    {
        path[j] = current;//add current to path
        visited[current] = 1;
        j++;
        int maxout = 0;//node with largest out-degree
        int Maximum =0;//number of outdegrees
        List *currentlist = mygraph->table[current].outlist;
        while(currentlist != NULL){
            int currentindex = currentlist -> index;
            int currentmax = mygraph->table[currentindex].outdegree;
            if(visited[currentindex] == 0 && currentmax > Maximum){
                maxout = currentindex;
                Maximum = currentmax;
            }
            currentlist = currentlist ->next;
        }
        current = maxout;
    }
    path[j] = current;
    j++;
    
    printf("SOURCE: %d\t TARGET:%d\n", source, target);
    printf("The path from the source to target is\n");
    for(int i = 0; i<j; i++){
        if(path[i]!=0){
            printf("SOURCE %d\n", path[i]);
        }
        if(current == 0){
            printf("TARGET %d is not reachable from SOURCE %d\n", target, source);
        }
        else{
            printf("The distance from SOURCE %d to TARGET %d is %d\n", source, target, j);
        }
    }
}
