
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define limite_superior 256000

void gerarNumeros(int* v, int n){

	srand(time(NULL));
	
	for(int i=0; i<n; i++){
		v[i] = (rand() % (limite_superior-1))+1;
	}
}

void separar(int** faixas, int*v, int n, int n_faixas){
	
	int dif = n/n_faixas;
	int limite_inicial = 0;
	int limite_final = dif;
	int tam_faixas = 0;
	int count = 0;

	//tam_faixas = (int*) malloc(n_faixas * sizeof(int));

	for(int i=0; i<n_faixas; i++){
		//Analisa se é a última faixa
		if(i == (n_faixas-1)) limite_final = n;

		for(tam_faixas = 0; v[count] < limite_final; tam_faixas++, count++);

		faixas[i] = (int*) malloc(tam_faixas * sizeof(int));

		for(int j=(count-tam_faixas), k = 0; v[j] < limite_final; j++,k++){
			faixas[i][k] = v[j];
		}

		limite_inicial = limite_final;
		limite_final += dif;	
	}	
}

void imprimir(int* v, int n){
	for(int i=0; i<n; i++){
		printf("%d", v[i]);
		if((i%10)!=9) printf("\t");
		else printf("\n");
	}
	printf("\n");
}

void imprimirFaixas(int** faixas, int n, int n_faixas){

	for(int i=0; i<n_faixas; i++){
		printf("\nImprimindo faixa %d\n", i);

		for(int k=0; faixas[i][k] != NULL; k++){
			printf("%d", faixas[i][k]); 
			if((k%10)!=9) printf("\t");
			else printf("\n");
		}
		printf("\n");
	}
}

void mostrarFrequencia(int** faixas, int n, int n_faixas){
	int dif = n/n_faixas;
	int limite_inicial = 0;
	int limite_final = dif;
	int tam_faixas = 0;

	printf("\n");
	for(int i=0; i<n_faixas; i++){
		for(int k=0; faixas[i][k] != NULL; k++){
			tam_faixas++; 
		}
		if(i == (n_faixas-1)) limite_final = n;

		printf("Faixa %d a %d - Frequencia = %d\n", limite_inicial,limite_final, tam_faixas);

		tam_faixas = 0;
		limite_inicial = limite_final;
		limite_final += dif;	
	}
}

void ordenar(int* v, int n){
	mergeSort(v,0,n-1);
}

void mergeSort(int *vetor, int posicaoInicio, int posicaoFim) {
    int i, j, k, metadeTamanho, *vetorTemp;
    if(posicaoInicio == posicaoFim) return;
    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;

    mergeSort(vetor, posicaoInicio, metadeTamanho);
    mergeSort(vetor, metadeTamanho + 1, posicaoFim);

    i = posicaoInicio;
    j = metadeTamanho + 1;
    k = 0;
    vetorTemp = (int *) malloc(sizeof(int) * (posicaoFim - posicaoInicio + 1));

    while(i < metadeTamanho + 1 || j  < posicaoFim + 1) {
        if (i == metadeTamanho + 1 ) { 
            vetorTemp[k] = vetor[j];
            j++;
            k++;
        }
        else {
            if (j == posicaoFim + 1) {
                vetorTemp[k] = vetor[i];
                i++;
                k++;
            }
            else {
                if (vetor[i] < vetor[j]) {
                    vetorTemp[k] = vetor[i];
                    i++;
                    k++;
                }
                else {
                    vetorTemp[k] = vetor[j];
                    j++;
                    k++;
                }
            }
        }

    }
    for(i = posicaoInicio; i <= posicaoFim; i++) {
        vetor[i] = vetorTemp[i - posicaoInicio];
    }
    free(vetorTemp);
}

void main(){
	
	int n = limite_superior;
	int n_faixas = 8;

	int* v = (int *) malloc(n * sizeof(int));
	int** faixas = (int**)malloc(n_faixas * sizeof(int*)); //Aloca um Vetor de Ponteiros

	gerarNumeros(v,n);
	//printf("Números aleatórios gerados:\n");
	//imprimir(v,n);
	//printf("\nNúmeros aleatórios ordenandos\n");
	ordenar(v, n);
	//imprimir(v,n);
	separar(faixas, v, n, n_faixas);
	//imprimirFaixas(faixas, n, n_faixas);
	mostrarFrequencia(faixas, n, n_faixas);

}


