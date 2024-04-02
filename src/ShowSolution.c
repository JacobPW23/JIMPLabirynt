#include "Graph.h"
#include "Solution.h"
#include "ShowSolution.h"

void wypisz(Stack *stack, Graph graph)
{
    Node *temp=stack->top;
    while(temp!=NULL && temp->next!=NULL)
    {
        if(graph->coords[2*(temp->node)] == graph->coords[2*(temp->next->node)])
        {
            if(graph->coords[2*(temp->node)+1] > graph->coords[2*(temp->next->node)+1])
                printf("Góra %d \n", graph->coords[2*(temp->node)+1]-graph->coords[2*(temp->next->node)+1]);
            else if(graph->coords[2*(temp->node)+1] < graph->coords[2*(temp->next->node)+1])
                printf("Dół %d \n", graph->coords[2*(temp->next->node)+1]-graph->coords[2*(temp->node)+1]);
        }

        else if(graph->coords[2*(temp->node)+1] == graph->coords[2*(temp->next->node)+1])
        {
            if(graph->coords[2*(temp->node)] > graph->coords[2*(temp->next->node)])
                printf("Lewo %d \n", graph->coords[2*(temp->node)]-graph->coords[2*(temp->next->node)]);
            else if(graph->coords[2*(temp->node)] < graph->coords[2*(temp->next->node)])
                printf("Prawo %d \n", graph->coords[2*(temp->next->node)]-graph->coords[2*(temp->node)]);
        }
        else
            printf("Błąd\n");

        temp=temp->next;
     }
}

