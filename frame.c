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

	struct stackFrame* sf = NULL;
	sf =(struct stackFrame*) calloc(sizeof(struct stackFrame),1);
	if(sf == NULL){
		printf("deu ruim\n");
	}
	sf->refFrame = (struct frame*) calloc(sizeof(struct frame),1);

}
