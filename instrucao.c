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
 * Arquivo que contém as instrucoes implementadas pelo nosso programa
 * Conforme sugerido, foi usado um vetor de ponteiro para funcoes
 * 
 */

#include "./includes/instrucao.h"
#include "./includes/frame.h"
#include "./includes/carregador.h"
#include "./includes/area_metodos.h"
#include "./includes/metodo.h"
 
#include <stdio.h>
#include <math.h> 
#include <stdint.h>
#include <stdlib.h>

 #define NULL_REF NULL

//OBS: Alternativa para memcpy no manipulação de ponto flutuante -> UNION.

/**
 * Acesso ao frame corrente declarado no modulo frame.h
 */
extern struct frame* frameCorrente;

int naoEmpilhaFlag = 0;

/**
 * o decodificador permite eh um array com informacoes das varias instrucoes\n
 * a partir do opcode da instrucao, pode-se pelo decodificador descobrir o nome e quantos bytes ele ocupa 
 */ 
decodificador dec[NUM_INSTRUCAO];

/**
 * Função que atualiza o valor do program counter do frame corrente.
 * @param void
 * @return void 
 */
void atualizaPc(){

	//atualiza pc
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

/*
 * a funcao recebe uma referencia para a constant pool e a posicao que se deseja acessar
 * a funcao retorna o indice da CONSTANT_UTF8 associada a CONSTANT da posicao passada na constant pool 
 * @param cp_info* uma referencia a constant pool 
 * @param int um indice para a constant pool 
 * @return int indice da CONSTANT_UTF8 associada 
 */
int obtem_utf_eq(cp_info* cp, int pos_pool)
{
    int tag;

    // pega tag 
    tag = cp[pos_pool].tag;

    // se a tag for o de uma UTF8
    if (tag == CONSTANT_Utf8)
    {
        // imprime informacao e sai
        return pos_pool;
    }

    // senao, de acordo com a tag, decide qual sera a proxima posicao da cte pool que iremos olhar
    switch(tag)
    {
        case CONSTANT_Class:
            return obtem_utf_eq(cp, cp[pos_pool].info.Class.name_index - 1);
        case CONSTANT_String:
            return obtem_utf_eq(cp, cp[pos_pool].info.String.string_index - 1); 
        case CONSTANT_Integer: 
            return obtem_utf_eq(cp, cp[pos_pool].info.String.string_index - 1); 
        case CONSTANT_Float: 
            return obtem_utf_eq(cp, cp[pos_pool].info.String.string_index - 1); 
    }
}


/**
 * Função que aponta para uma implementação de cada instrução de acordo
 * com o opcode fornecido.
 * @param void
 * @return void
 */
void newInstrucoes(){
	
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
    push((int32_t)NULL_REF);
    
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
    push(-1);
    
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
	push((int32_t) 0);

	atualizaPc();
}

/**
 * Funcao que empilha 1 na pilha de operandos.
 * @param void
 * @return void 
 */
void iconst_1(){
    // poe 1 na pilha de operandos
    push(1);
    
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
    push(2);
    
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
    push(3);
    
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
    push(4);
    
    // atualiza pc 
    frameCorrente->pc++;
}

/**
 * Funcao que empilha 5 na pilha de operandos.
 * @param void
 * @return void 
 */
void iconst_5(){
    // poe 5 na pilha de operandos
    push(5);
    
    // atualiza pc 
    frameCorrente->pc++;
}

/*
 * a funcao coloca a constante long 0 na pilha de operandos
 * ocupa 2 espacos na pilha 
 * @param void 
 * @return void
 */
void lconst_0(){

    int64_t long0 = 0; 
    int32_t parte_alta;
    int32_t parte_baixa; 

    // pega parte alta e parte baixa do long
	parte_alta = long0 >> 32;
	parte_baixa = long0 & 0xffffffff;
    
    // pela convencao, empilha a parte alta primeiro
    push(parte_alta);

    // pela convencao, empilha a parte baixa depois
    push(parte_baixa);

    // atualiza pc 
    frameCorrente->pc++; 
}

/*
 * a funcao coloca a constante long 1 na pilha de operandos
 * ocupa 2 espacos na pilha
 * @param void
 * @return void
 */
void lconst_1(){

    int64_t long1 = 1; 
    int32_t parte_alta;
    int32_t parte_baixa; 

    // pega parte alta e parte baixa do long
	parte_alta = long1 >> 32;
	parte_baixa = long1 & 0xffffffff;
    
    // pela convencao, empilha a parte alta primeiro
    push(parte_alta);

    // pela convencao, empilha a parte baixa depois
    push(parte_baixa);

    // atualiza pc 
    frameCorrente->pc++;
}

/**
 * Funcao que coloca 0.0 na pilha.
 * @param void
 * @return void 
 */
void fconst_0(){

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
	push(*valPilha);

	atualizaPc();
}

/**
 * Funcao que coloca 1.0 na pilha.
 * @param void
 * @return void 
 */
void fconst_1(){

	//Auxiliar para utilizar o memcpy e não perder precisão com cast.
	int32_t* valPilha;

	//Float com valor zero para ser empilhado.
	float valF = 1.0;

	//Aloca mem para int32.
	valPilha = (int32_t*) malloc(sizeof(int32_t));

	//Importante!! -> copia bytes de um float para um int32
	//para empilhar na forma correta. Ao desempilhar realiza
	//Memcpy de volta para um float.
	memcpy(valPilha, &valF, sizeof(int32_t));
	printf("Valor Empilhado: %d\n",*valPilha);

	//Empilha float na forma de int32 para se adequar ao tipo da pilha.
	push(*valPilha);

	atualizaPc();
}

/**
 * Funcao que coloca 2.0 na pilha.
 * @param void
 * @return void 
 */
void fconst_2(){

	//Auxiliar para utilizar o memcpy e não perder precisão com cast.
	int32_t* valPilha;

	//Float com valor zero para ser empilhado.
	float valF = 2.0;

	//Aloca mem para int32.
	valPilha = (int32_t*) malloc(sizeof(int32_t));

	//Importante!! -> copia bytes de um float para um int32
	//para empilhar na forma correta. Ao desempilhar realiza
	//Memcpy de volta para um float.
	memcpy(valPilha, &valF, sizeof(int32_t));
	printf("Valor Empilhado: %d\n",*valPilha);

	//Empilha float na forma de int32 para se adequar ao tipo da pilha.
	push(*valPilha);

	atualizaPc();
}

/*
 * funcao que empilha o double 0.0 na pilha
 * @param void
 * @return void
 */
void dconst_0(){
    double double0 = 0.0; 
    int64_t temp; 
    int32_t parte_alta;
    int32_t parte_baixa;

    // copia valor de double para o int temp
	memcpy(&temp, &double0, sizeof(int64_t));
    
    // divide temp em parte alta e parte baixa
	parte_alta = temp >> 32;
	parte_baixa = temp & 0xffffffff;
    
    // empilha a parte alta primeiro e depois a baixa
    push(parte_alta);
    push(parte_baixa);

    // atualiza pc 
    frameCorrente->pc++;
}

/*
 * funcao que empilha o double 1.0 na pilha
 * @param void
 * @return void
 */
void dconst_1(){
    double double1 = 1.0; 
    int64_t temp; 
    int32_t parte_alta;
    int32_t parte_baixa;

    // copia valor de double para o int temp
	memcpy(&temp, &double1, sizeof(int64_t));
    
    // divide temp em parte alta e parte baixa
	parte_alta = temp >> 32;
	parte_baixa = temp & 0xffffffff;
    
    // empilha a parte alta primeiro e depois a baixa
    push(parte_alta);
    push(parte_baixa);

    // atualiza pc 
    frameCorrente->pc++;
}

/**
 * Acessa um parametro(8 bits) da instrução em empilha na pilha de operandos.
 * @param void
 * @return void 
 */
void bipush(){
	int8_t argumento = (int8_t) frameCorrente->code[(++frameCorrente->pc)];
	printf("argumento empilhado: %d\n",argumento);
	push((int32_t)argumento);
	
	atualizaPc();
}

/**
 * le dois bytes e poe resultado da concantenacao deles na pilha
 * @param void
 * @return void
 */
void sipush(){
    int32_t byte1, byte2;
    int32_t valor; 

    // pega primeiro byte
	byte1 = frameCorrente->code[(frameCorrente->pc + 1)];
    
    // pega segundo byte
	byte2 = frameCorrente->code[(frameCorrente->pc + 2)];
    
    // obtem short 
    valor = (byte1 << 8) + byte2;
    
    // poe valor no stack de operandos
    push(valor);
    
    atualizaPc();
}

/*
 * a funcao coloca um item da run-time constan pool na pilha 
 * @param void
 * @return void
 */
void ldc(){
    uint32_t indice;
	
    // pega indice 
    indice = frameCorrente->code[frameCorrente->pc + 1];

    // se o indice para a constant pool for para um int ou float
    if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_Float || \
            frameCorrente->constant_pool[indice - 1].tag == CONSTANT_Integer)
    {
        // empilha valor correto
        if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_Float)
        {
            push(frameCorrente->constant_pool[indice - 1].info.Float.bytes);
        }
        else
        {
            push(frameCorrente->constant_pool[indice - 1].info.Integer.bytes);
        }
    }
    
    // se o indice para a constant pool for para uma string
    else if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_String) 
    {
        uint32_t indice_utf;
        indice_utf = obtem_utf_eq(frameCorrente->constant_pool, indice-1); 
        push(indice_utf);
        printf("Valor %d empilhado\n", frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1]);
    }

    // se o indice para a constant pool for uma referencia a uma classe 
    else if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_String) 
    {
        // poe referencia para a classe na constant pool 
        // TODO Resolve nome da classe 
    }

    // se nao for nenhum dos acima, reporta erro e sai
    else
    {
        printf("erro na instrucao ldc\n");
        exit(1);
    }

    atualizaPc();
}


/**
 * a funcao coloca um item da run-time constan pool na pilha 
 * eh semelhante a ldc, mas o indice lido eh um numero de 16 bits ao 
 * inves de 8 
 * @param void
 * @return void
 */
void ldc_w(){
    uint32_t indice;
    
	inicializa_decodificador(dec); 
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

    // pega indice 
    indice = (frameCorrente->code[frameCorrente->pc + 1] << 8 + frameCorrente->code[frameCorrente->pc + 2]);

    // se o indice para a constant pool for para um int ou float
    if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_Float || \
            frameCorrente->constant_pool[indice - 1].tag == CONSTANT_Integer)
    {
        // empilha valor correto
        if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_Float)
        {
            push(frameCorrente->constant_pool[indice - 1].info.Float.bytes);
        }
        else
        {
            push(frameCorrente->constant_pool[indice - 1].info.Integer.bytes);
        }
    }
    
    // se o indice para a constant pool for para uma string
    else if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_String) 
    {
        uint32_t indice_utf;
        indice_utf = obtem_utf_eq(frameCorrente->constant_pool, indice-1); 
        push(indice_utf);
        printf("Valor %d empilhado\n", frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1]);
    }

    // se o indice para a constant pool for uma referencia a uma classe 
    else if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_String) 
    {
        // poe referencia para a classe na constant pool 
        // TODO Resolve nome da classe 
    }

    // se nao for nenhum dos acima, reporta erro e sai
    else
    {
        printf("erro na instrucao ldc\n");
        exit(1);
    }

	// atualiza proxima instrucao 
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;

}

/**
 * Acessa a constant pool num campo de 64 bits e coloca na pilha.
 * @param void
 * @return void 
 */
void ldc2_w(){

	//Pega indice presente na instrução para acesso a constant pool.
	uint8_t indice = frameCorrente->code[frameCorrente->pc + 2];

	//Pega tag da posição da constant pool dada pelo indice
	//Pode ser ou long ou double.
	uint8_t tag = (frameCorrente->constant_pool[indice-1]).tag;

	//TODO LONG

	//Se tag é 6 (double) acessa high bytes e low bytes e empilha.
	if(tag == 6){
		uint32_t alta = frameCorrente->constant_pool[indice-1].info.Double.high_bytes;
		uint32_t baixa = frameCorrente->constant_pool[indice-1].info.Double.low_bytes;
		printf("Parte alta empilhada: %d\n",alta);
		printf("Parte baixa empilhada: %d\n",baixa);
		push(alta);
		push(baixa);
	}

	atualizaPc();

}

/**
 * funcao carrega um inteira do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void iload(){

	// TODO: The iload opcode can be used in conjunction with the wide
	// instruction (§wide) to access a local variable using a two-byte
	// bunsigned index.

	int32_t argumento = (int32_t) frameCorrente->code[frameCorrente->pc + 1];
	int32_t aux = frameCorrente->fields[argumento];
	printf("argumento empilhado: %d\n",argumento);
	push(aux);

	atualizaPc();

}

/**
 * a funcao carrega um long do array de var locais a pilha de operandos
 * @param void
 * @return void
 */
void lload(){

    // TODO pq ta diferente do iload na parte de conseguir os bytes
    int32_t indice;
    int32_t parte_alta, parte_baixa;

    // pega indice
    indice = frameCorrente->code[frameCorrente->pc + 1];

    // empilha a parte alta - por convencao vem primeiro
    parte_alta = frameCorrente->fields[indice];
    push(parte_alta);

    // empilha a parte baixa
    parte_baixa = frameCorrente->fields[indice + 1];
    push(parte_baixa);

    atualizaPc();
}

/** 
 * a funcao carrega um float no array de variaveis locais da pilha
 * @param void
 * @return void
 */
void fload(){

    int32_t indice, valor; 

    // pega indice 
    indice = frameCorrente->code[frameCorrente->pc + 1];
    
    // empilha 
    valor = frameCorrente->fields[indice];
    push(valor);
    
    atualizaPc();
}

/**
 * a funcao carrega um double no array de variaveis locais da pilha 
 * @param void
 * @return void
 */
void dload(){
    // TODO pq ta diferente do iload na parte de conseguir os bytes
    int32_t indice;
    int32_t parte_alta, parte_baixa;

    // pega indice
    indice = frameCorrente->code[frameCorrente->pc + 1];

    // empilha a parte alta - por convencao eh empilhada primeiro
    parte_alta = frameCorrente->fields[indice];
    push(parte_alta);

    // empilha a parte baixa
    parte_baixa = frameCorrente->fields[indice + 1];
    push(parte_baixa);

    atualizaPc();
}

/**
 * a funcao carrega uma referencia do array de variaveis locais da pilha
 * @param void
 * @return void
 */
void aload(){

    int32_t indice, valor; 

    // pega indice 
    indice = frameCorrente->code[frameCorrente->pc + 1];
    
    // empilha 
    valor = frameCorrente->fields[indice];
    push(valor);
    
    atualizaPc();

}

/**
 * a funcao carrega o int na posicao 0 do array de variaveis locais para a pilha de operandos
 * @param void
 * @return void
 */
void iload_0(){

    int32_t valor;

    // pega valor do array de var local na posicao 2
    valor = frameCorrente->fields[0];

    // poe valor na pilha de operandos
    push(valor);
    
	atualizaPc();
}

/** 
 * a funcao carrega o int na posicao 1 do array de variaveis locais para a pilha de operandos
 * @param void
 * @return void
 */
void iload_1(){

    int32_t valor;

    // pega valor do array de var local na posicao 1
    valor = frameCorrente->fields[1];

    // poe valor na pilha de operandos
    push(valor);
    
    atualizaPc();
}

/** 
 * a funcao carrega o int na posicao 2 do array de variaveis locais para a pilha de operandos
 * @param void
 * @return void
 */
void iload_2(){

    int32_t valor;

    // pega valor do array de var local na posicao 2
    valor = frameCorrente->fields[2];

    // poe valor na pilha de operandos
    push(valor);
    
    atualizaPc();
}

/**
 * a funcao carrega o int na posicao 3 do array de variaveis locais para a pilha de operandos
 * @param void
 * @return void
 */
void iload_3(){
    int32_t valor;

    // pega valor do array de var local na posicao 3
    valor = frameCorrente->fields[3];

    // poe valor na pilha de operandos
    push(valor);
    
    atualizaPc();

}

/**
 * a funcao carrega o long da posicao 0/1 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 **/
void lload_0(){

    int32_t indice;
    int32_t parte_alta, parte_baixa;

    // pega indice
    indice = 0;

    // empilha a parte alta - por convencao vem primeiro
    parte_alta = frameCorrente->fields[indice];
    push(parte_alta);

    // empilha a parte baixa
    parte_baixa = frameCorrente->fields[indice + 1];
    push(parte_baixa);

	atualizaPc();

}

/**
 * a funcao carrega o long da posicao 1/2 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void lload_1(){
    int32_t indice;
    int32_t parte_alta, parte_baixa;

    // pega indice
    indice = 1;

    // empilha a parte alta - por convencao vem primeiro
    parte_alta = frameCorrente->fields[indice];
    push(parte_alta);

    // empilha a parte baixa
    parte_baixa = frameCorrente->fields[indice + 1];
    push(parte_baixa);

    atualizaPc();

}

/**
 * a funcao carrega o long da posicao 2/3 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void lload_2(){
    int32_t indice;
    int32_t parte_alta, parte_baixa;

    // pega indice
    indice = 2;

    // empilha a parte alta - por convencao vem primeiro
    parte_alta = frameCorrente->fields[indice];
    push(parte_alta);

    // empilha a parte baixa
    parte_baixa = frameCorrente->fields[indice + 1];
    push(parte_baixa);

   atualizaPc();

}

/**
 * a funcao carrega o long da posicao 3/4 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void lload_3(){
    int32_t indice;
    int32_t parte_alta, parte_baixa;

    // pega indice
    indice = 3;

    // empilha a parte alta - por convencao vem primeiro
    parte_alta = frameCorrente->fields[indice];
    push(parte_alta);

    // empilha a parte baixa
    parte_baixa = frameCorrente->fields[indice + 1];
    push(parte_baixa);

    atualizaPc();

}

/**
 * a funcao carrega o float da posicao 0 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void fload_0(){

    int32_t indice, valor; 

    // pega indice 
    indice = 0; 
    
    // empilha 
    valor = frameCorrente->fields[indice];
    push(valor);
    
   atualizaPc();

}

/**
 * a funcao carrega o float da posicao 1 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void fload_1(){
    int32_t indice, valor; 

    // pega indice 
    indice = 1; 
    
    // empilha 
    valor = frameCorrente->fields[indice];
    push(valor);
    
    atualizaPc();

}

/**
 * a funcao carrega o float da posicao 2 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void fload_2(){
    int32_t indice, valor; 

    // pega indice 
    indice = 2; 
    
    // empilha 
    valor = frameCorrente->fields[indice];
    push(valor);
    
    atualizaPc();

}

/**
 * a funcao carrega o float da posicao 3 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void fload_3(){
    int32_t indice, valor; 

    // pega indice 
    indice = 3; 
    
    // empilha 
    valor = frameCorrente->fields[indice];
    push(valor);
    
    atualizaPc();

}

/**
 * a funcao carrega o double da posicao 0/1 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void dload_0(){
    int32_t indice;
    int32_t parte_alta, parte_baixa;

    // pega indice
    indice = 0; 

    // empilha a parte alta - por convencao eh empilhada primeiro
    parte_alta = frameCorrente->fields[indice];
    push(parte_alta);

    // empilha a parte baixa
    parte_baixa = frameCorrente->fields[indice + 1];
    push(parte_baixa);

    atualizaPc();

}

/**
 * a funcao carrega o double da posicao 1/2 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void dload_1(){
    int32_t indice;
    int32_t parte_alta, parte_baixa;

    // pega indice
    indice = 1; 

    // empilha a parte alta - por convencao eh empilhada primeiro
    parte_alta = frameCorrente->fields[indice];
    push(parte_alta);

    // empilha a parte baixa
    parte_baixa = frameCorrente->fields[indice + 1];
    push(parte_baixa);

    atualizaPc();

}

/**
 * a funcao carrega o double da posicao 2/3 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void dload_2(){
    int32_t indice;
    int32_t parte_alta, parte_baixa;

    // pega indice
    indice = 2; 

    // empilha a parte alta - por convencao eh empilhada primeiro
    parte_alta = frameCorrente->fields[indice];
    push(parte_alta);

    // empilha a parte baixa
    parte_baixa = frameCorrente->fields[indice + 1];
    push(parte_baixa);

    atualizaPc();

}

/**
 * a funcao carrega o double da posicao 3/4 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void dload_3(){
    int32_t indice;
    int32_t parte_alta, parte_baixa;

    // pega indice
    indice = 3; 

    // empilha a parte alta - por convencao eh empilhada primeiro
    parte_alta = frameCorrente->fields[indice];
    push(parte_alta);

    // empilha a parte baixa
    parte_baixa = frameCorrente->fields[indice + 1];
    push(parte_baixa);

   atualizaPc();

}

/**
 * Acessa posição 0 do array de var local e empilha na pilha de operandos.
 * @param void
 * @return void 
 */
void aload_0(){
	//Empilha a posição 0 do vetor de variáveis locais.
	push(frameCorrente->fields[0]);
	atualizaPc();
}

/**
 * a funcao acessa a posicao 1 do array de var local e empilha o conteudo na pilha de operandos
 * @param void
 * @return voi
 */
void aload_1(){
    int32_t indice, valor; 

    // pega indice 
    indice = 1; 
    
    // empilha 
    valor = frameCorrente->fields[indice];
    push(valor);
    
    atualizaPc();
}

/**
 * a funcao acessa a posicao 2 do array de var local e empilha o conteudo na pilha de operandos
 * @param void
 * @return voi
 */
void aload_2(){
    int32_t indice, valor; 

    // pega indice 
    indice = 2; 
    
    // empilha 
    valor = frameCorrente->fields[indice];
    push(valor);
    
   atualizaPc();
}
/**
 * a funcao acessa a posicao 3 do array de var local e empilha o conteudo na pilha de operandos
 * @param void
 * @return voi
 */
void aload_3(){
    int32_t indice, valor; 

    // pega indice 
    indice = 3; 
    
    // empilha 
    valor = frameCorrente->fields[indice];
    push(valor);
    
    atualizaPc();

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

/*
 * pega inteiro e coloca no array de variaveis locais, na posicao dada por indice
 * @param void
 * @return void
 */
void istore(){

    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = frameCorrente->code[frameCorrente->pc + 1];
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    atualizaPc();
}

/* 
 * pega long e coloca no array de variaveis locais, na posicao dada por indice e indice + 1
 * @param void
 * @return void
 */
void lstore(){

    //TODO nao precisa de casting nesse caso, ne?
    int32_t indice; 
    int32_t parte_alta, parte_baixa; 

    // pega indice 
    indice = frameCorrente->code[frameCorrente->pc + 1];
    
    // desempilha a parte baixa - por convencao desempilhada primeiro 
    parte_baixa = pop_op();

    // desempilha a parte alta 
    parte_alta = pop_op();

    // poe parte alta e baixa no array de var locais
    // pela convencao a parte alta vem primeiro
    frameCorrente->fields[indice] = parte_alta;
    frameCorrente->fields[indice + 1] = parte_baixa;

    atualizaPc();
}

/* 
 * pega float e coloca no array de variaveis locais, na posicao dada por indice
 * @param void
 * @return void
 */
void fstore(){

    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = frameCorrente->code[frameCorrente->pc + 1];
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    atualizaPc();
}

/* 
 * pega double e coloca no array de variaveis locais, na posicao dada por indice e indice + 1
 * @param void
 * @return void
 */
void dstore(){
    int32_t indice; 
    int32_t parte_alta, parte_baixa; 

    // pega indice 
    indice = frameCorrente->code[frameCorrente->pc + 1];
    
    // desempilha a parte baixa - por convencao desempilhada primeiro 
    parte_baixa = pop_op();

    // desempilha a parte alta 
    parte_alta = pop_op();

    // poe parte alta e baixa no array de var locais
    // pela convencao a parte alta vem primeiro
    frameCorrente->fields[indice] = parte_alta;
    frameCorrente->fields[indice + 1] = parte_baixa;

    atualizaPc();
}

/* 
 * pega referencia e coloca no array de variaveis locais, na posicao dada por indice
 * @param void
 * @return void
 */
void astore(){

    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = frameCorrente->code[frameCorrente->pc + 1];
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    atualizaPc();
}

/*
 * pega inteiro e coloca na posicao 0 do array de variaveis locais
 * @param void
 * @return void
 */
void istore_0(){

    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = 0;
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    atualizaPc();
}

/**
 * a funcao coloca um int no array de variaveis locais
 * @param void
 * @return void
 */
void istore_1(){
    uint32_t valor; 

    // pega valor no topo da operand stack
    valor = pop_op();

    // coloca o valor na posicao 1 do array de variaveis locais
    frameCorrente->fields[1] = valor;

    atualizaPc();
}

/*
 * pega inteiro e coloca na posicao 2 do array de variaveis locais
 * @param void
 * @return void
 */
void istore_2(){
    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = 2;
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    atualizaPc();
}

/*
 * pega inteiro e coloca na posicao 3 do array de variaveis locais
 * @param void
 * @return void
 */
void istore_3(){
    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = 3;
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    atualizaPc();
}

/* 
 * pega long e coloca no array de variaveis locais, na posicao 0 e 1
 * @param void
 * @return void
 */
void lstore_0(){

    int32_t indice; 
    int32_t parte_alta, parte_baixa; 

    // pega indice 
    indice = 0;
    
    // desempilha a parte baixa - por convencao desempilhada primeiro 
    parte_baixa = pop_op();

    // desempilha a parte alta 
    parte_alta = pop_op();

    // poe parte alta e baixa no array de var locais
    // pela convencao a parte alta vem primeiro
    frameCorrente->fields[indice] = parte_alta;
    frameCorrente->fields[indice + 1] = parte_baixa;

    atualizaPc();
}

/* 
 * pega long e coloca no array de variaveis locais, na posicao 1 e 2
 * @param void
 * @return void
 */
void lstore_1(){
    int32_t indice; 
    int32_t parte_alta, parte_baixa; 

    // pega indice 
    indice = 1;
    
    // desempilha a parte baixa - por convencao desempilhada primeiro 
    parte_baixa = pop_op();

    // desempilha a parte alta 
    parte_alta = pop_op();

    // poe parte alta e baixa no array de var locais
    // pela convencao a parte alta vem primeiro
    frameCorrente->fields[indice] = parte_alta;
    frameCorrente->fields[indice + 1] = parte_baixa;

    atualizaPc();
}

/* 
 * pega long e coloca no array de variaveis locais, na posicao 2 e 3
 * @param void
 * @return void
 */
void lstore_2(){
    int32_t indice; 
    int32_t parte_alta, parte_baixa; 

    // pega indice 
    indice = 2;
    
    // desempilha a parte baixa - por convencao desempilhada primeiro 
    parte_baixa = pop_op();

    // desempilha a parte alta 
    parte_alta = pop_op();

    // poe parte alta e baixa no array de var locais
    // pela convencao a parte alta vem primeiro
    frameCorrente->fields[indice] = parte_alta;
    frameCorrente->fields[indice + 1] = parte_baixa;

    atualizaPc();
}

/* 
 * pega long e coloca no array de variaveis locais, na posicao 3 e 4
 * @param void
 * @return void
 */
void lstore_3(){
    int32_t indice; 
    int32_t parte_alta, parte_baixa; 

    // pega indice 
    indice = 3;
    
    // desempilha a parte baixa - por convencao desempilhada primeiro 
    parte_baixa = pop_op();

    // desempilha a parte alta 
    parte_alta = pop_op();

    // poe parte alta e baixa no array de var locais
    // pela convencao a parte alta vem primeiro
    frameCorrente->fields[indice] = parte_alta;
    frameCorrente->fields[indice + 1] = parte_baixa;

    atualizaPc();
}


/* 
 * pega float e coloca no array de variaveis locais na posicao 0
 * @param void
 * @return void
 */
void fstore_0(){
    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = 0;
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    // incrementa pc
    atualizaPc();

}

/* 
 * pega float e coloca no array de variaveis locais na posicao 1
 * @param void
 * @return void
 */
void fstore_1(){
    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = 1;
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    // incrementa pc
    atualizaPc();
}

/* 
 * pega float e coloca no array de variaveis locais na posicao 2
 * @param void
 * @return void
 */
void fstore_2(){
    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = 2;
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    // incrementa pc
    atualizaPc();

}

/* 
 * pega float e coloca no array de variaveis locais na posicao 3
 * @param void
 * @return void
 */
void fstore_3(){
    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = 3;
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    // incrementa pc
    atualizaPc();

}

/* 
 * pega double e coloca no array de variaveis locais, na posicao iniciada em 0 
 * @param void
 * @return void
 */
void dstore_0(){
    int32_t indice; 
    int32_t parte_alta, parte_baixa; 

    // pega indice 
    indice = 0;
    
    // desempilha a parte baixa - por convencao desempilhada primeiro 
    parte_baixa = pop_op();

    // desempilha a parte alta 
    parte_alta = pop_op();

    // poe parte alta e baixa no array de var locais
    // pela convencao a parte alta vem primeiro
    frameCorrente->fields[indice] = parte_alta;
    frameCorrente->fields[indice + 1] = parte_baixa;

    // incrementa pc
    atualizaPc();
}

/* 
 * pega double e coloca no array de variaveis locais, na posicao iniciada em 1 
 * @param void
 * @return void
 */
void dstore_1(){
    int32_t indice; 
    int32_t parte_alta, parte_baixa; 

    // pega indice 
    indice = 1;
    
    // desempilha a parte baixa - por convencao desempilhada primeiro 
    parte_baixa = pop_op();

    // desempilha a parte alta 
    parte_alta = pop_op();

    // poe parte alta e baixa no array de var locais
    // pela convencao a parte alta vem primeiro
    frameCorrente->fields[indice] = parte_alta;
    frameCorrente->fields[indice + 1] = parte_baixa;

    // incrementa pc
    atualizaPc();

}

/* 
 * pega double e coloca no array de variaveis locais, na posicao iniciada em 2 
 * @param void
 * @return void
 */
void dstore_2(){
    int32_t indice; 
    int32_t parte_alta, parte_baixa; 

    // pega indice 
    indice = 2;
    
    // desempilha a parte baixa - por convencao desempilhada primeiro 
    parte_baixa = pop_op();

    // desempilha a parte alta 
    parte_alta = pop_op();

    // poe parte alta e baixa no array de var locais
    // pela convencao a parte alta vem primeiro
    frameCorrente->fields[indice] = parte_alta;
    frameCorrente->fields[indice + 1] = parte_baixa;

    // incrementa pc
    atualizaPc();

}

/* 
 * pega double e coloca no array de variaveis locais, na posicao iniciada em 3 
 * @param void
 * @return void
 */
void dstore_3(){
    int32_t indice; 
    int32_t parte_alta, parte_baixa; 

    // pega indice 
    indice = 2;
    
    // desempilha a parte baixa - por convencao desempilhada primeiro 
    parte_baixa = pop_op();

    // desempilha a parte alta 
    parte_alta = pop_op();

    // poe parte alta e baixa no array de var locais
    // pela convencao a parte alta vem primeiro
    frameCorrente->fields[indice] = parte_alta;
    frameCorrente->fields[indice + 1] = parte_baixa;

    // incrementa pc
    atualizaPc();

}


/* 
 * pega referencia e coloca no array de variaveis locais, na posicao 0
 * @param void
 * @return void
 */
void astore_0(){
    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = 0;
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    atualizaPc();

}

/* 
 * pega referencia e coloca no array de variaveis locais, na posicao dada por 1
 * @param void
 * @return void
 */
void astore_1(){
    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = 1;
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    // incrementa pc
    atualizaPc();

}

/* 
 * pega referencia e coloca no array de variaveis locais, na posicao dada por 2
 * @param void
 * @return void
 */
void astore_2(){
    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = 2;
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    // incrementa pc
    atualizaPc();

}

/* 
 * pega referencia e coloca no array de variaveis locais, na posicao dada por 3
 * @param void
 * @return void
 */
void astore_3(){
    int32_t indice; 
    int32_t valor; 

    // pega indice 
    indice = 3;
    
    // desempilha 
    valor = pop_op(); 

    // poe o valor na posicao no array de var locais
    frameCorrente->fields[indice] = valor; 

    // incrementa pc
    atualizaPc();

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
	pop_op();

	atualizaPc();
}

/**
 * Funcao que desempilha dois valores da pilha de operandos.
 * @param void
 * @return void 
 */
void pop2(){
	//Desempilha os dois valores
	pop_op();
	pop_op();

	atualizaPc();
}

/**
 * Instrução que retira valor da pilha e adiciona de volta duplicado.
 * @param void
 * @return void 
 */
void dup(){
	int32_t aux;

	//Desempilha
	aux = pop_op();

	//Duplica
	push(aux);
	push(aux);
	
	atualizaPc();
}

/**
 * Instrução que duplica valor da pilha e adiciona de volta de forma que se repita de forma nao ordenada.
 * @param void
 * @return void
 */
void dup_x1(){

	printf("Entrei no dup\n");
	int32_t aux1, aux2;

	//Desempilha
	aux2 = pop_op();

	aux1 = pop_op();

	//Duplica
	push(aux1);
	printf("Valor %d empilhado\n",frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1]);
	push(aux2);
	printf("Valor %d empilhado\n",frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1]);
	push(aux1);

	atualizaPc();
}
void dup_x2(){

}
void dup2(){

}
void dup2_x1(){

}
void dup2_x2(){

}

/**
 * Desempilha dois valores da pilha e troca de posição um com o outro.
 * @param void
 * @return void 
 */
void swap(){
	int32_t val1,val2;

	//Desempilha os dois valores
	val1 = pop_op();
	val2 = pop_op();

	//Troca sua posições.
	push(val1);
	push(val2);

	atualizaPc();
}

/**
 * Funcao desempilha dois valores inteiros, soma-os e empilha resultado.
 * @param void
 * @return void 
 */
void iadd(){
	int32_t v1,v2;
	v1 = pop_op();
	v2 = pop_op();
	
	push(v1+v2);

	atualizaPc();
}

/**
 * Funcao desempilha dois valores long, soma-os e empilha resultado.
 * @param void
 * @return void 
 */
void ladd(){
	int32_t baixa,alta;

	baixa = pop_op();
	alta = pop_op();

	//Converter os numeros 32 bits para 64 bits(long)

	//Atribui parte alta primeiro
	int64_t lVal = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	lVal <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	lVal = lVal + baixa;

	baixa = pop_op();
	alta = pop_op();

	//Converter os numeros 32 bits para 64 bits(long)

	//Atribui parte alta primeiro
	int64_t lVal1 = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	lVal1 <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	lVal1 = lVal1 + baixa;

	//Soma os dois valores
	int64_t resultado = lVal1 + lVal;

	//Empilha o resultado

	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	//finalmente empilha.
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * Funcao desempilha dois valores float, soma-os e empilha resultado.
 * @param void
 * @return void 
 */
void fadd(){
	float fVal1,fVal2;

	//Desempilha os dois valores
	int32_t aux1 = pop_op();
	int32_t aux2 = pop_op();

	//Converte para float e nao perde precisao
	memcpy(&fVal1, &aux1, sizeof(int32_t));
	memcpy(&fVal2, &aux2, sizeof(int32_t));

	//Soma os dois valores em float
	float resultado = fVal1 + fVal2;

	//copia para um int32_t
	int32_t retPilha;
	memcpy(&retPilha, &resultado, sizeof(int32_t));

	//Empilha
	push(retPilha);

	atualizaPc();

}

/**
 * Desempilha dois valores, soma e empilha dois valores double.
 * @param void
 * @return void 
 */
void dadd(){
	//Parte alta e baixa do double.
	int32_t alta;
	int32_t baixa;

	//Obtem parte baixa primeiro -> Foi empilhada por ultimo(topo)
	baixa = pop_op();
	alta = pop_op();

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
	baixa = pop_op();
	alta = pop_op();

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
	double doubleSomado = valorDouble1 + valorDouble2;
	
	//Necessario converter mais uma vez o double somado para int64 para 
	//empilhar corretamente.
	int64_t valorPilha;
	memcpy(&valorPilha, &doubleSomado, sizeof(int64_t));

	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = valorPilha >> 32;
	baixa = valorPilha & 0xffffffff;

	//finalmente empilha.
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * Funcao desempilha dois valores inteiros, subtrai e empilha resultado.
 * @param void
 * @return void 
 */
void isub(){
	int32_t v1,v2;
	v1 = pop_op();
	v2 = pop_op();

	push(v1-v2);

	atualizaPc();

}

/**
 * Funcao desempilha dois valores long, subtrai e empilha resultado.
 * @param void
 * @return void
 */
void lsub(){
	int32_t baixa,alta;

	baixa = pop_op();
	alta = pop_op();

	//Converter os numeros 32 bits para 64 bits(long)

	//Atribui parte alta primeiro
	int64_t lVal = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	lVal <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	lVal = lVal + baixa;

	baixa = pop_op();
	alta = pop_op();

	//Converter os numeros 32 bits para 64 bits(long)

	//Atribui parte alta primeiro
	int64_t lVal1 = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	lVal1 <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	lVal1 = lVal1 + baixa;

	//subtrai os dois valores
	int64_t resultado = lVal1 - lVal;
	//Empilha o resultado


	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	//finalmente empilha.
	push(alta);
	push(baixa);


	atualizaPc();
}

/**
 * Funcao desempilha dois valores float, subtrai e empilha resultado.
 * @param void
 * @return void
 */
void fsub(){
	float fVal1,fVal2;

	//Desempilha os dois valores
	int32_t aux1 = pop_op();
	int32_t aux2 = pop_op();

	//Converte para float e nao perde precisao
	memcpy(&fVal1, &aux1, sizeof(int32_t));
	memcpy(&fVal2, &aux2, sizeof(int32_t));

	//subtrai os dois valores em float
	float resultado = fVal1 - fVal2;

	//copia para um int32_t
	int32_t retPilha;
	memcpy(&retPilha, &resultado, sizeof(int32_t));

	//Empilha
	push(retPilha);

	atualizaPc();
}

/**
 * Desempilha 2 valores double da pilha, subtrai e empilha o resultado.
 * @param void
 * @return void 
 */
void dsub(){
	//Parte alta e baixa do double.
	int32_t alta;
	int32_t baixa;

	//Obtem parte baixa primeiro -> Foi empilhada por ultimo(topo)
	baixa = pop_op();
	alta = pop_op();

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
	baixa = pop_op();
	alta = pop_op();

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
	double doubleSubtraido = valorDouble1 - valorDouble2;
	
	//Necessario converter mais uma vez o double somado para int64 para 
	//empilhar corretamente.
	int64_t valorPilha;
	memcpy(&valorPilha, &doubleSubtraido, sizeof(int64_t));

	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = valorPilha >> 32;
	baixa = valorPilha & 0xffffffff;

	//finalmente empilha.
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * Desempilha 2 valores da pilha, multiplica-os e empilha o resultado.
 * @param void
 * @return void 
 */
void imul(){
	int32_t v1 = pop_op();
	int32_t v2 = pop_op();

	push((int32_t)(v1 * v2));
	 
	atualizaPc();
}

/**
 * Desempilha 2 valores da pilha, multiplica-os e empilha o resultado.
 * @param void
 * @return void
 */
void lmul(){

	int32_t baixa,alta;

	baixa = pop_op();
	alta = pop_op();

	//Converter os numeros 32 bits para 64 bits(long)

	//Atribui parte alta primeiro
	int64_t lVal = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	lVal <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	lVal = lVal + baixa;

	baixa = pop_op();
	alta = pop_op();

	//Converter os numeros 32 bits para 64 bits(long)

	//Atribui parte alta primeiro
	int64_t lVal1 = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	lVal1 <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	lVal1 = lVal1 + baixa;

	//multiplica os dois valores
	int64_t resultado = lVal1 * lVal;
	//Empilha o resultado


	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	//finalmente empilha.
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * Desempilha 2 valores da pilha, multiplica-os e empilha o resultado.
 * @param void
 * @return void
 */
void fmul(){
	float fVal1,fVal2;

	//Desempilha os dois valores
	int32_t aux1 = pop_op();
	int32_t aux2 = pop_op();

	//Converte para float e nao perde precisao
	memcpy(&fVal1, &aux1, sizeof(int32_t));
	memcpy(&fVal2, &aux2, sizeof(int32_t));

	//multiplica os dois valores em float
	float resultado = fVal1 * fVal2;

	//copia para um int32_t
	int32_t retPilha;
	memcpy(&retPilha, &resultado, sizeof(int32_t));

	//Empilha
	push(retPilha);

	atualizaPc();
}

/**
 * Desempilha 2 valores double da pilha, multiplica-os e empilha o resultado.
 * @param void
 * @return void 
 */
void dmul(){
	//Parte alta e baixa do double.
	int32_t alta;
	int32_t baixa;

	//Obtem parte baixa primeiro -> Foi empilhada por ultimo(topo)
	baixa = pop_op();
	alta = pop_op();

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
	baixa = pop_op();
	alta = pop_op();

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
	double doubleMultiplicado = valorDouble1 * valorDouble2;
	
	//Necessario converter mais uma vez o double somado para int64 para 
	//empilhar corretamente.
	int64_t valorPilha;
	memcpy(&valorPilha, &doubleMultiplicado, sizeof(int64_t));

	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = valorPilha >> 32;
	baixa = valorPilha & 0xffffffff;

	//finalmente empilha.
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * Desempilha 2 valores da pilha, divide-os e empilha o resultado.
 * @param void
 * @return void 
 */
void idiv(){
	int32_t v1 = pop_op();
	int32_t v2 = pop_op();

	push((int32_t)(v1 / v2));
	 
	atualizaPc();
}

void ins_ldiv(){

}
void fdiv(){
	float fVal1,fVal2;

	//Desempilha os dois valores
	int32_t aux1 = pop_op();
	int32_t aux2 = pop_op();

	//Converte para float e nao perde precisao
	memcpy(&fVal1, &aux1, sizeof(int32_t));
	memcpy(&fVal2, &aux2, sizeof(int32_t));

	//multiplica os dois valores em float
	float resultado = fVal1 / fVal2;

	//copia para um int32_t
	int32_t retPilha;
	memcpy(&retPilha, &resultado, sizeof(int32_t));

	//Empilha
	push(retPilha);

	atualizaPc();
}

/**
 * Desempilha dois valores double da pilha divide e empilha o resultado,
 * @param void
 * @return void 
 */
void ddiv(){
	//Partes altas e baixas dos dois doubles.
	int32_t alta,baixa,alta1,baixa1;

	baixa1 = pop_op();
	alta1 = pop_op();

	baixa = pop_op();
	alta = pop_op();

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
	
	//Necessario converter mais uma vez o double somado para int64 para 
	//empilhar corretamente.
	int64_t pilhaVal;
	memcpy(&pilhaVal, &resultado, sizeof(int64_t));

	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = pilhaVal >> 32;
	baixa = pilhaVal & 0xffffffff;

	//finalmente empilha.
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * Desempilha 2 valores inteiros da pilha, obtem o resto da divisao e empilha o resultado.
 * @param void
 * @return void 
 */
void irem(){
	int32_t v1 = pop_op();
	int32_t v2 = pop_op();

	push((int32_t)(v1 % v2));

	atualizaPc();
}

void lrem(){

}

/**
 * Desempilha 2 valores float da pilha, obtem o resto da divisao e empilha o resultado.
 * @param void
 * @return void 
 */
void frem(){
	float fVal1,fVal2;

	//Desempilha os dois valores
	int32_t aux1 = pop_op();
	int32_t aux2 = pop_op();

	//Converte para float e nao perde precisao
	memcpy(&fVal1, &aux1, sizeof(int32_t));
	memcpy(&fVal2, &aux2, sizeof(int32_t));

	//multiplica os dois valores em float
	float resultado = fmodf(fVal1,fVal2);

	//copia para um int32_t
	int32_t retPilha;
	memcpy(&retPilha, &resultado, sizeof(int32_t));

	//Empilha
	push(retPilha);

	atualizaPc();
}

/**
 * Desempilha 2 valores double da pilha, obtem o resto da divisao e empilha o resultado.
 * @param void
 * @return void 
 */
void _drem(){
	//Partes altas e baixas dos dois doubles.
	int32_t alta,baixa,alta1,baixa1;

	baixa1 = pop_op();
	alta1 = pop_op();

	baixa = pop_op();
	alta = pop_op();

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

	double resultado = fmod(v2,v1);
	
	//Necessario converter mais uma vez o double somado para int64 para 
	//empilhar corretamente.
	int64_t pilhaVal;
	memcpy(&pilhaVal, &resultado, sizeof(int64_t));

	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = pilhaVal >> 32;
	baixa = pilhaVal & 0xffffffff;

	//finalmente empilha.
	push(alta);
	push(baixa);

	atualizaPc();

}

/**
 * Desempilha um int ,negativa e empilha o resultado.
 * @param void
 * @return void 
 */
void ineg(){
	//Desempilha valor da pilha
	int32_t retPilha = pop_op();
	//Negativa.
	int32_t aux = -retPilha;
	
	//Empilha valor negativado.
	push(aux);

	atualizaPc();
}

/**
 * Desempilha um long(do java -> no c long tem 32bits), negativa e empilha o resultado.
 * @param void
 * @return void 
 */
void lneg(){
	int32_t baixa,alta;

	//Desempilha parte alta e baixa de um long da pilha
	baixa = pop_op();
	alta = pop_op();

	//Converter os numeros 32 bits para 64 bits(long)

	//Atribui parte alta primeiro
	int64_t lVal = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	lVal <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	lVal = lVal + baixa;

	//Negativa o valor
	lVal = - lVal;

	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = lVal >> 32;
	baixa = lVal & 0xffffffff;

	//finalmente empilha.
	printf("Parte alta empilhada: %d\n",alta);
	printf("Parte baixa empilhada: %d\n",baixa);
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * Desempilha um float ,negativa e empilha o resultado.
 * @param void
 * @return void 
 */
void fneg(){
	float fVal;
	//Obtem valor da pilha em int32_t
	int32_t retPilha = pop_op();

	//Copia bits para um float para nao perder precisao -> Alternativa UNION
	memcpy(&fVal,&retPilha,sizeof(float));

	//Negativa o valor.
	fVal = - fVal;

	//Copia  bits para um int32_t para empilhar corretamente e n perder precisao.
	memcpy(&retPilha,&fVal,sizeof(int32_t));

	//Empilha valor de ponto flutuante em int32_t
	push(retPilha);

	atualizaPc();
}

/**
 * Desempilha um double ,negativa e empilha o resultado.
 * @param void
 * @return void 
 */
void dneg(){

	int32_t baixa,alta;

	//Desempilha parte alta e baixa do valor double
	baixa = pop_op();
	alta = pop_op();

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

	//Negativo o valor double
	valorDouble1 = - valorDouble1;

	//Copio os bytes para um int64_t para nao perder precisao.
	memcpy(&dVal, &valorDouble1, sizeof(int64_t));

	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = dVal >> 32;
	baixa = dVal & 0xffffffff;

	//finalmente empilha.
	printf("Parte alta empilhada: %d\n",alta);
	printf("Parte baixa empilhada: %d\n",baixa);
	push(alta);
	push(baixa);

	atualizaPc();
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

/**
 * Funcao desempilha dois valores inteiros, opera com o and e empilha resultado.
 * @param void
 * @return void
 */
void iand(){

	printf("Entrei no iand\n");

	int32_t pop1 = pop_op();

	int32_t pop2 = pop_op();

	int32_t aux = pop1 & pop2;

	push(aux);

	//atualiza pc
	frameCorrente->pc++;

}

/**
 * Funcao desempilha dois valores long, opera com o and e empilha resultado.
 * @param void
 * @return void
 */
void land(){

	int32_t baixa,alta;

	baixa = pop_op();
	alta = pop_op();

	//Converter os numeros 32 bits para 64 bits(long)

	//Atribui parte alta primeiro
	int64_t lVal = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	lVal <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	lVal = lVal + baixa;

	baixa = pop_op();
	alta = pop_op();

	//Converter os numeros 32 bits para 64 bits(long)

	//Atribui parte alta primeiro
	int64_t lVal1 = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	lVal1 <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	lVal1 = lVal1 + baixa;


	int64_t resultado = lVal1 & lVal;
	//Empilha o resultado


	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	//finalmente empilha.
	printf("Parte alta empilhada: %d\n",alta);
	printf("Parte baixa empilhada: %d\n",baixa);
	push(alta);
	push(baixa);

	//atualiza pc
	inicializa_decodificador(dec);
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

/**
 * Funcao desempilha dois valores inteiros, opera com o or e empilha resultado.
 * @param void
 * @return void
 */
void ior(){

	printf("Entrei no ior\n");

	int32_t pop1 = pop_op();

	int32_t pop2 = pop_op();

	int32_t aux = pop1 | pop2;

	push(aux);

	//atualiza pc
	frameCorrente->pc++;

}

/**
 * Funcao desempilha dois valores long, opera com o or e empilha resultado.
 * @param void
 * @return void
 */
void lor(){

	int32_t baixa,alta;

	baixa = pop_op();
	alta = pop_op();

	//Converter os numeros 32 bits para 64 bits(long)

	//Atribui parte alta primeiro
	int64_t lVal = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	lVal <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	lVal = lVal + baixa;

	baixa = pop_op();
	alta = pop_op();

	//Converter os numeros 32 bits para 64 bits(long)

	//Atribui parte alta primeiro
	int64_t lVal1 = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	lVal1 <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	lVal1 = lVal1 + baixa;

	int64_t resultado = lVal1 | lVal;
	//Empilha o resultado


	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	//finalmente empilha.
	printf("Parte alta empilhada: %d\n",alta);
	printf("Parte baixa empilhada: %d\n",baixa);
	push(alta);
	push(baixa);

	//atualiza pc
	inicializa_decodificador(dec);
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;

}

/**
 * Funcao desempilha dois valores inteiros, opera com o xor e empilha resultado.
 * @param void
 * @return void
 */
void ixor(){

	printf("Entrei no ixor\n");

	int32_t pop1 = pop_op();

	int32_t pop2 = pop_op();

	int32_t aux = pop1 ^ pop2;

	push(aux);

	//atualiza pc
	frameCorrente->pc++;

}

/**
 * Funcao desempilha dois valores long, opera com o xor e empilha resultado.
 * @param void
 * @return void
 */
void lxor(){
	int32_t baixa,alta;

	baixa = pop_op();
	alta = pop_op();

	//Converter os numeros 32 bits para 64 bits(long)

	//Atribui parte alta primeiro
	int64_t lVal = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	lVal <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	lVal = lVal + baixa;

	baixa = pop_op();
	alta = pop_op();

	//Converter os numeros 32 bits para 64 bits(long)

	//Atribui parte alta primeiro
	int64_t lVal1 = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	lVal1 <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	lVal1 = lVal1 + baixa;


	int64_t resultado = lVal1 ^ lVal;
	//Empilha o resultado


	//Converte para parte alta e baixa novamente :) kk para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	//finalmente empilha.
	printf("Parte alta empilhada: %d\n",alta);
	printf("Parte baixa empilhada: %d\n",baixa);
	push(alta);
	push(baixa);

	//atualiza pc
	inicializa_decodificador(dec);
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

	//proxima instruçao.
	for(int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
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
	int32_t val = (int32_t) pop_op();
	printf("Val inteiro: %d\n",val);

	//Realiza cast para float
	float valF = (float) val;
	printf("Val Float: %f\n",valF);

	//Utiliza um auxiliar para armazenar o valor float e empilha-lo.
	int32_t valPilha;
	memcpy(&valPilha, &valF, sizeof(int32_t));
	printf("Val empilhado %d\n",valPilha);
	push(valPilha);

	atualizaPc();
}

/**
 * Desempilha um inteiro converte para double e empilha o resultado.
 * @param void
 * @return void 
 */
void i2d(){
	printf("Entrei no i2d\n");
	//Desempilha valor da pilha
	int32_t retPilha = pop_op();

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
	push(alta);
	push(baixa);

	atualizaPc();
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
	int32_t retPilha = pop_op();
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
	push(alta);
	push(baixa);

	atualizaPc();
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
	printf("Entrei no d2f\n");
	int32_t alta,baixa;
	baixa = pop_op();
	alta = pop_op();

	//Atribui parte alta primeiro
	int64_t dVal = alta;
	//Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita.
	dVal <<= 32;
	//Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	//os 32 bits da parte baixa estão zerados.
	dVal = dVal + baixa;

	//Finalmente copio os bytes do int64_t para um double.
	//memcpy copia 64 bits de dVal para valorDouble1. -> Não perder a
	//Precisão. Alternativa UNION!!
	double v1;
	memcpy(&v1, &dVal, sizeof(double));

	//Realiza cast
	float fVal = (float) v1;
	printf("Valor float: %f\n",fVal);

	//Copia valor castado para um int32_T para ser empilhado.
	int32_t pilhaVal;
	memcpy(&pilhaVal,&fVal,sizeof(float));
	printf("Valor Empilhado: %d\n",pilhaVal);
	push(pilhaVal);

	atualizaPc();
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
	retPilha = pop_op();
	//Copia os bytes do int32 para uma var do tipo float para nao perder precisão.
	memcpy(&val2,&retPilha,sizeof(float));

	//Desempilha o primeiro valor(topo).
	retPilha = pop_op();
	//Copia os bytes do int32 para uma var do tipo float para nao perder precisão.
	memcpy(&val1,&retPilha,sizeof(float));

	//Compara os dois floats e seta o resultado.
	printf("val1: %f\n",val1);
	printf("val2: %f\n",val2);
	if(val1 == val2){
		printf("val1 == val2 empilhando 0\n");
		push((int32_t)0);
	}
	if(val1 > val2){
		printf("val1 > val2 empilhando 1\n");
		push((int32_t)1);
	}
	if(val1 < val2){
		printf("val1 < val2 empilhando -1\n");
		push((int32_t)-1);
	}

	atualizaPc();
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
	int32_t retPilha = pop_op();
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
	//obtém offset que vem da instruçao.
	int8_t offset = frameCorrente->code[frameCorrente->pc + 2];

	//TODO pc = pc + offset
	frameCorrente->pc += offset;
}
void jsr(){

}
void ret(){

}
void tableswitch(){
    uint32_t bytes_preench; 
    int32_t indice;
    int32_t default_v, low, high, npairs; 
    uint32_t pc_novo, pc_aux;
    int32_t qtd_offset, offset, posicao;
    uint32_t temp;

    // diz se o novo valor de pc ja esta definido ou nao 
    bool definido = false; 

    // pc auxiliar que iremos seguindo durante a execucao da instrucao 
    pc_aux = frameCorrente->pc; 

    // pega indice da operand stack
    indice = pop_op(); 
    
    /* passo 1 - le ateh o low. Se o indice eh menor que low - define logo o novo valor para PC */
    // pula bytes de preenchimento
    //bytes_preench = (pc_aux + 1) % 4;
    bytes_preench = (4 - ((pc_aux + 1) % 4) ) % 4;  
    pc_aux += bytes_preench;
    pc_aux++;
    
    // pega bytes do target default
    default_v = 0;
    for (int l = 0; l < 4; l++)
    {
        default_v = (default_v << 8) + frameCorrente->code[pc_aux];   
        pc_aux++;
    }       

    // pega bytes low
    low = 0;
    for (int l = 0; l < 4; l++)
    {
        low = (low << 8) + frameCorrente->code[pc_aux];   
        pc_aux++; 
    }       
    

    // se o indice eh menor que o low e ainda nao definimos novo pc
    if (indice < low && !definido)
    {
        definido = true;
        pc_novo = frameCorrente->pc + default_v; 
    }

    /* passo 2 - le ateh o high. Se o indice eh maior que o high - define o novo valor para PC
     * caso low ainda nao tenha sido definido */ 
    // pega bytes high 
    high = 0;
    for (int l = 0; l < 4; l++)
    {
        high = (high << 8) + frameCorrente->code[pc_aux];   
        pc_aux++; 
    }       

    // se o indice eh maior que o high e ainda nao definimos novo pc
    if (indice > high && !definido)
    {
        definido = true;
        pc_novo = frameCorrente->pc + default_v; 
    }

    /* passo 3 - calcula offset na posicao index - low. Coloca novo endereco de PC aqui, caso ainda não tenha sido 
     * definido */ 
    qtd_offset = 1 + high - low; 
    posicao = indice - low; 
    for (int32_t l = 0; l < qtd_offset; l++)
    {
        // se estamos na posicao correta
        if (l == posicao)
        {
            // extrai offset
            offset = 0;
            for (int i = 0; i < 4; i++)
            {
                offset = (offset << 8) + frameCorrente->code[pc_aux];   
                pc_aux++; 
            }       
            
            // calcula posicao 
            pc_novo = frameCorrente->pc + offset; 
            definido = true;
            
            // sai do loop 
            break;
        }

        // senao, passa pelo offset atual incrementando pc
        else
        {
            for (int i = 0; i < 4; i++)
            {
                pc_aux++; 
            }       
        }
    }

    // poe valor correto em frameCorrente
    frameCorrente->pc = pc_novo; 
}

void lookupswitch(){
    uint32_t pc_aux, pc_novo; 
    uint32_t bytes_preench;
    uint32_t offset;
    int32_t default_v, npairs; 
    int32_t match; 
    int32_t key;

    // diz se o novo valor de pc ja esta definido ou nao 
    bool definido = false; 

    // pc auxiliar que iremos seguindo durante a execucao da instrucao 
    pc_aux = frameCorrente->pc; 
   
    // pega key da operand stack
    key = pop_op(); 
    
    // pula bytes de preenchimento
    bytes_preench = (4 - ((pc_aux + 1) % 4) ) % 4;  
    //bytes_preench = (pc_aux + 1) % 4;
    pc_aux += bytes_preench;
    pc_aux++;
   
    // pega bytes default 
    default_v = 0;
    for (int l = 0; l < 4; l++)
    {
        default_v = (default_v << 8) + frameCorrente->code[pc_aux];   
        pc_aux++;
    }       
    
    // pega numeros de pares
    npairs = 0;
    for (int l = 0; l < 4; l++)
    {
        npairs = (npairs << 8) + frameCorrente->code[pc_aux];   
        pc_aux++;
    }       
    
    
    // itera pelo numero de pares
    for (int32_t l = 0; l < npairs; l++)
    {
        // pega match atual 
        match = 0;
        for (int l = 0; l < 4; l++)
        {
            match = (match << 8) + frameCorrente->code[pc_aux];   
            pc_aux++;
        }       
        
        // se a key corresponde ao match 
        if (key == match)
        {
            // pega offset
            offset = 0;
            for (int l = 0; l < 4; l++)
            {
                offset = (offset << 8) + frameCorrente->code[pc_aux];   
                pc_aux++;
            }       
            
            // poe valor correto em pc_novo
            pc_novo = frameCorrente->pc + offset; 

            // set booleano que achou o match
            definido = true;
        }

        // senao 
        else
        {
            // pula offset
            for(int i = 0; i < 4; i++)
            {
                pc_aux++;
            }
        }
     }

    // se ainda nao achamos o offset 
    if (!definido)
    {
        pc_novo = frameCorrente->pc + default_v;
    }

    // poe valor correto no offset
    frameCorrente->pc = pc_novo; 
}

/**
 * Retira um valor da pilha(inteiro) e empilha no frame chamador.
 * @param void
 * @return void 
 */
void ireturn(){
	int32_t retorno = pop_op();
	flagRet = 1;

	atualizaPc();
	printf("retornando! método acabou!\n");

}

/**
 * Retira dois valores da pilha(long) e empilha na função chamadora.
 * @param void
 * @return void 
 */
void lreturn(){
	int32_t alta,baixa;

	baixa = pop_op();
	alta = pop_op();

	flagRet = 2;

	retAlta = alta;
	retBaixa = baixa;

	atualizaPc();
	printf("retornando! método acabou!\n");

}

/**
 * Retira um valor float da pilha e empilha no frame chamador.
 * @param void
 * @return void 
 */
void freturn(){
	int32_t retorno = pop_op();
	flagRet = 1;

	atualizaPc();
	printf("retornando! método acabou!\n");

}

/**
 * Retira dois valores(double) da pilha e empilha no frame chamador.
 * @param void
 * @return void 
 */
void dreturn(){
	int32_t alta,baixa;

	baixa = pop_op();
	alta = pop_op();

	flagRet = 2;

	retAlta = alta;
	retBaixa = baixa;

	atualizaPc();
	printf("retornando! método acabou!\n");

}
void areturn(){

}

/**
 * Empilha o valor 0 no frame chamador.
 * @param void
 * @return void 
 */
void ins_return(){
	printf("entrei no ins_return!!\n");

	//setar variaveis globais de retorno para 0.
	retorno = 0;
	flagRet = 0;

	atualizaPc();
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

	atualizaPc();
}

void putstatic(){

}

/**
 * Função acessa um field do objeto e empilha na pilha de operandos do
 * frame corrente.
 * @param void
 * @return void 
 */
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

 	if((strcmp(tipo, "Ljava/util/Scanner;") == 0)){
 		atualizaPc();
		return;
 	}

 	objeto* obj = (objeto*) pop_op();

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
 	push(val);

	atualizaPc();
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
 	int32_t val = pop_op();
 	printf("valor desempilhado: %d\n",val);
 	objeto* obj = (objeto*)pop_op();

 	int i;
 	for(i = 0; obj->indiceCampos[i] != indiceNome; i++);
	obj->campos[i] = val;

	atualizaPc();
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
			resultado = pop_op();
			//resultado = frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1];
			string = frameCorrente->constant_pool[resultado].info.Utf8.bytes;
			printf("%s\n",string);
			}
			else if(flagAppend == 2){
				resultado = pop_op();
				resultado2 = pop_op();

				string = frameCorrente->constant_pool[resultado2].info.Utf8.bytes;
				printf("%s",string);

					if(strcmp(tipoGlobal, "F") == 0){
						float valDesemp;
						memcpy(&valDesemp,&resultado, sizeof(float));
						printf("%f\n",valDesemp);
					}

					if(strcmp(tipoGlobal, "I") == 0){
						printf("%d\n", resultado);
					}

				flagAppend = 0;
			}
		}
	}

	if((strcmp(nomeClasse, "java/util/Scanner") == 0) && (strcmp(nomeMetodo,"next") == 0)){
		int32_t aux;
		scanf("%d",&aux);
		push(aux);
		printf("Valor %d empilhado\n",frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1]);
	}

	atualizaPc();
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

		carregaMemClasse(nomeClasse);

		atualizaPc();
		return;
	}

	if(strcmp("java/lang/StringBuffer",nomeClasse) == 0){

		printf("Método nativo java - java/lang/object\n");

		atualizaPc();
		return;
	}

	if(strcmp("java/util/Scanner",nomeClasse) == 0){

		printf("Método nativo java - java/util/Scanner\n");

		atualizaPc();
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
		fields[i] = pop_op();

    dumpStack();
	//inicia método
	empilhaMetodo(metodoInvocado, classe);

	//Preenche fields no frame novo (invoke).
	for(int32_t i = 0; i <= numeroParametros; i++) {
			frameCorrente->fields[i] = fields[i];
	}

	//Executa método.
	executaFrameCorrente();

    dumpStack();
	atualizaPc();
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
			int32_t retPilha = pop_op();
			printf("cod retorno: %d\n",retPilha);
			exit(retPilha);
		}
	}

	if((strcmp(nomeClasse, "java/lang/Integer") == 0) && (strcmp(nomeMetodo,"parseInt") == 0)){
		
			int32_t retPilha = pop_op();
			pop_op();
			push(retPilha);
	}

	if((strcmp(nomeClasse, "java/lang/Math") == 0) && (strcmp(nomeMetodo,"sqrt") == 0)){
		if(strstr(descricaoMetodo, "(D)D") != NULL) {
			int32_t baixa = pop_op();
			int32_t alta = pop_op();

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

			push(alta);
			push(baixa);
		}
	}

	atualizaPc();
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
		naoEmpilhaFlag = 1;

		atualizaPc();
		return;
	}

	if(strcmp("java/lang/StringBuffer",nomeClasse) == 0){
		printf("Método nativo java - java/util/Scanner\n");
		naoEmpilhaFlag = 1;

		atualizaPc();
		return;
	}
	//Busca indice da classe no array de classeFiles
	aux = carregaMemClasse(nomeClasse);

	//Pega classFile pelo indice no array de classes
	classe = buscaClasseIndice(aux);

	//Cria um objeto a partir do classFile.
	objeto = criaObjeto(classe);

	if(objeto == NULL){
		printf("Objeto não foi corretamente alocado\n");
	}

	//empilha objeto na pilha de operandos (push)
	push((int32_t) objeto);
	printf("Valor %d empilhado\n",frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1]);
    dumpStack();

	atualizaPc();
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
