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

#include "./includes/frame.h"
#include "./includes/metodo.h"
#include "./includes/instrucao.h"
#include "./includes/area_metodos.h"

extern struct frame* frameCorrente;

uint32_t numObjetos = 0;


/**
 * Função para retornar uma referencia ao metodo main do primeiro .class carregado.
 * @param void
 * @return method_info* uma referencia ao metodo main
 */
method_info* buscaMetodoMain(){
	classFile* main;
	uint16_t nome_tam,desc_tam;
	uint8_t* nome;
	uint8_t* desc;

	//Busca a classe que contém o método main. Foi a segunda classe a ser carregada.
	main = buscaClasseIndice(1);

	//Percorre o method_info em busca do method main.
	for(int i = 0; i < main->methods_count; i++){
		nome = main->constant_pool[(main->methods[i].name_index -1)].info.Utf8.bytes;

		desc = main->constant_pool[(main->methods[i].descriptor_index - 1)].info.Utf8.bytes;

		//Se encontrou método main retorna uma referencia.
		if(strcmp("main",(char *)nome) == 0){ //Nome da função
			if(strcmp("([Ljava/lang/String;)V",(char *)desc) == 0){ //Parâmetros e Retorno da main.
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
void empilhaMetodo(method_info* metodo, classFile* classe){
	/** 
 	*1 - Inicializa as instrucoes implementadas pela jvm.
 	*/
	newInstrucoes();

	/** 
 	*2 - Aloca o frame a ser executado.
 	*/
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
	//Enquanto houver instruções no attributo code.
	for(;(frameCorrente->pc) < frameCorrente->code_length;){
		//Frame corrente == NULL -> não tem mais frames na pilha.
		if(frameCorrente == NULL)
			break;

		// printf("opcode: %d\n",frameCorrente->code[frameCorrente->pc]);

		instrucao[frameCorrente->code[frameCorrente->pc]]();
	}

	desalocaFrame();
}

/**
 * Função que recebe um classFile e preenche uma estrutura de um objeto
 * que será salvo na heap (array).
 * @param referencia a um classFile.
 * @return referencia a uma estrutura que representa um objeto.
 */
objeto* criaObjeto(classFile* classe){
	objeto* objeto;

	if(numObjetos == 0){
		heap = calloc(128,sizeof(struct objeto*));
	}

	//Aloca espaço e inicializa classe do objeto.
	objeto = calloc(sizeof(objeto),1);
	objeto->classe = classe;

	//Aloca espaço para os fields.
	objeto->campos = calloc(sizeof(uint32_t), classe->fields_count);
	objeto->indiceCampos = calloc(sizeof(uint32_t), classe->fields_count);

	//Preenche o objeto com os indices dos fields.
	for(int i = 0; i < classe->fields_count; i++){
		objeto->indiceCampos[i] = classe->fields[i].name_index; 
	}

	//Coloca no heap
	//heap[numObjetos] = objeto;
	//numObjetos++;
	//retorna objeto
	return objeto;
}

/**
 * Função que recebe uma classe de busca um indice para a constant pool
 * e busca o método a ser executado. Usado geralmente nos invokes.
 * @param classe de indice
 * @param classe de busca
 * @param indice para constant pool
 * @return referencia a uma estrutura de um método
 */
method_info* buscaMetodo(classFile* indiceClasse, classFile* searchClasse, uint16_t indice){

	//Busca nome e descrição do método pelo indice fornecido
	char* name = retornaNome(indiceClasse, indiceClasse->constant_pool[indice-1].info.NameAndType.name_index);
	char* desc = retornaNome(indiceClasse, indiceClasse->constant_pool[indice-1].info.NameAndType.descriptor_index);
	char* searchName;
	char* searchDesc;
	for(int i = 0; i < searchClasse->methods_count; i++) {

		//Busca nome do metodo na searchClasse
		searchName = searchClasse->constant_pool[(searchClasse->methods[i].name_index-1)].info.Utf8.bytes;
		//Busca descrição do metodo na searchClasse	
		searchDesc = searchClasse->constant_pool[(searchClasse->methods[i].descriptor_index-1)].info.Utf8.bytes;
		
		//Compara o nome e descrição. Se for igual é o método desejado e retorna.
		if((strcmp(name,searchName) == 0) && (strcmp(desc,searchDesc) == 0)) {
			return(searchClasse->methods + i);
		}

	}
}

/**
 * Função que recebe um nome e uma descrição de um campo e encontra sua posição. 
 * @param nome da classe que possui o campo
 * @param nome do campo
 * @param descrição do campo
 * @return posição do campo no fields da classe.
 */
int32_t buscaCampo(char* className, char* name, char* desc){
	//Obtem classe pelo nome para percorrer seus fields
	classFile* classe = retornaClasseNome(className);
	//Busca nome e descrição do campo pelo indice fornecido
	uint8_t* searchName;
	uint8_t* searchDesc;
	for(int i = 0; i < classe->fields_count; i++) {

		//Busca nome do campo na searchClasse
		searchName = classe->constant_pool[(classe->fields[i].name_index-1)].info.Utf8.bytes;
		//Busca descrição do campo na searchClasse	
		searchDesc = classe->constant_pool[(classe->fields[i].descriptor_index-1)].info.Utf8.bytes;
		
		//Compara o nome e descrição. Se for igual é o campo desejado e retorna.
		if ((strcmp(name, searchName) == 0) && (strcmp(desc, searchDesc) == 0)) {
			return i;
		}

	}
}

/**
 * Função que recebe um nome de classe e a partir desse nome retorna uma referencia
 * da classe com esse nome.
 * @param nome da classe buscada
 * @return referência da classe buscada.
 */
classFile* retornaClasseNome(char* nomeClasse) {
	for (int i = 0; i < area_met.num_classes; i++) {
		if (strcmp(nomeClasse, retornaNomeClasse(area_met.array_classes[i])) == 0)
			return area_met.array_classes[i];
	}
	return NULL;
}


/**
 * Função que recebe uma classe e um método e busca pela quantidade
 * de parâmetros do método presente na descrição dos métodos pelos
 * caracteres especiais. (L,B,C,F,I,S,Z,D,J)
 * @param referencia a uma classe que contém o método
 * @param método para acesso a sua descrição
 * @return quantidade de parametros passados para a função.
 */
int32_t retornaNumeroParametros(classFile* classe, method_info* metodo) {
	int32_t numeroParametros = 0;
	uint16_t length;
	uint8_t* bytes;

	//Busca o utf8 e o tamanho correspondente da descrição do metodo.
	bytes = classe->constant_pool[(metodo->descriptor_index-1)].info.Utf8.bytes;
	length = classe->constant_pool[(metodo->descriptor_index-1)].info.Utf8.length;

	//Percorre o vetor de caracteres em busca dos caracteres especiais.
	//Percorre até o ) que significa o fim do descriptor.
	int i = 0; 
	while(i < length) {
        if(bytes[i] == ')')
			break;
		if(bytes[i] == 'L') {
			while(bytes[i] != ';') {
				i++;
			}
			numeroParametros++;
		} else if((bytes[i] == 'Z')||(bytes[i] == 'S')||(bytes[i] == 'F')|| (bytes[i] == 'I')||(bytes[i] == 'C')||(bytes[i] == 'B')) {
			numeroParametros++;
		//long e Double precisam de dois espaços.
		} else if((bytes[i] == 'D')||(bytes[i] == 'J')) {
			numeroParametros+=2;
		}
		i++;
	}
	return numeroParametros;
}
