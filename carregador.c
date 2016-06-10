/*
* Software Basico - 1/2016
* Arquivo que contém funções para carregar classes nas estruturas
* adequadas.
*/

#include "carregador.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

classFile** arrayClasses;
int16_t numeroClasses = 0;

int32_t carregaMemClasse(char* nomeClass){
	int aux;

	//Se ja esta carregado retorna posição no array de classes.
	for (int32_t i = 0; i < numeroClasses; i++) {
		if (strcmp(nomeClass, retornaNomeClasse(arrayClasses[i])) == 0)
			return i;
	}

	//Se não está carregado carrega e salva no array de classes.

	printf("Carregando classe: %s\n",nomeClass);

	//uma classe nova vai entrar na lista de classes carregadas.
	numeroClasses++;
	aux = numeroClasses;

	classFile** arrayClassesTemp = NULL;

	//Realoca o tamanho do vetor para adicionar a nova classe carregada.
	//Classes previamente carregas não são perdidas com o realloc.
	arrayClassesTemp = (classFile**) realloc(arrayClasses, (aux*sizeof(classFile *)));
	//printf("ponteiro tempo: %d\n",*arrayClassesTemp);

	arrayClasses = arrayClassesTemp;
	arrayClasses[aux-1] = leitorClasse(nomeClass);

	return aux - 1;

}

// Acessa a constant pool no campo bytes a partir do index da classe e 
// retorna o nome da classe.
// Necessaria para saber se classe ja foi carregada ou não.
char* retornaNomeClasse(classFile* classe){
	uint16_t thisClass = classe->this_class;
	uint16_t nameIndex = (classe->constant_pool[thisClass]).info.Class.name_index;

	int i;
	char* retorno = (char*) malloc((classe->constant_pool[nameIndex]).info.Utf8.length + 1);

	// Percorre o bytes na constant pool e salva no retorno.
	for (i = 0; i < ( classe->constant_pool[nameIndex]).info.Utf8.length; i++) {
		retorno[i] = (char) (classe->constant_pool[nameIndex]).info.Utf8.bytes[i];
	}

	// \0 no final do nome da classe a ser retornada
	retorno[i] = '\0';

	return retorno;
}

//Função que retorna uma referencia a uma classFile de acordo com o indice.
//Util para encontrar a classe da main no inicio do processamento.
classFile* buscaClasseIndice(int indice){
	return indice >= numeroClasses ? NULL : arrayClasses[indice];
}