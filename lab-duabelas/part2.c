#include "graph.h"

int main(int argc, char **argv)
{
    Graph mygraph;
    
    read_graph(&mygraph, argv[1]);
    
    heuristic(&mygraph, 17, 21);
    
    return 0;
    
}