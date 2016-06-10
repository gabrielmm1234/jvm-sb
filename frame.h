#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>
#include "leitor.h"

void criaFrame(cp_info* cp, classFile* classe, code_attribute* code);

//Por indicação do professor cada frame terá seu próprio PC
//Cada método ao ser executado cria um frame próprio.
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

//Pilha de referencias para estrutura frame.
struct stackFrame{
	struct frame* refFrame;
	struct stackFrame* next;
};

//Salva o frame que está sendo executado.
extern struct frame *frameCorrente;

#endif
