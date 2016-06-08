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

struct vetor{
	uint32_t ref;
	uint32_t size;
};

struct vetor* vetorLength; 
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

	// 4 - Abre arquivo passado via linha de comando
	FILE* file;
	file = fopen(arquivo, "rb");

	if(file == NULL){
		printf("Arquivo não encontrado! Erro ao abrir o arquivo!\n");
		return 0;
	}

	//Aloca memória para a estrutura do .class
	classFile* cf = (classFile*) malloc(sizeof(classFile));

	//Le informações gerais.
	generalInfo(cf,file);

	//Le a constant pool
	constantPool(cf,file);

	//le informações gerais após a constant pool
	secondGeneralInfo(cf,file);
	//Se passa 1 na linha de comando imprime no prompt
	if((argv[2] != NULL && *argv[2] == '1') || printPrompt)
		imprimePrompt(cf);
	
	//liberando ponteiros.
	free(file);
	free(cf);
	return 0;
}