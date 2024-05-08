#include <stdio.h>
#include <stdlib.h>
int comparator(const void* p1, const void* p2){
    const int (*x)[3] = p1;
    const int (*y)[3] = p2;

    return (*x)[2] - (*y)[2];
}

void makeSet(int root[], int rank[], int n){
    int i;
    for (i = 0; i < n; i++)
    {
        root[i] = i;
        rank[i] = 0;
    }
}

int findRoot(int root[], int component){
    if(root[component] == component)
        return component;
    return root[component] = findRoot(root, root[component]);
}

void unionset(int u, int v, int root[], int rank[], int n){
    u = findRoot(root, u);
    v = findRoot(root, v);

    if (rank[u] > rank[v])
    {
        root[v] = u;
    }
    else if (rank[u] < rank[v])
    {
        root[u] = v;
    }
    else
    {
        root[v] = u;
    }
    
}

void KruskalAlgo(int n, int edge[n][3]){
    qsort(edge, n, sizeof(edge[0]), comparator);
    int root[n];
    int rank[n];
    makeSet(root, rank, n);
    int minCost = 0;
    printf("Following are tje edges in the constructed MST\n");
    for(int i = 0; i<n; i++){
        int v1 = findRoot(root, edge[i][0]);
        int v2 = findRoot(root, edge[i][1]);
        int wt = edge[i][2];
        if (v1 != v2){
            unionset(v1, v2, root, rank, n);
            minCost += wt;
            printf("%d -- %d == %d\n", edge[i][0], edge[i][1], wt);
        }
    }
    printf("\nMinimum Cost Spanning Tree: %d\n", minCost);
}

int main(int argc, char const *argv[])
{
    int n, m;
    printf("Enter the row count:\n");
    scanf("%d", &n);
    printf("Enter the col count:\n");
    scanf("%d",&m);
    int Graph[n][m];
    printf("Enter the weighted adjacency matrix of the graph:\n");
    for (int i=0; i<n; i++){
        for (int j = 0; j <m; j++)
        {
            scanf("%d", &Graph[i][j]);
        }
        
    }
    KruskalAlgo(n, Graph);
    return 0;
}
