/*
* Software Basico - 1/2016
* Professor: Marcelo Ladeira
* Função main do processamento do arquivo .class
* E execução das instruções -> JVM.
* compilar:			$ gcc main.c -o jvm -std=c99
* executar:    		$ ./jvm .class 1  //Arquivo .class com a main e 1 para printar o classfile.
*                   $ ./jvm .class 0  //Arquivo .class com a main e 0 para não printar o classfile.
*/


#include "leitor.h"
#include "exibidor.h"
#include "instrucao.h"
#include "carregador.h"

struct vetor{
	uint32_t ref;
	uint32_t size;
};

//Vetor que contém o size de cada vetor.
struct vetor* vetorLength; 
//Numero de vetores alocados.
uint32_t numbervetor;


char arquivo[100];
int printPrompt = 0;

int main(int argc, char* argv[]){

	// 1 - Inicializa o vetor de classes - Inicialmente nenhuma classe foi carregada.
	vetorLength = NULL;
	numbervetor = 0;

	// 2 - Inicializa as instruções implementadas pela jvm.
	newInstrucoes();

	// 3 - Verifica argumentos por linha de comando.
	if(argc < 2){
		printf("Forneça o .class que contém a main: \n");
		scanf ("%s", arquivo);
		getchar();

		printf("Deseja imprimir no prompt? 1 - SIM / 0 - NAO \n");
		scanf("%d", &printPrompt);
	}else{
		strcpy (arquivo, argv[1]);
	}

	carregaMemClasse(arquivo);

	//Se passa 1 na linha de comando imprime no prompt
	if((argv[2] != NULL && *argv[2] == '1') || printPrompt)
		for(int i = 0; i < numeroClasses; i++)
		        imprimePrompt(arrayClasses[i]);

	return 0;
}