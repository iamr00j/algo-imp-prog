//http://syllabus.cs.manchester.ac.uk/ugt/2017/COMP26120/lab/ex11-new.html

#include "graph.h"

Node find_largestOut(Graph * mygraph)
{

    int i = 0;
    int maximum = mygraph->MaxSize;
    int current = 0;
    int index = 0;

    for (i = 0; i < maximum; i++) {
		if (mygraph->table[i].outdegree > current) {
		    current = mygraph->table[i].outdegree;
		    index = i;
		}
    }

    return mygraph->table[index];
}

Node find_smallestOut(Graph * mygraph)
{

    int i = 0;
    int j = 0;
    int maximum = mygraph->MaxSize;
    int current = 0;
    int index = 0;

    while (mygraph->table[i].outdegree == 0) {
	i++;
    }

    current = mygraph->table[i].outdegree;
    index = i;

    for (j = i; j < maximum; j++) {
	if (mygraph->table[j].outdegree < current
	    && mygraph->table[j].outdegree != 0) {
	    current = mygraph->table[j].outdegree;
	    index = j;
	}
    }

    return mygraph->table[index];
}

Node find_largestIn(Graph * mygraph)
{

    int maximum = mygraph->MaxSize;
    int current = 0;
    int index = 0;
    int temp[maximum];

    for (int i = 0; i < maximum; i++) {
	temp[i] = 0;
    }

    List *thislist;

    for (int i = 0; i < maximum; i++) {
		thislist = mygraph->table[i].outlist;
		while (thislist != NULL) {
		    temp[thislist->index]++;
		    thislist = thislist->next;
		}
    }

	for (int i = 0; i < maximum; i++) {
	    if (temp[i] > current) {
		current = temp[i];
		index = i;
	    }
	}

	return mygraph->table[index];
}

Node find_smallestIn(Graph * mygraph) {

	int maximum = mygraph->MaxSize;
	int current = 0;
	int index = 0;
	int temp[maximum];

	for (int i = 0; i < maximum; i++) {
	    temp[i] = 0;
	}

	List *thislist;

	for (int i = 0; i < maximum; i++) {
	    thislist = mygraph->table[i].outlist;
	    while (thislist != NULL) {
		temp[thislist->index]++;
		thislist = thislist->next;
	    }
	}

	int j = 0;
	while (temp[j] == 0) {
	    j++;
	}
	current = temp[j];
	index = j;

	for (int i = j; i < maximum; i++) {
	    if (temp[i] < current && temp[i] != 0) {
		current = temp[i];
		index = i;
	    }
	}

	return mygraph->table[index];
}

int main(int argc, char *argv[]) {
	Graph mygraph;

	read_graph(&mygraph, argv[1]);

	/* you take it from here */
	print_graph(&mygraph);

	Node largestOut = find_largestOut(&mygraph);
	Node smallestOut = find_smallestOut(&mygraph);
	Node largestIn = find_largestIn(&mygraph);
	Node smallestIn = find_smallestIn(&mygraph);

	printf("The node with the largest out-degree is\n");
	printf("Node\t Out-degree\n %s\t%d\n", largestOut.name,
	       largestOut.outdegree);

	printf("The node with the smallest out-degree is\n");
	printf("Node\t Out-degree\n %s\t%d\n", smallestOut.name,
	       smallestOut.outdegree);

	printf("The node with the largest in-degree is\n");
	printf("Node\n %s\n", largestIn.name);

	printf("The node with the smallest in-degree is\n");
	printf("Node\n %s\n", smallestIn.name);

	return 0;
}
