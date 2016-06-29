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
 * Arquivo que contém funcoes que manipulam os frames criados e a stack de frames
 * 
 * 
 */

#include "./includes/frame.h"

/**
 * Cria uma estrutura de pilha e coloca no frame. Sao necessarios uma referencia a classe q contem o metodo\n
 * os bytecodes e uma referencia a constant Pool\n
 * @param cp_info* uma referencia a constant pool 
 * @param classFile* uma referencia a classe 
 * @param code* uma referencia ao atributo code do metodo que estamos 
 * @return void 
 */
void criaFrame(cp_info* cp, classFile* classe, code_attribute* code){
	//Aloca espaço para o novo frame.
	struct stackFrame* sf = NULL;
	sf =(struct stackFrame*) calloc(sizeof(struct stackFrame),1);

	if(sf == NULL){
		printf("Problema na alocação do frame\n");
	}

	sf->refFrame = (struct frame*) calloc(sizeof(struct frame),1);

	//Empilha o frame na pilha de frames.
	pushFrame(cp,classe,code,sf);
}

/**
 * Função que empilha na nossa pilha de frames um novo frame alocado. 
 * @param cp_info* uma referencia a constant pool 
 * @param classFile* uma referencia a classe 
 * @param code* uma referencia ao atributo code do metodo que estamos 
 * @param struct stackFrame* referencia para a pilha de frames.
 * @return void 
 */
void pushFrame(cp_info* cp, classFile* classe, code_attribute* code,struct stackFrame* sf){
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
	topo->refFrame->max_stack = 2 * code->max_stack + 110;
	topo->refFrame->max_locals = code->max_locals;
	topo->refFrame->code_length = code->code_length;		
	topo->refFrame->code = code->code;

	//Aloca espaço para o array de var local
	topo->refFrame->fields = calloc(sizeof(uint32_t), topo->refFrame->max_locals);

    // aloca espaco para a pilha de operandos e poe indice na pilha na posicao correta
    topo->refFrame->pilha_op = calloc(1, sizeof(pilha_op));
    topo->refFrame->pilha_op->operandos = calloc(topo->refFrame->max_stack, sizeof(uint32_t));
    topo->refFrame->pilha_op->depth = 0; // inicialmente a pilha esta vazia 

	//Atualiza o frameCorrente para o frame alocado agora.
	//IMPORTANTE para que o loop de execução acesse o frameCorrente atualizado.
	frameCorrente = topo->refFrame;
}

/**
 * Função que desempilha na nossa pilha de frames o frame que terminou a execução.
 * desempilha e atualiza o estado da pilha. Se não tem mais frames na pilha garante
 * que a execução termine. 
 */
void popFrame(){
	struct stackFrame *anterior;
	//se topo->next diferente de null -> existe outros frames para executar.
	//Atualiza o frame corrente para prosseguir a execução.
	if (topo->next != NULL) {
		frameCorrente = topo->next->refFrame;

		//Empilha valor de retorno do frame anterior na pilha do proximo frame.
		//Salvo numa var global.
		if(flagRet == 1){
			push(retorno);
		}else if(flagRet == 2){
			push(retAlta);
			push(retBaixa);
		}

		flagRet = 0;
		
	} else {
		frameCorrente = NULL;
	}

	//Salva frame anterior.
	anterior = topo->next;

	//Desaloca frame já executado.
    free(topo->refFrame->pilha_op->operandos);
    free(topo->refFrame->pilha_op);
    free(topo->refFrame->fields);
	free(topo->refFrame);
	free(topo);

	//Atualiza topo com o proximo frame a ser executado.
	topo = anterior;
}

/**
 * Funcao que desaloca o topo da pilha de frames de metodos.
 * @param void
 * @return void 
 */
void desalocaFrame(){
	popFrame();
}

/**
 * funcao para dar um push na pilha de operandos, 
 * @param frame* frame_corrente, uma referencia ao frame atual
 * @param int32_t valor, o valor a ser colocado na pilha
 * @return void
 */
void push(int32_t valor)
{	
	//printf("depth: %d\n",frameCorrente->pilha_op->depth);
	//printf("max_stack: %d\n",frameCorrente->max_stack);
    
    mostra_profundidade(1);


	if(frameCorrente->pilha_op->depth >= frameCorrente->max_stack){
		printf("Overflow na pilha de operandos!\n");
		exit(0);
	}

    // incrementa profundidade da pilha 
    frameCorrente->pilha_op->depth += 1;

    // poe valor no frame - o -1 eh pq o array comeca em 0
    frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1] = valor; 
}

/**
 * funcao para dar um pop na pilha de operandos, 
 * @param frame* frame_corrente, uma referencia ao frame atual
 * @return int32_t valor, o valor a ser colocado na pilha
 */
int32_t pop_op()
{
    mostra_profundidade(-1);

    // decrementa profundidade da pilha 
    frameCorrente->pilha_op->depth -= 1;

    if (frameCorrente->pilha_op->depth < 0)
    {
        printf("profundidade da pilha de operandos negativa: %d\n", frameCorrente->pilha_op->depth);
        printf("pc: %d\n", frameCorrente->pc);
    }

    // retorna valor se deve ao fato de ja termos decrementado o topo da pilha
    return frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth];  

}

decodificador dec[NUM_INSTRUCAO];
void mostra_profundidade(int i)
{
    // flag para debug
    int j = 0;
    
    if (j == 1)
    { 
        inicializa_decodificador(dec); 
        int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

        printf("instrucao que modifica pilha: %s\n", dec[frameCorrente->code[frameCorrente->pc]].instrucao);
        printf("valor de pc: %d\n", frameCorrente->pc);
        printf("nova profundidade da pilha: %d\n", frameCorrente->pilha_op->depth + i);   
    }
}

/**
 * funcao criada para analisar o conteudo da pilha de operandos
 * foi usada mais para debug e problemas com stackOverflow 
 */
void dumpStack(){
	int i;
    printf("\n");
	for(i = 0; i < frameCorrente->pilha_op->depth; i++){
		printf("valor: %d\n",frameCorrente->pilha_op->operandos[i]);
	}
}


/**
 * funcao criada para analisar o conteudo do array de variaveis locais
 * foi usada mais para debug de alguns problemas. 
 */
void dumpFields(){
	int i;
	for(i = 0; i < frameCorrente->max_locals; i++){
		printf("valor: %d\n",frameCorrente->fields[i]);
	}
}
