#include "graph.h"

int main(int argc, char **argv)
{
    Graph mygraph;
    
    read_graph(&mygraph, argv[1]);
    
    dijkstra(&mygraph, 17);
    
    return 0;
    
}