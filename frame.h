#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>
#include "leitor.h"

void criaFrame(cp_info* cp, classFile* classe, code_attribute* code);
void desalocaFrame();

/**
 * Struct que representa um frame 
 * por indicacao do professor, cada frame tem seu proprio PC
 * cada metodo ao ser executado cria um frame proprio
 */
struct frame{
	uint32_t* fields;
	cp_info* constant_pool;
	classFile* classe; //revisar conceito!
	uint16_t max_stack;
	uint16_t max_locals;
	uint32_t code_length;
	uint8_t* code;
	uint32_t pc;
};

/**
 * Struct para a pilha de frames de metodos 
 */ 
struct stackFrame{
	struct frame* refFrame;
	struct stackFrame* next;
};

//Salva o frame que está sendo executado.
struct frame *frameCorrente;

#endif
