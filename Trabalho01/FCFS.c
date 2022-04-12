#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

 typedef struct TasksFCFS {
  	char taskName[2];
  	int initialValue;
  	int finalValue;
  	int waitTime;
  	int turnAroundTime;
  	bool completed;
  } TasksFCFS;
 
int main()
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
      return 0;
}
