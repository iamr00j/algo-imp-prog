//http://syllabus.cs.manchester.ac.uk/ugt/2017/COMP26120/lab/ex11-new.html

#include "graph.h"

int main(int argc, char **argv){
    
    Graph mygraph;
    read_graph(&mygraph, argv[1]);

    dfs(&mygraph, 3); 
    
    return (0);
}