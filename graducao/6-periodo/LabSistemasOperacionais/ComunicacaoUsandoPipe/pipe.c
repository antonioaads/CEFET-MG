//Para compilar utilize:
//gcc -o pipe pipe.c

/**
 * Código que gera um vetor de caracteres maiúsculos aleatórios e através de pipe
 * Passa para um processo filho, que faz a contagem e passa o resutado de volta, 
 * também por PIPE.
 * 
 * Autores:
 * Antônio Augusto Diniz Sousa
 * Illyana Guimarães de Avelar
 * 
 * Baseado no codigo de:
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define READ_END	0
#define WRITE_END	1
#define SIZE_VETOR 500
#define BUSCAR_O_CARACTER 'J'

int main(void)
{
	srand(time(NULL));
	pid_t pid;
	int fd[2];
	void *buffer;
	void *bufferInicio;

	int maxSize = SIZE_VETOR + sizeof(char) + sizeof(int) + 2;

	// Criação do pipe
	if (pipe(fd) == -1) {
		fprintf(stderr,"Erro na Criação do pipe");
		return 1;
	}

	// Criação do processo Filho
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Erro no Fork");
		return 1;
	}

	//PROCESSO PAI
	if (pid > 0) {
		printf("ID do processo Pai: %d\n",getpid());
		
		sleep(1);

		//Criação do vetor de caracteres
		char vetorAleatorio[SIZE_VETOR+1];

		//Preenchimento do vetor de caracteres com algoritmos aleatórios
		for(int i = 0; i< SIZE_VETOR; i++){
			vetorAleatorio[i] = 'A' + (random() % 26);
		}
		vetorAleatorio[SIZE_VETOR] = '\0';

		//Calculo do tamanho que o buffer precisará
		int tamanhoBuffer = sizeof(char) + sizeof(int) + sizeof(vetorAleatorio);

		//Alocação dinâmica do buffer
		buffer = malloc(tamanhoBuffer);
		bufferInicio = buffer;				//salvando o início do ponteiro

		printf("Pai (%d) - O vetor Gerado foi: \n%s\n\n", getpid(), vetorAleatorio);

		//Salvando informações do vetor e o vetor na variável que será passada para o pipe
		*(char*)buffer = BUSCAR_O_CARACTER; 	//Caracter a ser buscado
		buffer += sizeof(char);					//Deslocamento
		*(int*)buffer = sizeof(vetorAleatorio); //Mandando o tamanho do vetor gerado
		buffer += sizeof(int);
		sprintf(buffer, vetorAleatorio);		//Salvando o vetor aleatório

		write(fd[WRITE_END], bufferInicio, tamanhoBuffer+1); 
		sleep(1);
		
		// Fechando a saida de escrita do PIPE
		close(fd[WRITE_END]);


		printf("Pai (%d) - Pai Esperando o resultado da contagem ...\n\n", getpid());
		read(fd[READ_END], bufferInicio, maxSize);
		int numeroDeCaracteres = *(int*)bufferInicio;	//Pegando o número que foi contado

		printf("Pai (%d) - A quantidade de caracteres %c encontrados no vetor foi: %d\n\n", getpid(), BUSCAR_O_CARACTER, numeroDeCaracteres);

		// Fechando a saida de leitura do PIPE
		close(fd[READ_END]);
	}

	//PROCESSO FILHO
	else {

		printf("ID do processo Filho: %d\n\n",getpid());

		
		printf("Filho (%d) - esperando dados do pipe ...\n\n",getpid());

		// Alocação de memória
		buffer = malloc(maxSize);
		bufferInicio = buffer;

		//Lendo o PIPE
		read(fd[READ_END], buffer, maxSize);

		char caracterParaBuscar = *(char *)buffer;
		buffer += sizeof(char);
		int tamanhoVetor = *(int *)buffer;
		buffer += sizeof(int);

		printf("Child (%d) - Efetuando contagem ...\n",getpid());

		sleep(1);

		char vetorAleatorio[tamanhoVetor+1];
		int sum = 0;
		for(int i = 0; i<tamanhoVetor; i++){
			if(*(char*)buffer != '\0'){
				if(*(char*)buffer == caracterParaBuscar) sum++;
				vetorAleatorio[i] = *(char*)buffer;
				buffer += sizeof(char);
			}
			else{
				vetorAleatorio[i] = '\0';
				break;
			}
		}
		vetorAleatorio[tamanhoVetor] = '\0';


		printf("Child (%d) - Escrevendo no pipe o resultado\n",getpid());

		// Fechando a saida de leitura do PIPE
		close(fd[READ_END]);

		*(int*)bufferInicio = sum; 
		write(fd[WRITE_END], bufferInicio, sizeof(int));

		// Fechando a saida de escrita do PIPE
		close(fd[WRITE_END]);
	}

	return 0;
}
