#include <stdlib.h>
#include <stdio.h>
#include "MazeSolver.h"
#include "Graph.h"
#include "Solution.h"

int visitNode(Graph graph, int node, int end, int *visited, Stack *stack)
{
    visited[node]=1;
    push(stack, node);
    for(int i=0;graph->neighbours[node][i]!=-1;i++)
    {
        if(graph->neighbours[node][i]==end)
        {
            printf("Znaleziono ścieżkę\n");
	    push(stack, graph->neighbours[node][i]);
            return 1;
        }
	else if(visited[graph->neighbours[node][i]]==0)
        {
	    if(visitNode(graph, graph->neighbours[node][i], end, visited, stack))
            	return 1;
        }

        
    }
    pop(stack);
    return 0;
}

void solve(Graph graph, int start, int end, int *visited, Stack *stack)
{
    for(int i=0;i<graph->n;i++)
    {
	    visited[i]=0;
    }

    visitNode(graph, start, end, visited, stack);
}

