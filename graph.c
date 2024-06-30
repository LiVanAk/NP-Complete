#include"graph.h"

void InitGraph(FILE* fp,MatGraph* Graph){
    fscanf(fp,"%d %d",&Graph->n,&Graph->e);
    int a,b;
    for(int i = 0; i != Graph->e; i++){
        fscanf(fp,"%d,%d",&a,&b);
        Graph->edges[a][b] = Graph->edges[b][a] = 1;
    }
}

void InitDGraph(FILE* fp, MatGraph* Graph){
    fscanf(fp,"%d %d",&Graph->n,&Graph->e);
    int a,b;
    for(int i = 0; i != Graph->e; i++){
        fscanf(fp,"%d,%d",&a,&b);
        Graph->edges[a][b] = 1;
    }
}

void PrintGraph(MatGraph* Graph){
    for(int i = 0; i != Graph->n; i++){
        for(int j = 0; j != Graph->n; j++){
            printf("%d ",Graph->edges[i][j]);
        }
        printf("\n");
    }
}


/*                             CLIQUE                          */
// Judge subset is clique
bool is_clique(MatGraph* Graph, int* subset, int size){
    for(int i = 0; i != size; i++){
        for(int j = i+1; j != size; j++){
            if(!Graph->edges[subset[i]][subset[j]])
                return false;
        }
    }
    return true;
}

// Solve Clique with backtracking
bool solve_clique(MatGraph* Graph, int start, int k, int size, int* subset){
    if(size == k)
        return true;
    for(int i = start; i != Graph->n; i++){
        subset[size] = i;
        if(is_clique(Graph, subset, size + 1)){
            if(solve_clique(Graph, i + 1, k, size + 1, subset))
                return true;
        }
    }
    return false;
}

// Solve Clique Cover with backtracking
bool solve_clique_cover(MatGraph* Graph,int* cover, int* clique_sizes, int k, int size, int num_cliques){
    if(size == Graph->n)
        return true;
    for(int i = 0; i != num_cliques; i++){
        cover[size] = i;
        clique_sizes[i]++;      // Current clique size +1
        if(is_clique(Graph, cover, size + 1))
            if(solve_clique_cover(Graph, cover, clique_sizes, k ,size + 1, num_cliques));
                return true;
        clique_sizes[i]--;
    }
    if(num_cliques < k){
        cover[size] = num_cliques;
        clique_sizes[num_cliques] = 1;
        if(solve_clique_cover(Graph, cover, clique_sizes, k, size + 1, num_cliques + 1))
            return true;
    }
    return false;
}

// Hamilton
bool is_connected(MatGraph* Graph, int v, int path[],int pos){
    // Check if v is connected to the last vertex
    if(Graph->edges[pos][v] == 0)
        return false;
    // Check if v is in path already
    for(int i = 0; i != Graph->n ; i++){
        if(path[i] == v)
            return false;
    }
    return true;
}
// Looking for hamilton cycle
bool hamiltonCycle(MatGraph* Graph, int path[], int num){
    if(num == Graph->n){
        if(Graph->edges[path[num-1]][path[0]])
            return true;
        else
            return false;
    }
    for(int v = 0; v != Graph->n; v++){
        if(is_connected(Graph, v, path, path[num-1])){
            path[num] = v;
            if(hamiltonCycle(Graph, path, num + 1)){
                return true;
            }
            path[num] = -1;
        }
    }
    return false;
}
void hamilton(MatGraph* Graph){
    int* path = (int*)malloc(sizeof(int)*Graph->n);
    int op = 0;
    for(int start = 0; start != Graph->n; start++){
        // Init path
        for(int i = 0; i != Graph->n; i++)
            path[i] = -1;
        path[0] = start;
        if(hamiltonCycle(Graph, path, 1)){
            printf("Hamilton cycle:\n");
            for (int i = 0; i != Graph->n; i++)
                printf("%d ", path[i]);
            printf("%d\n", path[0]);
            op = 1;
            break;
        }
    }
    if (!op) {
        printf("No hamilton cycle\n");
    }
}

// Directed
// Looking for hamilton cycle
bool dhamiltonCycle(MatGraph* Graph, int path[], int num){
    if(num == Graph->n){
        if(Graph->edges[path[num-1]][path[0]])
            return true;
        else
            return false;
    }
    for(int v = 0; v != Graph->n; v++){
        if(is_connected(Graph, v, path, path[num-1])){
            path[num] = v;
            if(dhamiltonCycle(Graph, path, num + 1)){
                return true;
            }
            path[num] = -1;
        }
    }
    return false;
}
void dhamilton(MatGraph* Graph){
    int* path = (int*)malloc(sizeof(int)*Graph->n);
    int op = 0;
    for(int start = 0; start != Graph->n; start++){
        // Init path
        for(int i = 0; i != Graph->n; i++)
            path[i] = -1;
        path[0] = start;
        if(dhamiltonCycle(Graph, path, 1)){
            printf("Directed hamilton cycle:\n");
            for (int i = 0; i != Graph->n; i++)
                printf("%d ", path[i]);
            printf("%d\n", path[0]);
            op = 1;
            break;
        }
    }
    if (!op) {
        printf("No directed hamilton cycle\n");
    }
}

// CHROMATIC NUMBER
bool is_ok(MatGraph* Graph, int v, int color){
    if(Graph->colors[v])
        return false;
    for(int i = 0; i != Graph->n; i++){
        if((Graph->edges[v][i] == 1) && (Graph->colors[i] == color))
            return false;
    }
    return true;
}
bool chromatic(MatGraph* Graph, int k, int v){
    if(v == Graph->n)
        return true;
    for(int c = 1; c <= k; c++){
        if(is_ok(Graph, v, c)){
            Graph->colors[v] = c;
            if(chromatic(Graph, k, v+1))
                return true;
            Graph->colors[v] = 0;
        }
    }
    return false;
}

// Vertex cover
bool is_covered(MatGraph* Graph, int* C, int size){
    for(int i = 0; i != Graph->n; i++){
        for(int j = i+1; j != Graph->n; j++){
            if(Graph->edges[i][j]){
                int op = 0;
                for(int k = 0; k != size; k++)
                    if(C[k] == i || C[k] == j){
                        op = 1;
                        break;
                    }
                if(!op)
                    return false;
            }
        }
    }
    return true;
}
void complement(MatGraph* G, MatGraph* CG){
    CG->n = G->n;
    CG->e = G->n*(G->n-1)/2 - G->e;
    for(int i = 0; i != G->n; i++){
        CG->edges[i][i] = 0;
    }
    for(int i = 0; i != G->n; i++){
        for(int j = i+1; j != G->n; j++){
            if(G->edges[i][j])
                CG->edges[i][j] = CG->edges[j][i] = 0;
            else
                CG->edges[i][j] = CG->edges[j][i] = 1;
        }
    }
}