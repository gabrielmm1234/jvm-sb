/*
* Software Basico - 1/2016
* Arquivo que contém funções responsáveis por manipular os métodos que 
* serão usados nos frames.
*/

#include "frame.h"
#include "metodo.h"

//Função para retornar o método main do primeiro .class carregado.
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

//Metodo que busca os bytecodes atrelado a um método e inicia o frame
//com os bytecodes para execução.
void iniciaMetodo(method_info* metodo,classFile* classe){
	criaFrame(classe->constant_pool,classe,metodo->cd_atrb);
}