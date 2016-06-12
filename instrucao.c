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
#include <stdio.h>
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

//NOP -> Não realiza nada da pilha de operandos nem no array de var local.
//Somente pula para a proxima instrucao.
void nop(){
	frameCorrente->pc++;
}

void aconst_null(){

}
void iconst_m1(){

}
void iconst_0(){

}
void iconst_1(){

}
void iconst_2(){

}
void iconst_3(){

}
void iconst_4(){

}
void iconst_5(){

}
void lconst_0(){

}
void lconst_1(){

}
void fconst_0(){

}
void fconst_1(){

}
void fconst_2(){

}
void dconst_0(){

}
void dconst_1(){

}
void bipush(){

}
void sipush(){

}
void ldc(){
    uint8_t indice;

	printf("Entrei no ldc!!\n");
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	printf("num_bytes: %d\n",num_bytes);

    // pega indice 
    indice = frameCorrente->code[frameCorrente->pc + 1];

    // se o indice para a constant pool for um int
    //if (frameCorrente->cp_info[indice].tag == CONSTANT_Integer)
    //{
        
    //}

    // se o indice para a constant pool for um float 
    //if (frameCorrente->cp_info[indice].tag == CONSTANT_Float)

    // se o indice para a constant pool for para uma string
    if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_String)
    {
        // poe uma referencia a essa instancia na pilha de operandos
        frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth] = (int32_t) indice;

        // incrementa profundidade da pilha de operandos 
        frameCorrente->pilha_op->depth += 1;
    }

	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
	printf("novo pc: %d\n",frameCorrente->pc);
	printf("novo opcode: %d\n",frameCorrente->code[frameCorrente->pc]);
}

void ldc_w(){

}
void ldc2_w(){

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
void aload_0(){

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
void pop(){

}
void pop2(){

}
void dup(){

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
void iadd(){

}
void ladd(){

}
void fadd(){

}
void dadd(){

}
void isub(){

}
void lsub(){

}
void fsub(){

}
void dsub(){

}
void imul(){

}
void lmul(){

}
void fmul(){

}
void dmul(){

}
void idiv(){

}
void ins_ldiv(){

}
void fdiv(){

}
void ddiv(){

}
void irem(){

}
void lrem(){

}
void frem(){

}
void _drem(){

}
void ineg(){

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
void i2f(){

}
void i2d(){

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
void f2d(){

}
void d2i(){

}
void d2l(){

}
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
void fcmpl(){

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
void iflt(){

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
void ins_goto(){

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
void ins_return(){
	printf("entrei no ins_return!!\n");

	//Executa instrução.

	//Atualiza PC.
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	printf("num_bytes: %d\n",num_bytes);
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
	printf("novo pc: %d\n",frameCorrente->pc);
	printf("novo opcode: %d\n",frameCorrente->code[frameCorrente->pc]);
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
	printf("num_bytes: %d\n",num_bytes);
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
	printf("novo pc: %d\n",frameCorrente->pc);
	printf("novo opcode: %d\n",frameCorrente->code[frameCorrente->pc]);
}
void putstatic(){

}
void getfield(){

}
void putfield(){

}
void invokevirtual(){
	printf("Entrei no invokevirtual!!\n");

	//Executa a instrução.
    
    // pega indice 
    
    // se a referencia a constant pool nao for uma referencia simbolica a um metodo
        // avisa erro e para
    
    // se for uma chamada a printStream 
        // nesse caso usa printf do C 
        // decrementa a profundidade do stack por 2

	//Atualiza PC.
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;
	printf("num_bytes: %d\n",num_bytes);
	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
	printf("novo pc: %d\n",frameCorrente->pc);
	printf("novo opcode: %d\n",frameCorrente->code[frameCorrente->pc]);

}
void invokespecial(){

}
void invokestatic(){

}
void invokeinterface(){

}
void ins_new(){

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
