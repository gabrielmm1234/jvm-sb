/**
 *@file
 *@section DESCRIPTION
 *Universidade de Brasilia
 *
 *Gabriel Mesquita de Araujo 13/0009121\n
 *Gabriel 13/0009121\n
 *Renato 13/0009121\n
 *Leandro 13/0009121\n
 *Carlos 13/0009121\n\n
 *
 * Software Basico - 1/2016\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Funcao main do processamento do arquivo .class
 * e execucao das instrucoes -> JVM.
 *
 * compilar:	make\n
 * executar:	./jvm.exe .class 1  //Arquivo .class com a main e 1 para printar o classfile.\n
 *          	./jvm.exe .class 0  //Arquivo .class com a main e 0 para nao printar o classfile.\n
 *				./jvm.exe 			//Programa pede pelo .class e opcao de print\n
 */

#include "exibidor.h"
#include "instrucao.h"
#include "carregador.h"
#include "metodo.h"

/** 
 *Salva nome do arquivo passado via linha de comando.
 */
char arquivo[100];

/** 
 *Flag para printar no prompt - 1 printa - 0 nao printa.
 */
int printPrompt = 0;


/**
 * Inicio da execucao da jvm
 * @param argumentos via linha de comando. 
 * @param Primeiro argumento e o .class que contem a main
 * @param Segundo argumento e flag para printar no prompt 1-printa. 0-nao printa.
 */
int main(int argc, char* argv[]) {

	/** 
 	*Ponteiro para uma estrutura de method_info. Para comecar executando
 	*a main.
 	*/
	method_info* Main;

	arrayClasses = NULL;

	/** 
 	*1 - Inicializa as instrucoes implementadas pela jvm.
 	*/
	newInstrucoes(1);

	/** 
 	*2 - Verifica argumentos por linha de comando.
 	*/
	if (argc < 3) {
		printf("Forneca o .class que contem a main: \n");
		scanf("%s", arquivo);
		getchar();

		printf("Deseja imprimir no prompt? 1 - SIM / 0 - NAO \n");
		scanf("%d", &printPrompt);
	}
	else {
		strcpy(arquivo, argv[1]);
		if(*argv[2] == '1')
			printPrompt = 1;
	}
 
	/** 
 	*3 - Carrega no array de classes o .class passado por linha de comando.
 	*/
	carregaMemClasse(arquivo);


	/** 
 	*4 - Busca o metodo main para comecar a execucao.
 	*/
	Main = buscaMetodoMain();

	//Se nao encontrou o main o .class passado esta errado.
	if (Main == NULL) {
		printf("Forneça um .class via linha de comando com o método main.");
		return 0;
	}

	/** 
 	*5 - Cria frame e coloca na pilha. Passa o metodo com o bytecode
 	*e a classe que contem o metodo com a constantPool.
 	*/
	iniciaMetodo(Main, buscaClasseIndice(0));

	/** 
 	*6 - Executa o metodo main que esta no topo da stackFrame.
 	*/
	executaFrameCorrente();


	//Se passa 1 na linha de comando imprime no prompt
	if (printPrompt)
		for (int i = 0; i < numeroClasses; i++) {
			imprimePrompt(arrayClasses[i]);
		}

	return 0;
}
