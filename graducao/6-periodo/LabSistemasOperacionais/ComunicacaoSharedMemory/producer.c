//Para compilar utilize:
//gcc -o producer producer.c -lrt

/**
 * Código que gera um vetor de caracteres maiúsculos aleatórios e insere em uma memória
 * compartilhada. Juntamente, gera uma outra memoria compartilhada que contem as informações
 * do vetor gerado.
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

#include <time.h>
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
	srand(time(NULL));

	/* INFORMAÇÕES SOBRE O VETOR A SER GERADO */

	const int sizeVetor = 200; 	//Tamanho do vetor
	const char *vetor = "vetor"; 	//Nome na memoria compartilhada

	/* INFORMAÇÕES SOBRE O ESPAÇO DE MEMÓRIA PAR INFO */

	const int sizeInfo = 3*sizeof(int) + sizeof(char); 	//Tamanho desse espaço
	const int processos = 5; 		//Quantidade de processos filhos que deverá ser gerado
	const char buscarLetra = 'A'; 	//letra a ser buscada
	const char *info = "info";		//Nome na memoria compartilhada


	int shm_fd;
	void *ptr, *start;

	//Alocação da memória de dados
	shm_fd = shm_open(vetor, O_CREAT | O_RDWR, 0666);

	ftruncate(shm_fd,sizeVetor);

	ptr = mmap(0,sizeVetor, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	//Criação do vetor de caracteres
	char vetorAleatorio[sizeVetor];

	//Preenchimento do vetor de caracteres com algoritmos aleatórios
	for(int i = 0; i< sizeVetor-1; i++){
		vetorAleatorio[i] = 'A' + (random() % 26);
	}

	//Grava o vetor gerado na memoria compartilhada
	sprintf(ptr, vetorAleatorio);

	printf("O vetor Gerado foi: \n%s\n\n",(char*)ptr);


	//Alocação da memória de informações
	shm_fd = shm_open(info, O_CREAT | O_RDWR, 0666);

	ftruncate(shm_fd,sizeInfo);

	ptr = mmap(0,sizeInfo, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	//salva o início do ponteiro
	start = ptr;

	//Considerou-se a seguinte estrututa para a memória de informações:
	// Numero de processos - Caracter a ser buscado - Tamanho do vetor

	//Salvando as informações conforme estrutura
	*(int*)ptr = processos;
	ptr += sizeof(int);		//Deslocamento
	*(char*)ptr = buscarLetra;
	ptr += sizeof(char);	//Deslocamento
	*(int*)ptr = sizeVetor;
	ptr += sizeof(int);		//Deslocamento
	*(int*)ptr = -1;

	while(*(int*)ptr == -1){
		printf("Aguardando receber quantidade ...\n");
		sleep(10);
	}
	
	printf("A quantidade de %c no vetor é: %d\n", buscarLetra, *(int*)ptr);

	/* remove the shared memory segment */
	if (shm_unlink(info) == -1) {
		printf("Error removing %s\n",info);
		exit(-1);
	}
	return 0;
}
