#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 8000


void SalvaMatriz(int Altura, int Largura, int* M, char* Titulo, char* NomeArquivo)
{
	int L, C; //Linha e Coluna
	
	FILE *fp = fopen(NomeArquivo, "w");
	if( fp == NULL)
	{
		printf("\n::: Erro abrindo arquivo '%s''!\n", NomeArquivo);
		exit(EXIT_FAILURE);
	}

    fprintf(fp, " %s \n", Titulo);
    for(L = 0; L < Altura; L++)
    {
        for(C = 0; C < Largura; C++)
        {
            fprintf(fp, " %2d ", M[L * Altura + C]);
        }
        fprintf(fp, "\n");
    }	
    
    fclose(fp);
	
}

void MostraMatriz(int Altura, int Largura, int* M, char* Titulo)
{
    int L, C; //Linha e Coluna

    printf(" %s \n", Titulo);
    for(L = 0; L < Altura; L++)
    {
        for(C = 0; C < Largura; C++)
        {
            printf(" %2d ", M[L * Altura + C]);
        }
        printf("\n");
    }
}

void PreencheMatriz(int Altura, int Largura, int* M, int Valor)
{
    int L, C; //Linha e Coluna

    for(L = 0; L < Altura; L++)
    {
        for(C = 0; C < Largura; C++)
        {
            M[L * Altura + C] = Valor;
        }
    }

}

int main()
{

    int* MatrizA = (int*)malloc(sizeof(int) * N * N);
    if ( MatrizA == NULL )
    {
        printf("\nErro alocando memoria! \n");
        exit( EXIT_FAILURE );
    }

    int* MatrizB = (int*)malloc(sizeof(int) * N * N);
    if ( MatrizB == NULL )
    {
        printf("\nErro alocando memoria! \n");
        exit( EXIT_FAILURE );
    }

    int* MatrizC = (int*)malloc(sizeof(int) * N * N);
    if ( MatrizC == NULL )
    {
        printf("\nErro alocando memoria! \n");
        exit( EXIT_FAILURE );
    }
 //Aloca na memória, determina que o tamanho dela é N * N, e verifica se não é null, ou seja, tem tamanho definido.
 
	printf("::: Matrix Multiplication \n");
	printf("::: Width: %d | Height: %d | Total Size: %d \n", N, N, N*N);
	printf("::: Preenchendo as matrizes... ");

    PreencheMatriz(N, N, MatrizA, 1);
    PreencheMatriz(N, N, MatrizB, 3);
    PreencheMatriz(N, N, MatrizC, 0);
    //Função que vai preencher a matriz (L,C, qual a matriz, valor que vai ser inserido nela)

	printf("Done! Now calculating...\n");
    //MostraMatriz(N, N, MatrizA, " Matriz A ");
    //MostraMatriz(N, N, MatrizB, " Matriz B ");
     MostraMatriz(N, N, MatrizC, " Matriz C ");

    int L, C, K;

    // conta o tempo de processamento
    clock_t tempo;
    tempo = clock();

    //C = A . B
    for(L=0; L<N; L++)
    {
        for(C=0; C<N; C++)
        {
            for(K=0; K<N; K++)
            {
              // MatrizC[L * N + C] += MatrizA[L * N + K] * MatrizB[L * N + K];
             MatrizC[L * N + C] += MatrizA[K * N + C] * MatrizB[K * N + C];
               // MatrizC[L * N + C] += MatrizA[L * N + K] * MatrizB[K * N + C];
             // MatrizC[L * N + C] += MatrizA[K * N + C] * MatrizB[L * N + K];
            }
        }
    }

	clock_t final = clock();
	double tempoProcessamento = ((double)(final-tempo)) / (double)(CLOCKS_PER_SEC);
	
	printf("Calculation is done! Now saving data on the disc...\n");
    //MostraMatriz(N, N, MatrizC, " Matriz C ");
    printf("Saving Matriz A on disc...\n");
	//SalvaMatriz(N, N, MatrizA, "::: Matriz A :::", "matrizA.txt");
    printf("Saving Matriz B on disc...\n");
	//SalvaMatriz(N, N, MatrizB, "::: Matriz B :::", "matrizB.txt");
    printf("Saving Matriz C on disc...\n");
	//SalvaMatriz(N, N, MatrizC, "::: Matriz C :::", "matrizC.txt");
    
    printf("\nAll done! Tempo de processamento: %.2f segundos.\n", tempoProcessamento);
    return 0;
}
 

