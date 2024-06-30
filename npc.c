#include"npc.h"
#include"graph.h"
#include"set.h"

void printHint(){
    printf("Plese select the NPC question:\n");
    printf("\t1.SATISFIABILITY\n");
    printf("\t2.0-1 INTEGER PROGRAMMING\n");
    printf("\t3.CLIQUE\n");
    printf("\t4.SET PACKING\n");
    printf("\t5.VERTEX COVER\n");
    printf("\t6.SET COVERING\n");
    printf("\t7.FEEDBACK NODE SET\n");
    printf("\t8.FEEDBACK ARC SET\n");
    printf("\t9.DIRECTED HAMILTON CIRCUIT\n");
    printf("\t10.UNDIRECTED HAMILTON CIRCUIT\n");
    printf("\t11.SATISFIABILITY WITH AT MOST 3 LITERALS PER CLAUSE\n");
    printf("\t12.CHROMATIC NUMBER\n");
    printf("\t13.CLIQUE COVER\n");
    printf("\t14.EXACT COVER\n");
    printf("\t15.HITTING SET\n");
    printf("\t16.STEINER TREE\n");
    printf("\t17.3-DIMENSIONAL MATCHING\n");
    printf("\t18.KNAPSACK\n");
    printf("\t19.JOB SEQUENCING\n");
    printf("\t20.PARTITION\n");
    printf("\t21.MAX CUT\n");
}

// SATISFIABILITY
void npc1(){
    FILE *fp = fopen("graph.txt","r");
    MatGraph Graph;
    InitGraph(fp, &Graph);
    fclose(fp);
}

// 0-1 INTEGER PROGRAMMING
void npc2(){
    
}

// CLIQUE
void npc3(){
    FILE *fp = fopen("clique.txt","r");
    MatGraph Graph;
    InitGraph(fp, &Graph);
    PrintGraph(&Graph);
    int k;
    printf("Please input k:");
    scanf("%d",&k);
    int* subset = (int*)malloc(sizeof(int)*(Graph.n));
    if(solve_clique(&Graph,0,k,0,subset))
        printf("CLIQUE of size %d exists\n", k);
    else
        printf("CLIQUE of size %d does not exist\n", k);
    free(subset);
    fclose(fp);
}

// SET PACKING
void npc4(){
    FILE *fp = fopen("packing.txt","r");
    int n;
    fscanf(fp, "%d", &n);
    int** U = (int**)malloc(sizeof(int*)*n);
    int* sz = (int*)malloc(sizeof(int)*n);
    for(int i = 0; i != n; i++){
        fscanf(fp, "%d", &sz[i]);
        U[i] = (int*)malloc(sizeof(int)*sz[i]);
        for(int j = 0; j != sz[i]; j++){
            fscanf(fp, "%d", &U[i][j]);
        }
    }
    // // Display
    // for(int i = 0; i != n; i++){
    //     for(int j = 0; j != sz[i]; j++){
    //         printf("%d ",U[i][j]);
    //     }
    //     printf("\n");
    // }
    int op = 0;
    for(int i = 0; i != n; i++){
        for(int j = i+1; j != n; j++){
            if(isEmpty(U[i],sz[i],U[j],sz[j])){
                printf("U1:%d,U2:%d\n",i+1,j+1);
                op = 1;
            }
        }
    }
    if(op)
        printf("Yes\n");
    else
        printf("No\n");
    for(int i = 0; i != n; i++){
        free(U[i]);
    }
    free(U);
    free(sz);
    fclose(fp);
}

// VERTEX COVER
void npc5(){
    FILE *fp = fopen("vertexCover.txt","r");
    MatGraph Graph;
    InitGraph(fp, &Graph);
    PrintGraph(&Graph);
    fclose(fp);
}
void npc6();
void npc7();
void npc8();
void npc9(){
    FILE *fp = fopen("dhamilton2.txt","r");
    MatGraph Graph;
    InitDGraph(fp, &Graph);
    PrintGraph(&Graph);
    dhamilton(&Graph);
    fclose(fp);
}

// UNDIRECTED HAMILTON CIRCUIT
void npc10(){
    FILE *fp = fopen("hamilton1.txt","r");
    MatGraph Graph;
    InitGraph(fp, &Graph);
    PrintGraph(&Graph);
    hamilton(&Graph);
    fclose(fp);
}
void npc11();
// CHROMATIC NUMBER
void npc12(){
    FILE *fp = fopen("chromatic.txt","r");
    MatGraph Graph;
    InitGraph(fp, &Graph);
    PrintGraph(&Graph);
    // Init colors      0:uncolored     else:other colors
    for(int i = 0; i != Graph.n; i++){
        Graph.colors[i] = 0;
    }
    int k;
    printf("Please input k:");
    scanf("%d",&k);
    if (!chromatic(&Graph, k, 0)) {
        printf("No resolution...\n");
    }
    else{
        for (int i = 0; i < Graph.n; i++)
            printf("vertex: %d => color: %d\n", i, Graph.colors[i]);
    }
    
    fclose(fp);
}

// CLIQUE COVER
void npc13(){
    FILE *fp = fopen("clique.txt","r");
    MatGraph Graph;
    InitGraph(fp, &Graph);
    int k = Graph.n;
    int* cover = (int*)malloc(sizeof(int)*(Graph.n));
    int* clique_sizes = (int*)malloc(sizeof(int)*(Graph.n));
    for(int i = 0; i != Graph.n; i++){
        cover[i] = -1;
        clique_sizes[i] = 0;
    }
    while (!solve_clique_cover(&Graph, cover, clique_sizes, k, 0, 0)) {
        k--;
    }
    for(int i = 0; i != Graph.n; i++){
        printf("%d:%d\n",i,clique_sizes[i]);
    }
    free(cover);
    free(clique_sizes);
    fclose(fp);
}
void npc14();
void npc15();
void npc16();
void npc17();

// KNAPSACK
void npc18(){
    FILE *fp = fopen("knapsack.txt","r");
    int n,C;    // num of items and Volume
    fscanf(fp, "%d %d", &n, &C);
    int *w,*v;      // w[i-1]表示第i个物品的重量（体积），v[i-1]表示第i个物品的价值
    w = (int*)malloc(sizeof(int) * n);
    v = (int*)malloc(sizeof(int) * n);
    // Read in volume
    for(int i = 0; i != n; i++){
        fscanf(fp, "%d", &w[i]);
    }
    // Read in value
    for(int i = 0; i != n; i++){
        fscanf(fp, "%d", &v[i]);
    }
    // Display v & w
    // for(int i = 0; i != n; i++){
    //     printf("%d: w=%d,v=%d\n",i+1,w[i],v[i]);
    // }
    
    //Allocate space
    int **V;     // V[i][j]表示前 i 个物品装入容量为 j 的背包中获得的最大价值
    V = (int**)malloc(sizeof(int*)*(n+1));
    for(int i = 0; i != n+1; i++)
        V[i] = (int*)malloc(sizeof(int)*(C+1));
    for(int i = 0; i != n+1; i++)
        V[i][0] = 0;
    for(int i = 0; i != C+1; i++)
        V[0][i] = 0;
    
    // Dynamic programming
    for(int i = 1; i != n+1; i++){
        for(int j = 1; j != C+1; j++){
            if (j < w[i-1])
                V[i][j] = V[i-1][j];
            else
                V[i][j] = V[i-1][j]>(V[i-1][j-w[i-1]]+v[i-1])?V[i-1][j]:(V[i-1][j-w[i-1]]+v[i-1]);
        }
    }
    // // Display V[i][j]
    // for(int i = 0; i != n+1; i++){
    //     for(int j = 0; j != C+1; j++){
    //         printf("%d ",V[i][j]);
    //     }
    //     printf("\n");
    // }
    // 标示哪些物品被放入
    int j = C;
    printf("Items placed in the backpack:\n");
    for(int i = n; i != 0 ; i--)
        if(V[i][j] > V[i-1][j]){
            printf("%d: weigh:%d value:%d\n", i, w[i-1], v[i-1]);
            j-=w[i-1];
        }
    // Free space
    for(int i = 0; i != n+1; i++)
        free(V[i]);
    free(V);
    fclose(fp);
}
void npc19();
void npc20();
void npc21();
