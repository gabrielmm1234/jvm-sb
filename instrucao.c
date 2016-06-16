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
 * Arquivo que contém as instrucoes implementadas pelo nosso program
 * Conforme sugerido, foi usado um vetor de ponteiro para funcoes
 * 
 */

#include "instrucao.h"
#include "frame.h"
#include "carregador.h"
#include "area_metodos.h"
#include "metodo.h"
#include <stdio.h>
#include <math.h> 
#include <stdint.h>
#include <stdlib.h>


/**
 * Acesso ao frame corrente declarado no modulo frame.h
 */
extern struct frame* frameCorrente;

/**
 * o decodificador permite eh um array com informacoes das varias instrucoes\n
 * a partir do opcode da instrucao, pode-se pelo decodificador descobrir o nome e quantos bytes ele ocupa 
 */ 
decodificador dec[NUM_INSTRUCAO];


/**
 * Funcao para executar uma instrucao, com base no opcode passado\n
 * @param uint8_t correspondente ao opcode da instrucao 
 * @return void
 */
void executarInstrucoes(uint8_t opcode){
	instrucao[opcode]();
}

/**
 * Função que aponta para uma implementação de cada instrução de acordo
 * com o opcode fornecido.
 * @param void
 * @return void
 */
void newInstrucoes()
{
	printf("Inicializando o vetor de ponteiros para funções!\n");
	
	instrucao[0] = nop;
	instrucao[1] = aconst_null;
	instrucao[2] = iconst_m1;
	instrucao[3] = iconst_0;
	instrucao[4] = iconst_1;
	instrucao[5] = iconst_2;
	instrucao[6] = iconst_3;
	instrucao[7] = iconst_4;
	instrucao[8] = iconst_5;
	instrucao[9] = lconst_0;
	instrucao[10] = lconst_1;
	instrucao[11] = fconst_0;
	instrucao[12] = fconst_1;
	instrucao[13] = fconst_2;
	instrucao[14] = dconst_0;
	instrucao[15] = dconst_1;
	instrucao[16] = bipush;
	instrucao[17] = sipush;
	instrucao[18] = ldc;
	instrucao[19] = ldc_w;
	instrucao[20] = ldc2_w;
	instrucao[21] = iload;
	instrucao[22] = lload;
	instrucao[23] = fload;
	instrucao[24] = dload;
	instrucao[25] = aload;
	instrucao[26] = iload_0;
	instrucao[27] = iload_1;
	instrucao[28] = iload_2;
	instrucao[29] = iload_3;
	instrucao[30] = lload_0;
	instrucao[31] = lload_1;
	instrucao[32] = lload_2;
	instrucao[33] = lload_3;
	instrucao[34] = fload_0;
	instrucao[35] = fload_1;
	instrucao[36] = fload_2;
	instrucao[37] = fload_3;
	instrucao[38] = dload_0;
	instrucao[39] = dload_1;
	instrucao[40] = dload_2;
	instrucao[41] = dload_3;
	instrucao[42] = aload_0;
	instrucao[43] = aload_1;
	instrucao[44] = aload_2;
	instrucao[45] = aload_3;
	instrucao[46] = iaload;
	instrucao[47] = laload;
	instrucao[48] = faload;
	instrucao[49] = daload;
	instrucao[50] = aaload;
	instrucao[51] = baload;
	instrucao[52] = caload;
	instrucao[53] = saload;
	instrucao[54] = istore;
	instrucao[55] = lstore;
	instrucao[56] = fstore;
	instrucao[57] = dstore;
	instrucao[58] = astore;
	instrucao[59] = istore_0;
	instrucao[60] = istore_1;
	instrucao[61] = istore_2;
	instrucao[62] = istore_3;
	instrucao[63] = lstore_0;
	instrucao[64] = lstore_1;
	instrucao[65] = lstore_2;
	instrucao[66] = lstore_3;
	instrucao[67] = fstore_0;
	instrucao[68] = fstore_1;
	instrucao[69] = fstore_2;
	instrucao[70] = fstore_3;
	instrucao[71] = dstore_0;
	instrucao[72] = dstore_1;
	instrucao[73] = dstore_2;
	instrucao[74] = dstore_3;
	instrucao[75] = astore_0;
	instrucao[76] = astore_1;
	instrucao[77] = astore_2;
	instrucao[78] = astore_3;
	instrucao[79] = iastore;
	instrucao[80] = lastore;
	instrucao[81] = fastore;
	instrucao[82] = dastore;
	instrucao[83] = aastore;
	instrucao[84] = bastore;
	instrucao[85] = castore;
	instrucao[86] = sastore;
	instrucao[87] = pop;
	instrucao[88] = pop2;
	instrucao[89] = dup;
	instrucao[90] = dup2_x1;
	instrucao[91] = dup2_x2;
	instrucao[92] = dup2;
	instrucao[93] = dup2_x1;
	instrucao[94] = dup2_x2;
	instrucao[95] = swap;
	instrucao[96] = iadd;
	instrucao[97] = ladd;
	instrucao[98] = fadd;
	instrucao[99] = dadd;
	instrucao[100] = isub;
	instrucao[101] = lsub;
	instrucao[102] = fsub;
	instrucao[103] = dsub;
	instrucao[104] = imul;
	instrucao[105] = lmul;
	instrucao[106] = fmul;
	instrucao[107] = dmul;
	instrucao[108] = idiv;
	instrucao[109] = ins_ldiv;
	instrucao[110] = fdiv;
	instrucao[111] = ddiv;
	instrucao[112] = irem;
	instrucao[113] = lrem;
	instrucao[114] = frem;
	instrucao[115] = _drem;
	instrucao[116] = ineg;
	instrucao[117] = lneg;
	instrucao[118] = fneg;
	instrucao[119] = dneg;
	instrucao[120] = ishl;
	instrucao[121] = lshl;
	instrucao[122] = ishr;
	instrucao[123] = lshr;
	instrucao[124] = iushr;
	instrucao[125] = lushr;
	instrucao[126] = iand;
	instrucao[127] = land;
	instrucao[128] = ior;
	instrucao[129] = lor;
	instrucao[130] = ixor;
	instrucao[131] = lxor;
	instrucao[132] = iinc;
	instrucao[133] = i2l;
	instrucao[134] = i2f;
	instrucao[135] = i2d;
	instrucao[136] = l2i;
	instrucao[137] = l2f;
	instrucao[138] = l2d;
	instrucao[139] = f2i;
	instrucao[140] = f2l;
	instrucao[141] = f2d;
	instrucao[142] = d2i;
	instrucao[143] = d2l;
	instrucao[144] = d2f;
	instrucao[145] = i2b;
	instrucao[146] = i2c;
	instrucao[147] = i2s;
	instrucao[148] = lcmp;
	instrucao[149] = fcmpl;
	instrucao[150] = fcmpg;
	instrucao[151] = dcmpl;
	instrucao[152] = dcmpg;
	instrucao[153] = ifeq;
	instrucao[154] = ifne;
	instrucao[155] = iflt;
	instrucao[156] = ifge;
	instrucao[157] = ifgt;
	instrucao[158] = ifle;
	instrucao[159] = if_icmpeq;
	instrucao[160] = if_icmpne;
	instrucao[161] = if_icmplt;
	instrucao[162] = if_icmpge;
	instrucao[163] = if_icmpgt;
	instrucao[164] = if_icmple;
	instrucao[165] = if_acmpeq;
	instrucao[166] = if_acmpne;
	instrucao[167] = ins_goto;
	instrucao[168] = jsr;
	instrucao[169] = ret;
	instrucao[170] = tableswitch;
	instrucao[171] = lookupswitch;
	instrucao[172] = ireturn;
	instrucao[173] = lreturn;
	instrucao[174] = freturn;
	instrucao[175] = dreturn;
	instrucao[176] = areturn;
	instrucao[177] = ins_return;
	instrucao[178] = getstatic;
	instrucao[179] = putstatic;
	instrucao[180] = getfield;
	instrucao[181] = putfield;
	instrucao[182] = invokevirtual;
	instrucao[183] = invokespecial;
	instrucao[184] = invokestatic;
	instrucao[185] = invokeinterface;
	instrucao[187] = ins_new;
	instrucao[188] = newarray;
	instrucao[189] = anewarray;
	instrucao[190] = arraylength;
	instrucao[191] = athrow;
	instrucao[192] = checkcast;
	instrucao[193] = instanceof;
	instrucao[194] = monitorenter;
	instrucao[195] = monitorexit;
	instrucao[196] = wide;
	instrucao[197] = multianewarray;
	instrucao[198] = ifnull;
	instrucao[199] = ifnonnull;
	instrucao[200] = goto_w;
	instrucao[201] = jsr_w;
}

//Implementação de cada instrução.

/**
 * funcao que nao realiza nada na pilha de operandos nem no array de var local 
 * @param void 
 * @return void 
 */
void nop(){

    // pula para proxima instrucao, atualizando pc
	frameCorrente->pc++;
}

/**
 * funcao que poe o valor a referencia null na pilha de operandos 
 * @param void 
 * @return void 
 */
void aconst_null(){

    // poe a refererencia null na pilha 
    push(frameCorrente, NULL_REF);
    
    // atualiza pc 
	frameCorrente->pc++;
}

/**
 * funcao que poe a constante inteira -1 na pilha de operandos 
 * @param void 
 * @return void 
 */
void iconst_m1(){
    // poe -1 na pilha de operandos
    push(frameCorrente, -1);
    
    // atualiza pc 
    frameCorrente->pc++;
}

/**
 * Funcao que empilha 0 na pilha de operandos.
 * @param void
 * @return void 
 */
void iconst_0(){

    // poe 0 na pilha de operandos
    push(frameCorrente, 0);
    
    // atualiza pc 
    frameCorrente->pc++;
	printf("Entrei no iconst_0\n");
	push(frameCorrente,(int32_t) 0);

	//atualiza pc
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

/**
 * Funcao que empilha 1 na pilha de operandos.
 * @param void
 * @return void 
 */
void iconst_1(){

    // poe 1 na pilha de operandos
    push(frameCorrente, 1);
    
    // atualiza pc 
    frameCorrente->pc++;

}

/**
 * Funcao que empilha 2 na pilha de operandos.
 * @param void
 * @return void 
 */
void iconst_2(){

    // poe 2 na pilha de operandos
    push(frameCorrente, 2);
    
    // atualiza pc 
    frameCorrente->pc++;

}

/**
 * Funcao que empilha 3 na pilha de operandos.
 * @param void
 * @return void 
 */
void iconst_3(){

    // poe 3 na pilha de operandos
    push(frameCorrente, 3);
    
    // atualiza pc 
    frameCorrente->pc++;

}

/**
 * Funcao que empilha 4 na pilha de operandos.
 * @param void
 * @return void 
 */
void iconst_4(){

    // poe 4 na pilha de operandos
    push(frameCorrente, 4);
    
    // atualiza pc 
    frameCorrente->pc++;

}

void iconst_5(){

}
void lconst_0(){

}
void lconst_1(){

}

/**
 * Funcao que coloca 0.0 na pilha.
 * @param void
 * @return void 
 */
void fconst_0(){
	printf("Entrei no fconst_0\n");
	//Auxiliar para utilizar o memcpy e não perder precisão com cast.
	int32_t* valPilha;
	//Float com valor zero para ser empilhado.
	float valF = 0.0;
	//Aloca mem para int32.
	valPilha = (int32_t*) malloc(sizeof(int32_t));
	//Importante!! -> copia bytes de um float para um int32
	//para empilhar na forma correta. Ao desempilhar realiza
	//Memcpy de volta para um float.
	memcpy(valPilha, &valF, sizeof(int32_t));
	printf("Valor Empilhado: %d\n",*valPilha);
	//Empilha float na forma de int32 para se adequar ao tipo da pilha.
	push(frameCorrente,*valPilha);

	//atualiza pc
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}
void fconst_1(){

}
void fconst_2(){

}
void dconst_0(){

}
void dconst_1(){

}

/**
 * Acessa um parametro(8 bits) da instrução em empilha na pilha de operandos.
 * @param void
 * @return void 
 */
void bipush(){
	printf("Entrei no bipush\n");
	int8_t argumento = (int8_t) frameCorrente->code[(++frameCorrente->pc)];
	printf("argumento empilhado: %d\n",argumento);
	push(frameCorrente,(int32_t)argumento);
	
	//atualiza pc
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

void sipush(){

}

int obtem_utf_eq(cp_info* cp, int pos_pool)
{
    int tag;

    // pega tag 
    tag = cp[pos_pool].tag;

    // se a tag for o de um class info 
    if (tag == CONSTANT_Utf8)
    {
        // imprime informacao e sai
        return pos_pool;
    }

    // senao, de acordo com a tag, decide qual sera a proxima posicao da cte pool que iremos olhar
    switch(tag)
    {
        // para fieldref e outros ele bifurcava e seguia dois 
        // como fazer nesses casos?
        case CONSTANT_Class:
            return obtem_utf_eq(cp, cp[pos_pool].info.Class.name_index - 1);

        case CONSTANT_String:
            return obtem_utf_eq(cp, cp[pos_pool].info.String.string_index - 1); 
    }
}
void ldc(){
    uint8_t indice, indice_utf;
    
	printf("Entrei no ldc!!\n");
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

    // pega indice 
    indice = frameCorrente->code[frameCorrente->pc + 1];
    indice_utf = obtem_utf_eq(frameCorrente->constant_pool, indice-1); 

    // se o indice para a constant pool for um int
    //if (frameCorrente->cp_info[indice].tag == CONSTANT_Integer)
    //{
        
    //}

    // se o indice para a constant pool for um float 
    //if (frameCorrente->cp_info[indice].tag == CONSTANT_Float)

    // se o indice para a constant pool for para uma string
    if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_String)
    {
        push(frameCorrente, (int32_t) indice_utf);
        printf("Valor %d empilhado\n",frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1]);

    }

	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

void ldc_w(){

}

/**
 * Acessa a constant pool num campo de 64 bits e coloca na pilha.
 * @param void
 * @return void 
 */
void ldc2_w(){
	printf("Entrei no ldc2_w\n");

	//Pega indice presente na instrução para acesso a constant pool.
	uint8_t indice = frameCorrente->code[frameCorrente->pc + 2];
	printf("Indice: %d\n",indice);

	//Pega tag da posição da constant pool dada pelo indice
	//Pode ser ou long ou double.
	uint8_t tag = (frameCorrente->constant_pool[indice-1]).tag;
	printf("tag: %d\n",tag);

	//TODO LONG

	//Se tag é 6 (double) acessa high bytes e low bytes e empilha.
	if(tag == 6){
		uint32_t alta = frameCorrente->constant_pool[indice-1].info.Double.high_bytes;
		uint32_t baixa = frameCorrente->constant_pool[indice-1].info.Double.low_bytes;
		printf("Parte alta empilhada: %d\n",alta);
		printf("Parte baixa empilhada: %d\n",baixa);
		push(frameCorrente,alta);
		push(frameCorrente,baixa);
	}

	//atualiza pc
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;

}
void iload(){

}
void lload(){

}
void fload(){

}
void dload(){

}
void aload(){

}
void iload_0(){

}
void iload_1(){

}
void iload_2(){

}
void iload_3(){

}
void lload_0(){

}
void lload_1(){

}
void lload_2(){

}
void lload_3(){

}
void fload_0(){

}
void fload_1(){

}
void fload_2(){

}
void fload_3(){

}
void dload_0(){

}
void dload_1(){

}
void dload_2(){

}
void dload_3(){

}

/**
 * Acessa posição 0 do array de var local e empilha na pilha de operandos.
 * @param void
 * @return void 
 */
void aload_0(){
	printf("Entrei aload_0\n");

	//Empilha a posição 0 do vetor de variáveis locais.
	push(frameCorrente,frameCorrente->fields[0]);
	printf("Valor %d empilhado\n",frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1]);


	//atualiza pc
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}
void aload_1(){

}
void aload_2(){

}
void aload_3(){

}
void iaload(){

}
void laload(){

}
void faload(){

}
void daload(){

}
void aaload(){

}
void baload(){

}
void caload(){

}
void saload(){

}
void istore(){

}
void lstore(){

}
void fstore(){

}
void dstore(){

}
void astore(){

}
void istore_0(){

}
void istore_1(){

}
void istore_2(){

}
void istore_3(){

}
void lstore_0(){

}
void lstore_1(){

}
void lstore_2(){

}
void lstore_3(){

}
void fstore_0(){

}
void fstore_1(){

}
void fstore_2(){

}
void fstore_3(){

}
void dstore_0(){

}
void dstore_1(){

}
void dstore_2(){

}
void dstore_3(){

}
void astore_0(){

}
void astore_1(){

}
void astore_2(){

}
void astore_3(){

}
void iastore(){

}
void lastore(){

}
void fastore(){

}
void dastore(){

}
void aastore(){

}
void bastore(){

}
void castore(){

}
void sastore(){

}

/**
 * Funcao que desempilha um valor da pilha de operandos.
 * @param void
 * @return void 
 */
void pop(){
	printf("Entrei no pop\n");
	pop_op(frameCorrente);

	//atualiza pc
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

void pop2(){

}

/**
 * Instrução que retira valor da pilha e adiciona de volta duplicado.
 * @param void
 * @return void 
 */
void dup(){
	printf("Entrei no dup\n");
	int32_t aux;

	//Desempilha
	aux = pop_op(frameCorrente);

	//Duplica
	push(frameCorrente,aux);
	printf("Valor %d empilhado\n",frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1]);
	push(frameCorrente,aux);
	printf("Valor %d empilhado\n",frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1]);


	//atualiza pc
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

void dup_x1(){

}
void dup_x2(){

}
void dup2(){

}
void dup2_x1(){

}
void dup2_x2(){

}
void swap(){

}

/**
 * Funcao desempilha dois valores inteiros, soma-os e empilha resultado.
 * @param void
 * @return void 
 */
void iadd(){
	printf("Entrei no iadd\n");
	int32_t v1,v2;
	v1 = pop_op(frameCorrente);
	v2 = pop_op(frameCorrente);
	printf("v1: %d\n",v1);
	printf("v2: %d\n",v2);
	printf("Empilhado: %d\n",v1+v2);
	push(frameCorrente, v1+v2);

	//atualiza pc
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

void ladd(){

}
void fadd(){

}

/**
 * Desempilha dois valores, soma e empilha dois valores double.
 * @param void
 * @return void 
 */
void dadd(){
	printf("Entrei no dadd\n");

	//Parte alta e baixa do double.
	int32_t alta;
	int32_t baixa;

	//Obtem parte baixa primeiro -> Foi empilhada por ultimo(topo)
	baixa = pop_op(frameCorrente);
	alta = pop_op(frameCorrente);

	//Converter os numeros 32 bits para 64 bits(double)

	//Atribui parte alta primeiro
	int64_t dVal = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	dVal <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	dVal = dVal + baixa;

	//Finalmente copio os bytes do int64_t para um double.
	//memcpy copia 64 bits de dVal para valorDouble1.
	double valorDouble1;
	memcpy(&valorDouble1, &dVal, sizeof(int64_t));


	//Obtem parte baixa primeiro -> Foi empilhada por ultimo(topo)
	baixa = pop_op(frameCorrente);
	alta = pop_op(frameCorrente);

	//Converter os numeros 32 bits para 64 bits(double)

	//Atribui parte alta primeiro
	dVal = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	dVal <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	dVal = dVal + baixa;

	//Finalmente copio os bytes do int64_t para um double.
	//memcpy copia 64 bits de dVal para valorDouble2.
	double valorDouble2;
	memcpy(&valorDouble2, &dVal, sizeof(int64_t));

	//Soma os dois valores double
	printf("Valor1 double: %f\n",valorDouble1);
	printf("Valor2 double: %f\n",valorDouble2);
	double doubleSomado = valorDouble1 + valorDouble2;
	printf("Valor somado: %f\n",doubleSomado);

	//Necessario converter mais uma vez o double somado para int64 para 
	//empilhar corretamente.
	int64_t valorPilha;
	memcpy(&valorPilha, &doubleSomado, sizeof(int64_t));

	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = valorPilha >> 32;
	baixa = valorPilha & 0xffffffff;

	//finalmente empilha.
	printf("Parte alta empilhada: %d\n",alta);
	printf("Parte baixa empilhada: %d\n",baixa);
	push(frameCorrente,alta);
	push(frameCorrente,baixa);

	//atualiza pc
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

void isub(){

}
void lsub(){

}
void fsub(){

}

/**
 * Desempilha 2 valores double da pilha, subtrai e empilha o resultado.
 * @param void
 * @return void 
 */
void dsub(){

}

/**
 * Desempilha 2 valores da pilha, multiplica-os e empilha o resultado.
 * @param void
 * @return void 
 */
void imul(){
	printf("Entrei no imul\n");
	 int32_t v1 = pop_op(frameCorrente);
	 int32_t v2 = pop_op(frameCorrente);
	 push(frameCorrente,(int32_t)(v1 * v2));
	 printf("Valor empilhado: %d\n",v1*v2);

	//atualiza pc
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

void lmul(){

}
void fmul(){

}

/**
 * Desempilha 2 valores double da pilha, multiplica-os e empilha o resultado.
 * @param void
 * @return void 
 */
void dmul(){

}
void idiv(){

}
void ins_ldiv(){

}
void fdiv(){

}

/**
 * Desempilha dois valores double da pilha divide e empilha o resultado,
 * @param void
 * @return void 
 */
void ddiv(){
	printf("Entrei no ddiv\n");

	//Partes altas e baixas dos dois doubles.
	int32_t alta,baixa,alta1,baixa1;

	baixa1 = pop_op(frameCorrente);
	alta1 = pop_op(frameCorrente);

	baixa = pop_op(frameCorrente);
	alta = pop_op(frameCorrente);

	//Converter os numeros 32 bits para 64 bits(double)

	//Atribui parte alta primeiro
	int64_t dVal = alta1;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	dVal <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	dVal = dVal + baixa1;

	//Finalmente copio os bytes do int64_t para um double.
	//memcpy copia 64 bits de dVal para valorDouble1.
	double v1;
	memcpy(&v1, &dVal, sizeof(double));

	//Converter os numeros 32 bits para 64 bits(double)

	//Atribui parte alta primeiro
	dVal = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	dVal <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	dVal = dVal + baixa;

	//Finalmente copio os bytes do int64_t para um double.
	//memcpy copia 64 bits de dVal para valorDouble1.
	double v2;
	memcpy(&v2, &dVal, sizeof(double));

	double resultado = v2 / v1;
	printf("Resultado: %f\n",resultado);

	//Necessario converter mais uma vez o double somado para int64 para 
	//empilhar corretamente.
	int64_t pilhaVal;
	memcpy(&pilhaVal, &resultado, sizeof(int64_t));

	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = pilhaVal >> 32;
	baixa = pilhaVal & 0xffffffff;

	//finalmente empilha.
	printf("Parte alta empilhada: %d\n",alta);
	printf("Parte baixa empilhada: %d\n",baixa);
	push(frameCorrente,alta);
	push(frameCorrente,baixa);


	exit(0);
}
void irem(){

}
void lrem(){

}
void frem(){

}
void _drem(){

}

/**
 * Desempilha um int ,negativa e empilha o resultado.
 * @param void
 * @return void 
 */
void ineg(){
	printf("Entrei no ineg\n");
		
	//Desempilha valor da pilha
	int32_t retPilha = pop_op(frameCorrente);
	//Negativa.
	int32_t aux = -retPilha;
	printf("Valor empilhado: %d\n",aux);
	//Empilha valor negativado.
	push(frameCorrente,aux);

	//atualiza pc
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}
void lneg(){

}
void fneg(){

}
void dneg(){

}
void ishl(){

}
void lshl(){

}
void ishr(){

}
void lshr(){

}
void iushr(){

}
void lushr(){

}
void iand(){

}
void land(){

}
void ior(){

}
void lor(){

}
void ixor(){

}
void lxor(){

}
void iinc(){

}
void i2l(){

}

/**
 * Funcao que desempilha um inteiro da pilha, converte para um float e empilha
 * o resultado.
 * @param void
 * @return void 
 */
void i2f(){
	printf("Entrei no i2f\n");
	
	//Obtem valor da pilha
	int32_t val = (int32_t) pop_op(frameCorrente);
	printf("Val inteiro: %d\n",val);

	//Realiza cast para float
	float valF = (float) val;
	printf("Val Float: %f\n",valF);

	//Utiliza um auxiliar para armazenar o valor float e empilha-lo.
	int32_t valPilha;
	memcpy(&valPilha, &valF, sizeof(int32_t));
	printf("Val empilhado %d\n",valPilha);
	push(frameCorrente,valPilha);

	//Atualiza PC.
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

/**
 * Desempilha um inteiro converte para double e empilha o resultado.
 * @param void
 * @return void 
 */
void i2d(){
	printf("Entrei no i2d\n");
	//Desempilha valor da pilha
	int32_t retPilha = pop_op(frameCorrente);

	//Cast para double
	double dVal = (double) retPilha;
	printf("Valor int já em double desempilhado: %f\n",dVal);

	int64_t pilhaVal;
	//Copia bytes em doubleNum para pilhaVal que é um int64
	memcpy(&pilhaVal, &dVal, sizeof(int64_t));

	//Parte alta e parte baixa do double.
	int32_t alta;
	int32_t baixa;

	//Shifta 32 bits para pegar somente a parte alta
	alta = pilhaVal >> 32;

	//Realiza um and bit a bit para zerar a parte alta e obter somente a parte baixa.
	baixa = pilhaVal & 0xffffffff;

	//Empilha parte alta e baixa.
	printf("Parte alta empilhada: %d\n",alta);
	printf("Parte baixa empilhada: %d\n",baixa);
	push(frameCorrente,alta);
	push(frameCorrente,baixa);

	//Atualiza PC.
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}
void l2i(){

}
void l2f(){

}
void l2d(){

}
void f2i(){

}
void f2l(){

}

/**
 * Desempilha um float converte para double e empilha
 * @param void
 * @return void 
 */
void f2d(){
	printf("Entrei no f2d\n");
	//Desempilha valor da pilha
	int32_t retPilha = pop_op(frameCorrente);
	float fVal;
	//Copia os bytes do retPilha para uma var float -> Nao perder precisao
	memcpy(&fVal, &retPilha, sizeof(int32_t));
	printf("Valor int já em float desempilhado: %f\n",fVal);

	//Cast para double
	double dVal = (double) fVal;

	//Copia dVal para um int64_t para poder empilhar. -> Nao perder precisao
	int64_t pilhaVal;
	memcpy(&pilhaVal, &dVal, 2*sizeof(int32_t));

	//Parte alta e parte baixa do double.
	int32_t alta;
	int32_t baixa;

	//Shifta 32 bits para pegar somente a parte alta
	alta = pilhaVal >> 32;

	//Realiza um and bit a bit para zerar a parte alta e obter somente a parte baixa.
	baixa = pilhaVal & 0xffffffff;

	//Empilha parte alta e baixa.
	printf("Parte alta empilhada: %d\n",alta);
	printf("Parte baixa empilhada: %d\n",baixa);
	push(frameCorrente,alta);
	push(frameCorrente,baixa);

	//Atualiza PC.
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}
void d2i(){

}
void d2l(){

}

/**
 * Desempilha um double converte para float e empilha.
 * @param void
 * @return void 
 */
void d2f(){

}
void i2b(){

}
void i2c(){

}
void i2s(){

}
void lcmp(){

}

/**
 * Função que desempilha dois floats da pilha e compara.
 * Se primeiro maior que segundo -> empilha 1
 * Se forem iguais -> empilha 0
 * Se primeiro menor que segundo -> empilha -1
 * @param void
 * @return void 
 */
void fcmpl(){
	//Valores a serem comparadas.
	float val1,val2;
	//Valor para receber o pop da pilha e realizar a copia dos bytes para 
	//os floats.
	int32_t retPilha;

	//Desempilha o segundo valor(topo).
	retPilha = pop_op(frameCorrente);
	//Copia os bytes do int32 para uma var do tipo float para nao perder precisão.
	memcpy(&val2,&retPilha,sizeof(float));

	//Desempilha o primeiro valor(topo).
	retPilha = pop_op(frameCorrente);
	//Copia os bytes do int32 para uma var do tipo float para nao perder precisão.
	memcpy(&val1,&retPilha,sizeof(float));

	//Compara os dois floats e seta o resultado.
	printf("val1: %f\n",val1);
	printf("val2: %f\n",val2);
	if(val1 == val2){
		printf("val1 == val2 empilhando 0\n");
		push(frameCorrente,(int32_t)0);
	}
	if(val1 > val2){
		printf("val1 > val2 empilhando 1\n");
		push(frameCorrente,(int32_t)1);
	}
	if(val1 < val2){
		printf("val1 < val2 empilhando -1\n");
		push(frameCorrente,(int32_t)-1);
	}

	//Atualiza PC.
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}
void fcmpg(){

}
void dcmpl(){

}
void dcmpg(){

}
void ifeq(){

}
void ifne(){

}

/**
 * Funcao que realiza um jump se valor desempilhado for menor que 0.
 * lt -> lower than zero.
 * @param void
 * @return void 
 */
void iflt(){
	uint8_t offset;
	//Pega offset para salto.
	offset = frameCorrente->code[frameCorrente->pc + 2];
	printf("Offset: %d\n",offset);

	//Pega valor a ser comparado na pilha.
	int32_t retPilha = pop_op(frameCorrente);
	printf("Val: %d\n",retPilha);

	//Se val menor que zero atualiza pc com offset
	if(retPilha < 0){
		frameCorrente->pc += offset;
		printf("Val < 0 novopc: %d\n",frameCorrente->pc);
	}else{
		frameCorrente->pc += 3;
		printf("Val > 0 novopc: %d\n",frameCorrente->pc);
	}
}

void ifge(){

}
void ifgt(){

}
void ifle(){

}
void if_icmpeq(){

}
void if_icmpne(){

}
void if_icmplt(){

}
void if_icmpge(){

}
void if_icmpgt(){

}
void if_icmple(){

}
void if_acmpeq(){

}
void if_acmpne(){

}

/**
 * Funcao que realiza um jump a partir de um offset da instrução.
 * @param void
 * @return void 
 */
void ins_goto(){
	//TODO obtém offset

	//TODO pc = pc + offset
}
void jsr(){

}
void ret(){

}
void tableswitch(){

}
void lookupswitch(){

}
void ireturn(){

}
void lreturn(){

}
void freturn(){

}
void dreturn(){

}
void areturn(){

}

/**
 * Funcao retorna 0
 * @param void
 * @return void 
 */
void ins_return(){
	printf("entrei no ins_return!!\n");

	//Executa instrução.

	//TODO setar variaveis globais de retorno para 0.

	//Atualiza PC.
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
	printf("retornando! método acabou!\n");
}
void getstatic(){
	printf("Entrei no getstatic!!\n");

	//Executa a instrução.
    // pega indice da constant pool 
    
    // se o indice nao corresponde a uma referencia a um field
        // erro
    
    // pega classe correspondente
    // se a classe nao eh a System Java
        // carrega classe na memoria, caso ainda nao tenha sido 
        // se nao for um campo static lanca excecao 
    // poe valor da classe no stack 
    // incrementa profundidade do stack 

	//Atualiza PC.
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

void putstatic(){

}
void getfield(){
	printf("Entrei no getfield\n");

	//Pega indice no argumento da instrução.
	uint32_t indice = frameCorrente->code[frameCorrente->pc + 2];
	printf("indice: %d\n",indice);

	//Acessa o indice da classe que possui o field.
	int32_t indiceClasse = frameCorrente->constant_pool[indice-1].info.Fieldref.class_index;
	printf("indiceClasse: %d\n",indiceClasse);

	//Obtem o nome da classe a partir do indice obtido anteriormente
	char* nomeClasse = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[indiceClasse-1].info.Class.name_index);
	printf("nomeClasse: %s\n",nomeClasse);
	//Obtem agora o indice do nome e do tipo
	uint16_t nomeTipoIndice = frameCorrente->constant_pool[indice-1].info.Fieldref.name_and_type_index;
	printf("nomeTipoIndice: %d\n",nomeTipoIndice);
	//Obtem finalmente o nome e o tipo do field
	char* nome = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[nomeTipoIndice-1].info.NameAndType.name_index);
	char* tipo = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[nomeTipoIndice-1].info.NameAndType.descriptor_index);
	tipoGlobal = tipo;
 	printf("nome: %s\n",nome);
 	printf("tipo: %s\n",tipo);

 	objeto* obj = (objeto*) pop_op(frameCorrente);

 	//Obtem indice do field utilizando as informações anteriores.
 	int32_t indiceField = buscaCampo(nomeClasse,nome,tipo);
 	printf("indiceField: %d\n",indiceField);

 	//obtem indice do nome do field (variavel)
 	uint32_t indiceNome = frameCorrente->classe->fields[indiceField].name_index;
 	printf("indiceNome: %d\n",indiceNome);

 	int32_t i;
	for(i = 0;obj->indiceCampos[i] != indiceNome; i++);
 	//Pega o field do objeto e empilha.
 	uint32_t val = obj->campos[i];
 	printf("val empilhado: %d\n",val);
 	push(frameCorrente,val);

	//Atualiza PC.
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

/**
 * Função que acessa valor na pilha e atribui ao objeto que o executa.
 * @param void
 * @return void 
 */
void putfield(){
	printf("Entrei no putfield\n");

	//Pega indice no argumento da instrução.
	uint32_t indice = frameCorrente->code[frameCorrente->pc + 2];
	printf("indice: %d\n",indice);

	//Acessa o indice da classe que possui o field.
	int32_t indiceClasse = frameCorrente->constant_pool[indice-1].info.Fieldref.class_index;
	printf("indiceClasse: %d\n",indiceClasse);

	//Obtem o nome da classe a partir do indice obtido anteriormente
	char* nomeClasse = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[indiceClasse-1].info.Class.name_index);
	printf("nomeClasse: %s\n",nomeClasse);
	//Obtem agora o indice do nome e do tipo
	uint16_t nomeTipoIndice = frameCorrente->constant_pool[indice-1].info.Fieldref.name_and_type_index;
	printf("nomeTipoIndice: %d\n",nomeTipoIndice);
	//Obtem finalmente o nome e o tipo do field
	char* nome = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[nomeTipoIndice-1].info.NameAndType.name_index);
	char* tipo = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[nomeTipoIndice-1].info.NameAndType.descriptor_index);
 	printf("nome: %s\n",nome);
 	printf("tipo: %s\n",tipo);

 	//Obtem indice do field utilizando as informações anteriores.
 	int32_t indiceField = buscaCampo(nomeClasse,nome,tipo);
 	printf("indiceField: %d\n",indiceField);

 	//obtem indice do nome do field (variavel)
 	uint32_t indiceNome = frameCorrente->classe->fields[indiceField].name_index;
 	printf("indiceNome: %d\n",indiceNome);

 	//obtem valor e objeto da pilha e seta o valor no field do objeto.
 	int32_t val = pop_op(frameCorrente);
 	printf("valor desempilhado: %d\n",val);
 	objeto* obj = (objeto*)pop_op(frameCorrente);

 	int i;
 	for(i = 0; obj->indiceCampos[i] != indiceNome; i++);
	obj->campos[i] = val;


	//Atualiza PC.
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	

	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

/**
 * Funcao que invoca métodos de uma classe que não se enquadram nas demais
 * categorias (static,interface,special).
 * @param void
 * @return void 
 */
void invokevirtual(){
	printf("Entrei no invokevirtual!!\n");

    char* nomeClasse;
    char* nomeMetodo;
    char* descricaoMetodo;
    uint16_t nomeMetodoAux, descricaoMetodoAux,nomeTipoAux,stringAux;
    int32_t resultado,resultado2;
    int32_t classeIndice;
    uint8_t* string;
    static int8_t flagAppend = 0;

    uint32_t pcAux = frameCorrente->code[frameCorrente->pc + 2];

    classeIndice = frameCorrente->constant_pool[pcAux - 1].info.Methodref.class_index;

    nomeClasse = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[classeIndice - 1].info.Class.name_index);
    nomeTipoAux = frameCorrente->constant_pool[pcAux - 1].info.Methodref.name_and_type_index;

    nomeMetodoAux = frameCorrente->constant_pool[nomeTipoAux - 1].info.NameAndType.name_index;

	descricaoMetodoAux = frameCorrente->constant_pool[nomeTipoAux - 1].info.NameAndType.descriptor_index;
	

    nomeMetodo = retornaNome(frameCorrente->classe, nomeMetodoAux);

    descricaoMetodo = retornaNome(frameCorrente->classe, descricaoMetodoAux);

    if((strcmp(nomeClasse, "java/lang/StringBuffer") == 0) && (strcmp(nomeMetodo,"append") == 0)){
			flagAppend++;
	}

	if((strcmp(nomeClasse, "java/io/PrintStream") == 0) && (strcmp(nomeMetodo,"println") == 0)){
		if(strstr(descricaoMetodo, "Ljava/lang/String") != NULL) {
			if(flagAppend == 0){
			resultado = pop_op(frameCorrente);
			//resultado = frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1];
			string = frameCorrente->constant_pool[resultado].info.Utf8.bytes;
			printf("%s\n",string);
			}
			else if(flagAppend == 2){
				resultado = pop_op(frameCorrente);
				resultado2 = pop_op(frameCorrente);

				string = frameCorrente->constant_pool[resultado2].info.Utf8.bytes;
				printf("%s",string);

					if(strcmp(tipoGlobal, "F") == 0){
						float valDesemp;
						memcpy(&valDesemp,&resultado, sizeof(float));
						printf("%f\n",valDesemp);
					}

				flagAppend = 0;
			}
		}
	}

	if((strcmp(nomeClasse, "java/util/Scanner") == 0) && (strcmp(nomeMetodo,"next") == 0)){
		int32_t aux;
		scanf("%d",&aux);
		push(frameCorrente,aux);
		printf("Valor %d empilhado\n",frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1]);
	}

	//Atualiza PC.

	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	

	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

/**
 * Função que invoca métodos especiais de uma classe.
 * @param void
 * @return void 
 */
void invokespecial(){
	printf("Entrei no invokespecial\n");
	method_info* metodoInvocado;
	//Executar instrução.

	//Pega indice no argumento da instrução.
	uint32_t indice = frameCorrente->code[frameCorrente->pc + 2];
	printf("indice: %d\n",indice);

	//Pega o indice do nome da classe na CP pelo indice anterior.
	uint32_t indiceClasse = (frameCorrente->constant_pool[indice-1]).info.Methodref.class_index;
	printf("indiceClasse: %d\n",indiceClasse);

	//Pega nome da classe.
	char* nomeClasse = retornaNome(frameCorrente->classe,(frameCorrente->constant_pool[indiceClasse-1]).info.Class.name_index);
	printf("nomeClasse: %s\n",nomeClasse);

	if(strcmp("java/lang/Object",nomeClasse) == 0){

		printf("Método nativo java - java/lang/object\n");

		//Atualiza PC.
		inicializa_decodificador(dec); 
		int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
		printf("num_bytes: %d\n",num_bytes);

		//proxima instruçao.
		for(int8_t i = 0; i < num_bytes + 1; i++)
			frameCorrente->pc++;
		printf("novo pc: %d\n",frameCorrente->pc);
		printf("novo opcode: %d\n",frameCorrente->code[frameCorrente->pc]);

		return;
	}

	if(strcmp("java/lang/StringBuffer",nomeClasse) == 0){

		printf("Método nativo java - java/lang/object\n");

		//Atualiza PC.
		inicializa_decodificador(dec); 
		int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
		printf("num_bytes: %d\n",num_bytes);

		//proxima instruçao.
		for(int8_t i = 0; i < num_bytes + 1; i++)
			frameCorrente->pc++;
		printf("novo pc: %d\n",frameCorrente->pc);
		printf("novo opcode: %d\n",frameCorrente->code[frameCorrente->pc]);

		return;
	}

	if(strcmp("java/util/Scanner",nomeClasse) == 0){

		printf("Método nativo java - java/util/Scanner\n");

		//Atualiza PC.
		inicializa_decodificador(dec); 
		int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

		//proxima instruçao.
		for(int8_t i = 0; i < num_bytes + 1; i++)
			frameCorrente->pc++;

		return;
	}

	//Pega posição da classe no array de classes
	int32_t indexClasse = carregaMemClasse(nomeClasse);
	printf("posClasse: %d\n",indexClasse);

	//Pega referencia ao classFile pelo indice anterior.
	classFile* classe = buscaClasseIndice(indexClasse);

	//Pega o nome e tipo dó método pelo indice da instrução.
	uint16_t nomeTipoIndice = frameCorrente->constant_pool[indice-1].info.Methodref.name_and_type_index;
	printf("nomeTipoIndice: %d\n",nomeTipoIndice);

	//Busca método a ser invocado.
	metodoInvocado = buscaMetodo(frameCorrente->classe,classe,nomeTipoIndice);

	if(metodoInvocado != NULL){
		printf("método invocado: %s\n",classe->constant_pool[metodoInvocado->name_index - 1].info.Utf8.bytes);
	}

	//Pega parametros da pilha pelo numero de fields
	int32_t numeroParametros = retornaNumeroParametros(classe,metodoInvocado);
	printf("numeroParametros: %d\n",numeroParametros);

	//Aloca espaço para os parametros do método
	uint32_t* fields = calloc(sizeof(uint32_t),numeroParametros + 1);

	//Desempilha os parametros da pilha.
	for(int32_t i = 0; i <= numeroParametros; i++)
		fields[i] = pop_op(frameCorrente);

	//inicia método
	iniciaMetodo(metodoInvocado, classe);

	//Preenche fields no frame novo (invoke).
	for(int32_t i = 0; i <= numeroParametros; i++) {
			frameCorrente->fields[i] = fields[i];
	}

	//Executa método.
	executaFrameCorrente();

	//Atualiza PC.
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

/**
 * Funcao que invoca métodos estáticos de uma classe.
 * @param void
 * @return void 
 */
void invokestatic(){
	printf("Entrei no invokestatic\n");

    char* nomeMetodo;
    char* descricaoMetodo;
    uint16_t nomeMetodoAux, descricaoMetodoAux,nomeTipoAux,stringAux;

	//Pega indice no argumento da instrução.
	uint32_t indice = frameCorrente->code[frameCorrente->pc + 2];
	printf("indice: %d\n",indice);

	//Pega o indice do nome da classe na CP pelo indice anterior.
	uint32_t indiceClasse = (frameCorrente->constant_pool[indice-1]).info.Methodref.class_index;
	printf("indiceClasse: %d\n",indiceClasse);

	//Pega nome da classe.
	char* nomeClasse = retornaNome(frameCorrente->classe,(frameCorrente->constant_pool[indiceClasse-1]).info.Class.name_index);
	printf("nomeClasse: %s\n",nomeClasse);

	nomeTipoAux = frameCorrente->constant_pool[indice - 1].info.Methodref.name_and_type_index;

    nomeMetodoAux = frameCorrente->constant_pool[nomeTipoAux - 1].info.NameAndType.name_index;

	descricaoMetodoAux = frameCorrente->constant_pool[nomeTipoAux - 1].info.NameAndType.descriptor_index;
	

    nomeMetodo = retornaNome(frameCorrente->classe, nomeMetodoAux);

    descricaoMetodo = retornaNome(frameCorrente->classe, descricaoMetodoAux);

	if((strcmp(nomeClasse, "java/lang/System") == 0) && (strcmp(nomeMetodo,"exit") == 0)){
		if(strstr(descricaoMetodo, "(I)V") != NULL) {
			printf("Saindo do programa!\n");
			int32_t retPilha = pop_op(frameCorrente);
			printf("cod retorno: %d\n",retPilha);
			exit(retPilha);
		}
	}

	if((strcmp(nomeClasse, "java/lang/Math") == 0) && (strcmp(nomeMetodo,"sqrt") == 0)){
		if(strstr(descricaoMetodo, "(D)D") != NULL) {
			int32_t baixa = pop_op(frameCorrente);
			int32_t alta = pop_op(frameCorrente);

			//Atribui parte alta primeiro
			int64_t dVal = alta;
			//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
			dVal <<= 32;
			//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
			//os 32 bits da parte baixa estão zerados.
			dVal = dVal + baixa;

			//Finalmente copio os bytes do int64_t para um double.
			//memcpy copia 64 bits de dVal para valorDouble1.
			double valorDouble1;
			memcpy(&valorDouble1, &dVal, sizeof(int64_t));

			//Tira raiz
			valorDouble1 = sqrt (valorDouble1);
			printf("Raiz do valor: %f\n",valorDouble1);

			//Volta para 64 bits para empilhar
			int64_t aux;
			memcpy(&aux, &valorDouble1, sizeof(int64_t));

			//Converte para parte alta e baixa novamente :) kk para empilhar
			alta = aux >> 32;
			baixa = aux & 0xffffffff;

			push(frameCorrente,alta);
			push(frameCorrente,baixa);
		}
	}

	//Atualiza PC.
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}
void invokeinterface(){

}

/**
 * Função que cria um objeto (struct objeto) e adiciona no heap(array)
 * @param void
 * @return void 
 */
void ins_new(){
	printf("Entrei no new!\n");
	uint32_t indice;
	int32_t aux;
	char* nomeClasse;
	classFile* classe;
	objeto* objeto;
	//TODO cria objeto no heap(array).

	//Pega indice na instrução.
	indice = frameCorrente->code[2+(frameCorrente->pc)];

	//Pega o nome da classe apontado pelo indice.
	nomeClasse = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[indice-1].info.Class.name_index);

	if(strcmp("java/util/Scanner",nomeClasse) == 0){

		printf("Método nativo java - java/util/Scanner\n");

		//Atualiza PC.
		inicializa_decodificador(dec); 
		int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

		//proxima instruçao.
		for(int8_t i = 0; i < num_bytes + 1; i++)
			frameCorrente->pc++;
		
		return;
	}

	if(strcmp("java/lang/StringBuffer",nomeClasse) == 0){

		printf("Método nativo java - java/util/Scanner\n");

		//Atualiza PC.
		inicializa_decodificador(dec); 
		int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

		//proxima instruçao.
		for(int8_t i = 0; i < num_bytes + 1; i++)
			frameCorrente->pc++;
		
		return;
	}
	//Busca indice da classe no array de classeFiles
	aux = carregaMemClasse(nomeClasse);

	//Pega classFile pelo indice no array de classes
	classe = buscaClasseIndice(aux);

	//Cria um objeto a partir do classFile.
	objeto = criaObjeto(classe);

	//empilha objeto na pilha de operandos (push)
	push(frameCorrente,(int32_t) objeto);
	printf("Valor %d empilhado\n",frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1]);

	//atualia pc.
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

void newarray(){

}
void anewarray(){

}
void arraylength(){

}
void athrow(){

}
void checkcast(){

}
void instanceof(){

}
void monitorenter(){

}
void monitorexit(){

}
void wide(){

}
void multianewarray(){

}
void ifnull(){

}
void ifnonnull(){

}
void goto_w(){

}
void jsr_w(){

}
