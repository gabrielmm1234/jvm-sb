/**
 *@file
 *@section DESCRIPTION
 *Universidade de Brasilia
 *
 *Gabriel Mesquita de Araujo 13/0009121\n
 *Gabriel Ferreira Silva 14/0140131\n
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
 * para compilar:	make clean && make\n
 * para executar:	./jvm.exe .class 1  //Arquivo .class com a main e 1 para printar o classfile.\n
 *                	./jvm.exe .class 0  //Arquivo .class com a main e 0 para nao printar o classfile.\n
 *			    	./jvm.exe 			//Programa pede pelo .class e opcao de print\n
 */

#include "./includes/exibidor.h"
#include "./includes/instrucao.h"
#include "./includes/carregador.h"
#include "./includes/metodo.h"


 #define arqSize 100

/** 
 *Salva nome do arquivo passado via linha de comando.
 */
char* arquivo;

/** 
 *Flag para printar no prompt - 1 printa - 0 nao printa.
 */
int printPrompt = 0;


/**
 * Inicio da execucao da jvm
 * @param argumentos passados via linha de comando. 
 * @param Primeiro argumento eh o .class que contem a main
 * @param Segundo argumento eh flag para printar no prompt 1-printa. 0-nao printa.
 */
int main(int argc, char* argv[]) {

	arquivo = calloc(arqSize,sizeof(char));

	/** 
 	*Ponteiro para uma estrutura de method_info. Para comecar executando
 	*a main.
 	*/
	method_info* Main;

	/** 
 	*1 - Verifica argumentos por linha de comando.
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
 	*2 - Carrega no array de classes o object.class.
 	*/
 	carregaObjectClasse("java/lang/Object");
 
	/** 
 	*3 - Carrega no array de classes o .class passado por linha de comando.
 	*/
	carregaMemClasse(arquivo);
	classFile* mainClass = buscaClasseIndice(1);

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
	empilhaMetodo(Main, mainClass);

	/** 
 	*6 - Executa o metodo main que esta no topo da stackFrame.
 	*/
	executaFrameCorrente();


	//Se passa 1 na linha de comando imprime no prompt
	if (printPrompt)
		for (int i = 1; i < area_met.num_classes; i++)
			imprimePrompt(area_met.array_classes[i]);

	return 0;
}
