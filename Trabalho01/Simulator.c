#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TasksRR {
  	char taskName[2];
  	int initialValue;
  	int finalValue;
  } TasksRR;

typedef struct TasksFCFS {
  	char taskName[2];
  	int initialValue;
  	int finalValue;
  	int waitTime;
  	int turnAroundTime;
  	bool completed;
  } TasksFCFS;
  
void RoundRobin(){
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
      fclose(archive);
}
 
int FCFS()
{
	FILE *archive;
	TasksFCFS tasks[100];
	int index = 0, tasksQuantity_p = 0, qtt=4, totalFinalValue = 0;
	int limitTasks, counterTasks = 0, quantum = 1, waitingTime = 0, turnAroundTime = 0, temp[10];
	float avgWaitTime, avgTAT, totalWaitTime = 0, totalTurnAroundTime =0;
      
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
		tasks[index].waitTime = 0;
		tasks[index].turnAroundTime = 0;
		tasks[index].completed = false;
	}
	
	index = 0;
	
	while(qtt != 0){
		if(index>= limitTasks){
			index = 0;
		}
		
		if(temp[index] == counterTasks && tasks[index].completed == false){
			qtt--;
			tasks[index].completed = true;
			
			counterTasks = 0;
			
			index++;
		}
		
		counterTasks++;
	}
	
	for(index = 0; index < limitTasks; index++) {
		if(index == 0){
			tasks[index].waitTime = tasks[index].initialValue;
		}else{
			tasks[index].waitTime = totalFinalValue - tasks[index].initialValue;
		}
		
		totalFinalValue += tasks[index].finalValue;
		totalWaitTime += tasks[index].waitTime;

	}
	
	avgWaitTime = totalWaitTime / limitTasks;
	

	for(index = 0; index < limitTasks; index++) {
		turnAroundTime += tasks[index].finalValue;
		tasks[index].turnAroundTime = turnAroundTime - tasks[index].initialValue;
		totalTurnAroundTime+=tasks[index].turnAroundTime;
	}
	
	avgTAT = totalTurnAroundTime/limitTasks;
		  
	for(index = 0; index < limitTasks; index++) {
		printf("[%s] --> Valor Inicial: %d | Valor Final: %d |  Tempo de Espera: %d | Tempo de Retorno: %d \n \n", tasks[index].taskName, tasks[index].initialValue, tasks[index].finalValue, tasks[index].waitTime, tasks[index].turnAroundTime);
	}
	

      printf("Media de tempo de espera: %.2f \n", avgWaitTime);
      printf("Media de tempo de retorno: %.2f \n", avgTAT);
      fclose(archive);
      return 0;
}

int main(){
	int option;
	printf("Qual algoritmo voce gostaria de rodar?\n");
	printf("1 - Round Robin \n2 - FCFS \n");
	scanf("%d", &option);

	switch(option){
		case 1:
			printf("\nRoundRobin \n\n");
			RoundRobin();
			break;
		case 2: 
			printf("\nFCFS \n\n");
			FCFS();
			break;
		default:
			printf("\nOpcao invalida! D:");

	}
	return  0;
}


