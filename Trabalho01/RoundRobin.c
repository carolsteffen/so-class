#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

 typedef struct TasksRR {
  	char taskName[2];
  	int initialValue;
  	int finalValue;
  } TasksRR;
 
int main()
{
	FILE *archive;
	TasksRR tasks[100];
	int index = 0, tasksIndex = 0, tasksQuantity_p = 0, qtt = 4;
	int limitTasks, total = 0, counterTasks = 0, quantum = 1, waitingTime = 0, turnAroundTime = 0, temp[10];
	float avgWaitTime, avgTAT;
	int tasksWT, tasksTAT;
      
	archive = fopen("Archive.txt", "r");
	if (archive == NULL)
	{
		printf("Erro!\n");
		exit(1);
	}
      	
	fscanf(archive, "%d", &tasksQuantity_p);
	printf("Quantidade de Tarefas: %d \n", tasksQuantity_p);	
	limitTasks = tasksQuantity_p;
	
	
	for(index = 0; index<=tasksQuantity_p; index++){
		fscanf(archive,"%s %d %d\n", tasks[index].taskName, &tasks[index].initialValue, &tasks[index].finalValue);	
		temp[index] = tasks[index].finalValue;
	}
 

	while(qtt != 0)
	{
		{
            if(temp[index] <= quantum && temp[index] > 0)
            {
                  total = total + temp[index];
                  temp[index] = 0;
                  counterTasks = 1;
            }
            else if(temp[index] > 0)
            {
                  temp[index] = temp[index] - quantum;
                  total = total + quantum;
            }
            if(temp[index] == 0 && counterTasks == 1)
            {
                  qtt--;
                  
                  tasksWT = total - tasks[index].initialValue;
                  tasksTAT = total - tasks[index].initialValue - tasks[index].finalValue;
                  
                  printf("[%s] --> Valor Inicial: %d | Valor Final: %d | Tempo de Espera: %d | Tempo de Retorno: %d \n \n", tasks[index].taskName, tasks[index].initialValue, tasks[index].finalValue, tasksWT, tasksTAT);
                  
                  waitingTime = waitingTime + total - tasks[index].initialValue - tasks[index].finalValue;
                  turnAroundTime = turnAroundTime + total - tasks[index].initialValue;
                  
                  counterTasks = 0;
            }
            if(index == limitTasks - 1)
            {
                  index = 0;
            }
            else if(tasks[index + 1].initialValue <= total)
            {
                  index++;
            }
            else
            {
                  index = 0;
            }
		}
	}
      avgWaitTime = waitingTime * 1.0 / limitTasks;
      avgTAT = turnAroundTime * 1.0 / limitTasks;
      printf("Media de tempo de espera: %.3f \n", avgWaitTime);
      printf("Media de tempo de retorno: %.3f \n", avgTAT);
      return 0;
}
