//Para compilar utilize:
//gcc -o consumer consumer.c -lrt -lm

/**
 * Código que consulta um vetor na memória dinâmica e faz a contagem de um caracter
 * específico utilizando vários processos.
 * 
 * Autores:
 * Antônio Augusto Diniz Sousa
 * Illyana Guimarães de Avelar
 * 
 * Baseado na estrutura feita por:
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
	/* INFORMAÇÕES SOBRE O VETOR A SER GERADO */

	int sizeVetor; 					//Tamanho do vetor
	const char *vetor = "vetor"; 	//Nome na memoria compartilhada

	/* INFORMAÇÕES SOBRE O ESPAÇO DE MEMÓRIA PAR INFO */

	const int sizeInfo = 3*sizeof(int) + sizeof(char); 	//Tamanho desse espaço
	const char *info = "info";		//Nome na memoria compartilhada
	int processos; 					//Quantidade de processos filhos que deverá ser gerado
	char buscarLetra; 				//letra a ser buscada
	

	int shm_fd;
	void *ptr;
	void *ptr_count;

	/* INICIANDO BUSCA DAS INFORMAÇÕES */

	// Acessando memoria compartilhada de informações
	shm_fd = shm_open(info, O_RDWR, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	ptr = mmap(0,sizeInfo, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

	//Buscando informações do vetor na memoria compartilhada de info
	processos = *(int*)ptr;
	ptr += sizeof(int);		//Deslocamento
	buscarLetra = *(char*)ptr;
	ptr += sizeof(char);	//Deslocamento
	sizeVetor = *(int*)ptr;
	ptr += sizeof(int);	//Deslocamento
	

	ptr_count = ptr;
	
	printf("Numero de processos: %d\n", processos);
	printf("Caracter a buscar: %c\n", buscarLetra);
	printf("Tamanho do Vetor: %d\n", sizeVetor);

	//sleep(60);

	/* INICIANDO BUSCA DO VETOR */
	
	// Acessando memoria compartilhada do vetor
	shm_fd = shm_open(vetor, O_RDONLY, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	ptr = mmap(0,sizeVetor, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

	printf("O vetor lido foi: \n%s\n",(char*)ptr);


	//Criação do vetor de caracteres
	char vetorAleatorio[sizeVetor];
	for(int i = 0; i<sizeVetor; i++){
		if(*(char*)ptr != '\0'){
			vetorAleatorio[i] = *(char*)ptr;
			ptr += sizeof(char);
		}
		else break;
	}

	printf("\n");

	int retval,i, contagem_total = 0, limite_inferior = 0, limite_superior = 0;

	int espacamento = ceil(sizeVetor/processos);

	for (i=0;i<processos;i++){
		limite_inferior = limite_superior;
		limite_superior += espacamento;
		if(limite_superior>sizeVetor) limite_superior = sizeVetor;
		retval = fork () ;
		if (retval == 0) break; //se processo filho			
	}
	if ( retval == 0 ){
		int sum = 0;
		for(int j = limite_inferior; j<limite_superior; j++){
			if(vetorAleatorio[j] == buscarLetra) sum++;
		}
		exit(sum);
	}
	else{
		for (i=0;i<processos;i++){
			int contagem;
			wait(&contagem);

			printf("Contagem parcial: %d\n", contagem>>8);
			contagem_total += contagem>>8;
		}
		printf("\nContagem Total: %d\n", contagem_total);
		*(int*)ptr_count = contagem_total;
	}
	/* remove the shared memory segment */
	if (shm_unlink(vetor) == -1) {
		printf("Error removing %s\n",vetor);
		exit(-1);
	}
	return 0;
}
