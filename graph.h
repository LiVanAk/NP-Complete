/*  Gpaph  */
/*  
    n e                     // num of nodes & edges
    0,3 2,4 3,5 2,6 5,1     // edges
*/
#define MAXV 500
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct{
    int edges[MAXV][MAXV];
    int n,e;    // nodes,edges
    int colors[MAXV];
} MatGraph;
void InitGraph(FILE*, MatGraph*);
void InitDGraph(FILE*, MatGraph*);
void PrintGraph(MatGraph*);
// Clique
bool is_clique(MatGraph*, int*, int);
bool solve_clique(MatGraph* Graph, int start, int k, int size, int* subset);
bool solve_clique_cover(MatGraph* Graph,int* cover, int* clique_sizes, int k, int size, int num_cliques);
// Hamilton
bool is_connected(MatGraph* Graph, int v, int path[],int pos);
bool hamiltonCycle(MatGraph* Graph, int path[], int num);
void hamilton(MatGraph* Graph);
bool dhamiltonCycle(MatGraph* Graph, int path[], int num);
void dhamilton(MatGraph* Graph);
// CHROMATIC NUMBER
bool is_ok(MatGraph* Graph, int v, int color);
bool chromatic(MatGraph* Graph, int k, int v);
// Vertex cover
bool is_covered(MatGraph* Graph, int* C, int size);
void complement(MatGraph* G, MatGraph* CG);