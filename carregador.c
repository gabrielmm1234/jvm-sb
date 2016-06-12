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
 * Arquivo que contém funções para carregar classes nas estruturas adequadas.
 * 
 */

#include "carregador.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** 
 *Array de referencia a classFiles. Declarado no carregador.h
 */
classFile** arrayClasses;
area_metodos area_met; 

/** 
 *Quantidade de classes já carregadas pelo carregador.
 */
bool ja_carregou = false;

/**
 * É passado o nome do arquivo .class a ser carregado.\n
 * 
 * Se ainda não foi carregado carrega no array de classes.
 * @param nome do arquivo ".class" a ser carregado no array de classes.
 * @return posição da classe alocada no array de classes.
 */
int32_t carregaMemClasse(char* nomeClass){
	int aux;

    // se eh a primeira classe a ser carregada
    if (ja_carregou == false)
    {
        area_met.num_classes = 0;
        ja_carregou = true; 
    }
	//Se ja esta carregado retorna posição no array de classes.
	for (int32_t i = 0; i < area_met.num_classes; i++) {
		if (strcmp(nomeClass, retornaNomeClasse(area_met.array_classes[i])) == 0)
			return i;
	}

	//Se não está carregado carrega e salva no array de classes.

	printf("Carregando classe: %s\n",nomeClass);

	//uma classe nova vai entrar na lista de classes carregadas.
	area_met.num_classes++;
	aux = area_met.num_classes;

	classFile** arrayClassesTemp = NULL;

	//Realoca o tamanho do vetor para adicionar a nova classe carregada.
	//Classes previamente carregas não são perdidas com o realloc.
	arrayClassesTemp = (classFile**) realloc(arrayClasses, (aux*sizeof(classFile *)));
	//printf("ponteiro tempo: %d\n",*arrayClassesTemp);

	arrayClasses = arrayClassesTemp;
	arrayClasses[aux-1] = leitorClasse(nomeClass);

    area_met.array_classes = (classFile**) calloc(1, sizeof(classFile*));
    area_met.array_classes = arrayClasses; 

	if(arrayClasses[aux -1] == NULL)
		printf("Erro ao carregar classe!\n");

	return aux - 1;

}


/**
 *Acessa a constant pool no campo bytes a partir do index da classe e 
 *retorna o nome da classe.\n
 *Necessaria para saber se classe ja foi carregada ou não.
 * @param Estrutura classFile de que se deseja obter o nome.
 * @return nome da classe fornecida.
 */
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

/**
 *Função que retorna uma referencia a uma classFile de acordo com o indice.\n
 *Util para encontrar a classe da main no inicio do processamento.
 * @param Posicao a ser acessada no array de classes.
 * @return Referencia a um classFile ou NULL caso nao exista a referencia 
 */
classFile* buscaClasseIndice(int indice){
	return indice >= area_met.num_classes ? NULL : area_met.array_classes[indice];
}
