/*

* Universidade de Brasilia

Gabriel Mesquita de Araujo 13/0009121
Gabriel
Renato
Leandro
Carlos

* Software Basico - 1/2016
* Professor: Marcelo Ladeira

* Função main do processamento do arquivo .class
* E execução das instruções -> JVM.

* compilar:			 gcc main.c -o jvm -std=c99
* executar:    		 ./jvm .class 1  //Arquivo .class com a main e 1 para printar o classfile.
*                    ./jvm .class 0  //Arquivo .class com a main e 0 para não printar o classfile.
*/

//Includes para funcionalidades necessárias.
#include "exibidor.h"
#include "instrucao.h"
#include "carregador.h"
#include "metodo.h"

//Arquivo passado via linha de comando.
char arquivo[100];

//Flag para printar no prompt - 1 printa - 0 não printa.
int printPrompt = 0;

int main(int argc, char* argv[]) {

	//Ponteiro para uma estrutura de method_info. Para começar executando
	//a main.
	method_info* Main;

	arrayClasses = NULL;

	// 1 - Inicializa as instruções implementadas pela jvm.
	newInstrucoes(1);

	// 2 - Verifica argumentos por linha de comando.
	if (argc < 2) {
		printf("Forneca o .class que contem a main: \n");
		scanf("%s", arquivo);
		getchar();

		printf("Deseja imprimir no prompt? 1 - SIM / 0 - NAO \n");
		scanf("%d", &printPrompt);
	}
	else {
		strcpy(arquivo, argv[1]);
	}

	// 3 - Carrega no array de classes o .class passado por linha de comando.
	carregaMemClasse(arquivo);

	//Se passa 1 na linha de comando imprime no prompt
	if ( printPrompt)//(argv[2] != NULL && *argv[2] == '1') ||
		for (int i = 0; i < numeroClasses; i++) {
			printf("%d\n", &arrayClasses[i]);
			imprimePrompt(arrayClasses[i]);
		}

	// 4 - Busca o método main para começar a execução.
	Main = buscaMetodoMain();

	//Se não encontrou o main o .class passado está errado.
	if (Main == NULL) {
		printf("Forneça um .class via linha de comando com o método main.");
		return 0;
	}

	// 5 - Cria frame e coloca na pilha. Passa o metodo com o bytecode
	// e a classe que contém o método com a constantPool.
	iniciaMetodo(Main, buscaClasseIndice(0));

	// 6 - Executa o método.

	return 0;
}
