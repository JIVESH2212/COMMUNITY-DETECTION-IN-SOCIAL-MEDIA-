#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

// a structure to represent a unweighted edge in graph
struct Edge
{
int src,dest;
}*age;

// a structure to represent a connected, undirected
// and unweighted graph as a collection of edges.

struct Graph
{
    // V-> Number of vertices, E-> Number of edges
int V, E;
    // graph is represented as an array of edges.
    // Since the graph is undirected, the edge
    // from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
   struct Edge *age;
};

// A structure to represent a subset for union-find
struct subset
{
int parent;
int rank;
};

// Function prototypes for union-find (These functions are defined
// after kargerMinCut() )

int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);

// A very basic implementation of Karger's randomized
// algorithm for finding the minimum cut. Please note
// that Karger's algorithm is a Monte Carlo Randomized algo
// and the cut returned by the algorithm may not be
// minimum always

int kargerMinCut(struct Graph *graph)
{        int a,i;

    // Get data of given graph
int V = graph->V, E=graph->E;
int vertices=V;
struct Edge *age =graph->age;
int cutedges = 0;

    // Allocate memory for creating V subsets.
 struct subset *subsets=subset[V];
    // Create V subsets with single elements
    for(a = 0; a<V; ++a)
    {
	subsets[a].parent = a;
	subsets[a].rank = 0;
    }

    // Initially there are V vertices in
    // contracted graph

    // Keep contracting vertices until there are
    // 2 vertices.
    while (vertices> 2)
    {
       // Pick a random edge

int i = rand() % E;

       // Find vertices (or sets) of two corners
       // of current edge
int subset1 = find(subsets, age[i].src);
int subset2 = find(subsets, age[i].dest);
       // If two corners belong to same subset,
       // then no point considering this edge
       if (subset1 == subset2)
	 continue;

       // Else contract the edge (or combine the
       // corners of edge into one vertex)
       else
       {
printf("Contracting edge %d-%d\n",age[i].src, age[i].dest);
	  vertices--;
	  Union(subsets, subset1, subset2);
       }
    }
    // Now we have two vertices (or subsets) left in
    // the contracted graph, so count the edges between
    // two components and return the count.

    for (i=0; i<E; i++)
    {
int subset1 = find(subsets, age[i].src);
int subset2 = find(subsets, age[i].dest);
	if (subset1 != subset2)
	  cutedges++;
    }
    return cutedges;
}

// A utility function to find set of an element i
// (uses path compression technique)

int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
     subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)

void Union(struct subset subsets[], int x, int y)
{
int xroot = find(subsets, x);
int yroot = find(subsets, y);
    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot].rank<subsets[yroot].rank)
	subsets[xroot].parent=yroot;
    else if (subsets[xroot].rank>subsets[yroot].rank)
	subsets[yroot].parent = xroot;
    // If ranks are same, then make one as root and
    // increment its rank by one
    else
    {
	subsets[yroot].parent = xroot;
	subsets[xroot].rank++;
    }
}

// Creates a graph with V vertices and E edges
struct Graph *createGraph(int V,int E)
{
   struct Graph *graph = new Graph;
 // struct graph=(struct Graph*)malloc(sizeof(struct Graph));
    graph->V =V;
    graph->E =E;
    graph->age=new Edge[E];
    return graph;
};
// Driver program to test above functions
int main()
{
    /* Let us create following unweighted graph
	0------1
	| \    |
	|   \  |
	|     \|
	2------3   */
int V = 4;  // Number of vertices in graph
int E = 5;  // Number of edges in graph

    struct Graph *graph=createGraph(V, E);
    clrscr();
    // add edge 0-1
    graph->age[0].src = 0;
    graph->age[0].dest = 1;
// add edge 0-2
    graph->age[1].src = 0;
    graph->age[1].dest = 2;
    // add edge 0-3
    graph->age[2].src = 0;
    graph->age[2].dest = 3;
    // add edge 1-3
    graph->age[3].src = 1;
    graph->age[3].dest = 3;
    // add edge 2-3
    graph->age[4].src = 2;
    graph->age[4].dest = 3;
    // Use a different seed value for every run.

srand(time(NULL));
printf("\nCut found by Karger randomized algo is %d\n",kargerMinCut(graph));

    return 0;
    getch();
}
