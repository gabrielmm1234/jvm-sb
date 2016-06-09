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
#include "metodo.h"

char arquivo[100];
int printPrompt = 0;

int main(int argc, char* argv[]){

	//Ponteiro para uma estrutura de method_info.
	method_info* Main;	

	// 1 - Inicializa as instruções implementadas pela jvm.
	newInstrucoes();

	// 2 - Verifica argumentos por linha de comando.
	if(argc < 2){
		printf("Forneça o .class que contém a main: \n");
		scanf ("%s", arquivo);
		getchar();

		printf("Deseja imprimir no prompt? 1 - SIM / 0 - NAO \n");
		scanf("%d", &printPrompt);
	}else{
		strcpy (arquivo, argv[1]);
	}

	// 3 - Carrega no array de classes o .class passado por linha de comando.
	carregaMemClasse(arquivo);

	// 4 - Busca o método main para começar a execução.
	Main = buscaMetodoMain();

	//Se não encontrou o main o .class passado está errado.
	if(Main == NULL){
		printf("Forneça um .class via linha de comando com o método main.");
		return 0;
	}

	// 5 - Cria frame e coloca na pilha. Passa o metodo com o bytecode
	// e a classe que contém o método com a constantPool.
	iniciaMetodo(Main,buscaClasseIndice(0));

	// 6 - Executa o método.

	//Se passa 1 na linha de comando imprime no prompt
	if((argv[2] != NULL && *argv[2] == '1') || printPrompt)
		for(int i = 0; i < numeroClasses; i++)
		        imprimePrompt(arrayClasses[i]);

	return 0;
}