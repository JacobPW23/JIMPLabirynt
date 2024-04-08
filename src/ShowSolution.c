#include <string.h>
#include <stdlib.h>
#include "Graph.h"
#include "Solution.h"
#include "ShowSolution.h"

void printSolution(Path *stack, Graph graph)
{
    PathNode *temp=stack->top;
    int prev_x=graph->coords[2*(temp->node)];
    int prev_y=graph->coords[2*(temp->node)+1];
    int dist=0;
    char direction[10]="";
    while(temp!=NULL && temp->next!=NULL)
    {
	int curr_x=graph->coords[2*(temp->node)];
	int curr_y=graph->coords[2*(temp->node)+1];
	int next_x=graph->coords[2*(temp->next->node)];
	int next_y=graph->coords[2*(temp->next->node)+1];
	
        if(curr_x == next_x)
        {
	    int diff=curr_y-next_y;
            if(dist==0 || strcmp(direction, diff > 0 ? "góra" : "dół")==0)
	    {
		    strcpy(direction, diff > 0 ? "góra" : "dół");
		    dist+=abs(diff);
	    }
            else
	    { 
                printf("%s %d\n", direction, dist);
		strcpy(direction, diff > 0 ? "góra" : "dół");
		dist=abs(diff);
	    }
	    	
        }

        else if(curr_y == next_y)
        {
	    int diff=curr_x-next_x;
            if(dist==0 || strcmp(direction, diff > 0 ? "lewo" : "prawo")==0)
	    {
		    strcpy(direction, diff > 0 ? "lewo" : "prawo");
		    dist+=abs(diff);
	    }
            else
	    {
		    printf("%s %d\n", direction, dist);
		    strcpy(direction, diff > 0 ? "lewo" : "prawo");
		    dist=abs(diff);
	    }
        }
        else
            printf("Błąd\n");

        temp=temp->next;
     }
}

