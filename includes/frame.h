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
	int32_t* fields; //Array de variaveis locais
	cp_info* constant_pool;
	classFile* classe;
	uint16_t max_stack;
	uint16_t max_locals;
	uint32_t code_length;
	uint8_t* code; //Bytecode
	uint32_t pc; //Program counter
    pilha_op* pilha_op; //Pilha de operandos
}frame;


/**
 * Struct para a pilha de frames de metodos 
 */ 
struct stackFrame{
	frame* refFrame;
	struct stackFrame* next;
};

//Struct que representa nosso array.
//Contem uma referencia ao array. E seu respectivo tamanho.
typedef struct array{
	int32_t referencia;
	int32_t tamanho;
}vector;


//Salva o frame que está sendo executado.
struct frame* frameCorrente;

//Array de arrays :)
vector* arrayVetores;

//Var com a quantidade de arrays no arrayVetores.
int32_t qtdArrays;

//Var globar para guardar retorno de um metodo e empilhar no proximo metodo.
int32_t retorno;
int32_t retAlta,retBaixa;

//Flag para empilhar 1 slot ou 2(double e long).
int8_t flagRet;

void push(int32_t valor); 
int32_t pop_op();
void dumpStack();
void dumpFields();
void pushFrame(cp_info*, classFile*, code_attribute*,struct stackFrame*);
void popFrame();
void mostra_profundidade(int i);

//Refencia ao topo da pilha de frames. Essencial para Empilhar e desempilhar os frames.
static struct stackFrame* topo = NULL;

#endif
