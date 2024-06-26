#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "MazeSolver.h"
#include "Graph.h"
#include "Solution.h"
#include "PriorityQueue.h"

int visitNode(Graph graph, int node, int end, char* visited, Path *stack){

	visited[node]='V';
	push(stack, node);
	for(int i=0;graph->neighbors[node][i]!=-1;i++){

		if(graph->neighbors[node][i]==end){

			printf("Sukces:Znaleziono ścieżkę\n");
			push(stack, graph->neighbors[node][i]);
			return 1;
		}
		else if(visited[graph->neighbors[node][i]]=='N'){

			if(visitNode(graph, graph->neighbors[node][i], end, visited, stack))
				return 1;
		}


	}
	pop(stack);
	return 0;
}

void solve(Graph graph, Path *stack)
{
	char* visited=malloc(graph->n);
	int start=graph->start;
	int end=graph->end;
	for(int i=0;i<graph->n;i++){

		visited[i]='N';
	}

	visitNode(graph, start, end, visited, stack);
	free(visited);
	reverse(stack);
}

void dijkstraSolve(Graph g,Path* solution){
	int distance [g->n];
	PQueue u;
	if((u=malloc(sizeof*u))==NULL){
		fprintf(stderr, "Błąd:Zabrakło pamięci na rozwiązanie labirnytu");
		return;

	}
	u->nxt=NULL;
	int previous [g->n];
	memset(&previous,-1,g->n*sizeof(int));
	for(int i=0;i<g->n;i++){
		distance[i]=INT_MAX;

	}
	distance[g->start]=0;
	PQueue q=NULL;
	for(int i=g->n-1;i>0;i--){
		if(i!=g->start)
			q=add(q,i,distance[i]);


	}
	q=add(q,g->start,0);
	while(q!=NULL){
		q=popElem(q,u);
		if(u->i==g->end)
			printf("Sukces:Znaleziono ścieżkę\n");
		for(int j=0;g->neighbors[u->i][j]!=-1 && j<4;j++){
			int v=g->neighbors[u->i][j];
			if(distance[v]>distance[u->i]+getEdge(g,u->i,v)){
				distance[v]=distance[u->i]+getEdge(g,u->i,v);
				q=promoteElem(q,v,distance[v]);
				previous[v]=u->i;
			}

		}

	}
	free(u);
	push(solution,g->end);
	for(int k=g->end;k>g->start;){

		push(solution,previous[k]);
		k=previous[k];	

	}
	push(solution,g->start);
	freePQueue(q);

}
int heuristic(Graph g, int vertex){
	return abs(g->coords[2*g->end]-g->coords[2*vertex]) +abs(g->coords[2*g->end+1]-g->coords[2*vertex+1]);


}
void astarSolve(Graph g, Path *solution){
	unsigned int score [g->n];
	unsigned int test_score;
	PQueue u;
	char close[g->n];
	if((u=malloc(sizeof*u))==NULL){
		fprintf(stderr, "Błąd:Zabrakło pamięci na rozwiązanie labirnytu");
		return;

	}
	u->nxt=NULL;
	int previous[g->n];
	for(int i=0;i<g->n;i++){
		score[i]=INT_MAX;

	}

	memset(&previous,-1,g->n*sizeof(int));
	memset(&close,'N',g->n*sizeof(short));
	score[g->start]=0;
	PQueue opened=NULL;
	opened=add(opened,g->start,0);
	while(opened!=NULL){
		opened=popElem(opened,u);
		close[u->i]='C';
		if(u->i==g->end){
			printf("Sukces:Znaleziono Ścieżkę:\n");	
			break;

		}

		for(int j=0;g->neighbors[u->i][j]!=-1 && j<4;j++){
			int v=g->neighbors[u->i][j];

			test_score=u->key+getEdge(g,u->i,v);
			if(close[v]=='C'){

				if(test_score+heuristic(g,v)<score[v]+heuristic(g,v)){

					score[v]=test_score;
					close[v]='N';
					opened=add(opened,v,score[v]+heuristic(g,v));
					previous[v]=u->i;
				}

			}
			else{
				score[v]=test_score;
				opened=add(opened,v,score[v]+heuristic(g,v));
				previous[v]=u->i;
			}
		}

	}
	free(u);
	freePQueue(opened);
	push(solution,g->end);
	for(int k=g->end;k>g->start;){
		if(previous[k]==-1){
			fprintf(stderr,"Błąd: Błąd ścieżki- A*");
			return;
		}
		push(solution,previous[k]);
		k=previous[k];	

	}
	push(solution,g->start);


}
