/*
* Software Basico - 1/2016
* Arquivo que contém funções que manipulam os frames criados
* e a stack de frames.
*/

#include "frame.h"

static struct stackFrame* topo = NULL;

//Cria uma estrutura de frame e coloca na pilha. Precisa dos bytecodes
//de uma referencia a constantPool e da classe que contém o método.
void criaFrame(cp_info* cp, classFile* classe, code_attribute* code){
	printf("Criando Frame.\n");

	//Aloca espaço para o novo frame.
	struct stackFrame* sf = NULL;
	sf =(struct stackFrame*) calloc(sizeof(struct stackFrame),1);

	if(sf == NULL){
		printf("Problema na alocação do frame\n");
	}
	sf->refFrame = (struct frame*) calloc(sizeof(struct frame),1);

	//Atualiza a pilha.
	sf->next = topo;
	topo = sf;

	//Preenche o frame com as informaçõess

	//Inicializa o pc.
	topo->refFrame->pc = 0;

	//Inicializa classe constantPool tamanho da pilha tamanho do array de ver local
	//Inicializa bytecodes.
	topo->refFrame->classe = classe;
	topo->refFrame->constant_pool = cp; 
	topo->refFrame->max_stack = code->max_stack;
	topo->refFrame->max_locals = code->max_locals;
	topo->refFrame->code_length = code->code_length;		
	topo->refFrame->code = code->code;

	//Aloca espaço para o array de var local
	topo->refFrame->fields = calloc(sizeof(uint32_t), topo->refFrame->max_locals);
	//Atualiza o frameCorrente para o frame alocado agora.
	//IMPORTANTE para que o loop de execução acesse o frameCorrente atualizado.
	frameCorrente = topo->refFrame;

	//TODO PILHA DE OPERANDOS!
}

void desalocaFrame(){
	struct stackFrame *anterior;

	//se topo->next diferente de null -> existe outros frames para executar.
	//Atualiza o frame corrente para prosseguir a execução.
	if (topo->next != NULL) {
		frameCorrente = topo->next->refFrame;
	} else {
		frameCorrente = NULL;
	}

	//Salva frame anterior.
	anterior = topo->next;
	//Desaloca frame já executado.
	free(topo->refFrame->fields);
	free(topo->refFrame);
	free(topo);

	//Atualiza topo com o proximo frame a ser executado.
	topo = anterior;

	//TODO Liberar pilha do frame desalocado.
}
