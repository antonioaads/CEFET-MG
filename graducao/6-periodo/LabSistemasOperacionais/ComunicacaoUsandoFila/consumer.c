//Para compilar utilize:
//gcc -o consumer consumer.c -lrt -lm

/**
 * Código que consulta um vetor na fila e faz a contagem de um caracter
 * específico.
 * 
 * Autores:
 * Antônio Augusto Diniz Sousa
 * Illyana Guimarães de Avelar
 * 
 * Baseado na estrutura disponível em:
 * http://stackoverflow.com/questions/3056307/how-do-i-use-mqueue-in-a-c-program-on-a-linux-based-system
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>
#include "common.h"

#define QUEUE_NAME  "/test_queue"
//MELHORIA PROPOSTA: Estava dando problema quando eu deixava esse tamanho dinâmico.
#define MAX_SIZE    1024

int main(int argc, char **argv)
{
	mqd_t mq;
	struct mq_attr attr;
	void *buffer;
	buffer = malloc(MAX_SIZE);
	void *bufferInicio = buffer; //variável para salvar o início do buffer

	attr.mq_flags = 0; 
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 1024;
	attr.mq_curmsgs = 0;
	
	mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
	CHECK((mqd_t)-1 != mq);
	
	//Loop para poder ler varias estruturas
	do{
		buffer = bufferInicio;
		printf("1 - Esperando dados de entrada... \n");
		ssize_t bytes_read;
		bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
		CHECK(bytes_read >= 0);

		char caracterParaBurcar = *(char*)buffer;
		buffer += sizeof(char);
		int tamanhoVetor = *(int*)buffer;
		buffer += sizeof(int);

		//Leitura do vetor de caracteres que foi gerado pelo producer e contagem
		printf("2 - Efetuando a contagem... \n");
		char vetorAleatorio[tamanhoVetor+1];
		int sum = 0;
		for(int i = 0; i<tamanhoVetor; i++){
			if(*(char*)buffer != '\0'){
				if(*(char*)buffer == caracterParaBurcar) sum++;
				vetorAleatorio[i] = *(char*)buffer;
				buffer += sizeof(char);
			}
			else{
				vetorAleatorio[i] = '\0';
				break;
			}
		}
		vetorAleatorio[tamanhoVetor] = '\0';

		//Salvando a contagem no buffer que será enviado
		*(int*)bufferInicio = sum; 

		//Mandando o resultado da contagem
		printf("3 - Enviando Resultado... \n\n");
		CHECK(0 <= mq_send(mq, bufferInicio, 1024, 0));
		CHECK( mq_getattr(mq, &attr) != -1);

	}while(1);

	return 0;
}
