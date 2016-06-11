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
 * Arquivo que contém funções responsaveis por manipular os metodos que serao usados nos frames
 * 
 * 
 */

#include "frame.h"
#include "metodo.h"
#include "instrucao.h"

extern struct frame* frameCorrente;

/**
 * Função para retornar uma referencia ao metodo main do primeiro .class carregado.
 * @param void
 * @return method_info* uma referencia ao metodo main
 */
method_info* buscaMetodoMain(){
	classFile * main;
	uint16_t nome_tam,desc_tam;
	uint8_t* nome;
	uint8_t* desc;

	//Busca a classe que contém o método main. Foi a primeira classe a ser carregada.
	main = buscaClasseIndice(0);

	printf("Buscando método main para inicio da execução\n");

	//Percorre o method_info em busca do method main.
	for(int i = 0; i < main->methods_count; i++){
		nome = main->constant_pool[(main->methods[i].name_index -1 )].info.Utf8.bytes;

		desc = main->constant_pool[(main->methods[i].descriptor_index - 1)].info.Utf8.bytes;

		//Se encontrou método main retorna uma referencia.
		if(strcmp("main",(char *)nome) == 0){ //Nome da função
			if(strcmp("([Ljava/lang/String;)V",(char *)desc) == 0){ //Parâmetros e Retorno da main.
				printf("Método main encontrado\n");
				return &(main->methods[i]);
			}
		}
	}

	//Se não encontra não possui método main na classe carregada.
	printf("Método main não encontrado.");
	return NULL;
}

/**
 * Funcao para iniciar um metodo
 * @param method_info* uma referencia ao metodo em questao 
 * @param classFile* uma referencia a estrutura da classe 
 * @return void
 */
void iniciaMetodo(method_info* metodo, classFile* classe){
	criaFrame(classe->constant_pool,classe,metodo->cd_atrb);
}

/**
 * Percorre os bytecodes do metodo do ultimo frame alocado e vai executando instrucao 
 * a instrucao ateh o metodo acabar
 * @param void
 * @return void
 */
void executaFrameCorrente(){

	//Loop que percorre o frame e executa instrução a instrução
	//Enquanto pc for menor que o tamanho do code e o frame foi desalocado(terminado)
	while((frameCorrente->pc) < frameCorrente->code_length && frameCorrente != NULL) {
		printf("opcode: %d\n",frameCorrente->code[frameCorrente->pc]);
		executarInstrucoes(frameCorrente->code[frameCorrente->pc]);
	}
	desalocaFrame();
}
