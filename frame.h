#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>
#include "leitor.h"

void criaFrame(cp_info* cp, classFile* classe, code_attribute* code);
void desalocaFrame();

/**
 * Struct que representa um frame a pilha de operandos da JVM
 */
typedef struct pilha_op
{
    // depth da pilha, inicialmente deve ficar em zero 
    // ja que a pilha comeca sem operandos
    int depth;
    
    // ponteiro para o array de 32 bits de tamanho max_stack 
    int32_t* operandos;  

}pilha_op;

/**
 * Struct que representa um frame 
 * por indicacao do professor, cada frame tem seu proprio PC
 * cada metodo ao ser executado cria um frame proprio
 */
typedef struct frame{
	uint32_t* fields;
	cp_info* constant_pool;
	classFile* classe; //revisar conceito!
	uint16_t max_stack;
	uint16_t max_locals;
	uint32_t code_length;
	uint8_t* code;
	uint32_t pc;
    pilha_op* pilha_op; 
}frame;


/**
 * Struct para a pilha de frames de metodos 
 */ 
struct stackFrame{
	struct frame* refFrame;
	struct stackFrame* next;
};


//Salva o frame que está sendo executado.
struct frame *frameCorrente;

//Var globar para guardar retorno de um metodo e empilhar no proximo metodo.
int32_t retorno;

void push(int32_t valor); 
int32_t pop_op();
void dumpStack();
#endif
