/*
* Software Basico - 1/2016
* Arquivo que contém Função para decodificar uma instrução
* e apresentar os mnemônicos de cada instrução no exibidor.
*/

#ifndef DECODIFICADOR_C
#define DECODIFICADOR_C

#include "decodificador.h"

void inicializa_decodificador(decodificador dec[])
{
    // adiciona instrucoes na ordem de opcode 

    /* instrucoes constantes */
    // nop
    strcpy(dec[0].instrucao, "nop");
    dec[0].bytes = 0;

    // aconst_null
    strcpy(dec[1].instrucao, "aconst_null");
    dec[1].bytes = 0;
    
    // iconst_m1
    strcpy(dec[2].instrucao, "iconst_m1");
    dec[2].bytes = 0;

    // iconst_0
    strcpy(dec[3].instrucao, "iconst_0");
    dec[3].bytes = 0;

    // iconst_1
    strcpy(dec[4].instrucao, "iconst_1");
    dec[4].bytes = 0;

    // iconst_2
	strcpy(dec[5].instrucao, "iconst_2");
	dec[5].bytes = 0;

    // iconst_3
    strcpy(dec[6].instrucao, "iconst_3");
    dec[6].bytes = 0;

    // iconst_4
    strcpy(dec[7].instrucao, "iconst_4");
    dec[7].bytes = 0;

    // iconst_5
    strcpy(dec[8].instrucao, "iconst_5");
    dec[8].bytes = 0;

    // lconst_0
    strcpy(dec[9].instrucao, "lconst_0");
    dec[9].bytes = 0;

    // lconst_1
    strcpy(dec[10].instrucao, "lconst_1");
    dec[10].bytes = 0;

    // fconst_0
    strcpy(dec[11].instrucao, "fconst_0");
    dec[11].bytes = 0;

    // fconst_1
    strcpy(dec[12].instrucao, "fconst_1");
    dec[12].bytes = 0;

    // fconst_2
    strcpy(dec[13].instrucao, "fconst_2");
    dec[13].bytes = 0;

    // dconst_0
    strcpy(dec[14].instrucao, "dconst_0");
    dec[14].bytes = 0;

    // dconst_0
    strcpy(dec[15].instrucao, "dconst_1");
    dec[15].bytes = 0;

    // bipush
    strcpy(dec[16].instrucao, "bipush");
    dec[16].bytes = 1;

    strcpy(dec[17].instrucao, "sipush");
    dec[17].bytes = 2;

    // ldc
    strcpy(dec[18].instrucao, "ldc");
    dec[18].bytes = 1;
    
    strcpy(dec[19].instrucao, "ldc_w");
    dec[19].bytes = 2;

    strcpy(dec[20].instrucao, "ldc2_w");
    dec[20].bytes = 2;

    strcpy(dec[21].instrucao, "iload");
    dec[21].bytes = 1;

    strcpy(dec[22].instrucao, "lload");
    dec[22].bytes = 1;

    strcpy(dec[23].instrucao, "fload");
    dec[23].bytes = 1;

    strcpy(dec[24].instrucao, "dload");
    dec[24].bytes = 1;

    strcpy(dec[25].instrucao, "aload");
    dec[25].bytes = 1;

    strcpy(dec[26].instrucao, "iload_0");
    dec[26].bytes = 0;

    strcpy(dec[27].instrucao, "iload_1");
    dec[27].bytes = 0;

    strcpy(dec[28].instrucao, "iload_2");
    dec[28].bytes = 0;

    strcpy(dec[29].instrucao, "iload_3");
    dec[29].bytes = 0;

    strcpy(dec[30].instrucao, "lload_0");
    dec[30].bytes = 0;

    strcpy(dec[31].instrucao, "lload_1");
    dec[31].bytes = 0;

    strcpy(dec[32].instrucao, "lload_2");
    dec[32].bytes = 0;

    strcpy(dec[33].instrucao, "lload_3");
    dec[33].bytes = 0;

    strcpy(dec[34].instrucao, "fload_0");
    dec[34].bytes = 0;

    strcpy(dec[35].instrucao, "fload_1");
    dec[35].bytes = 0;

    strcpy(dec[36].instrucao, "fload_2");
    dec[36].bytes = 0;

    strcpy(dec[37].instrucao, "fload_3");
    dec[37].bytes = 0;

    strcpy(dec[38].instrucao, "dload_0");
    dec[38].bytes = 0;

    strcpy(dec[39].instrucao, "dload_1");
    dec[39].bytes = 0;

    strcpy(dec[40].instrucao, "dload_2");
    dec[40].bytes = 0;

    strcpy(dec[41].instrucao, "dload_3");
    dec[41].bytes = 0;

    /* loads */
    // aload_0
    strcpy(dec[42].instrucao, "aload_0");
    dec[42].bytes = 0;

    // aload_1
    strcpy(dec[43].instrucao, "aload_1");
    dec[43].bytes = 0;

    strcpy(dec[44].instrucao, "aload_2");
    dec[44].bytes = 0;

    strcpy(dec[45].instrucao, "aload_3");
    dec[45].bytes = 0;

    strcpy(dec[46].instrucao, "iaload");
    dec[46].bytes = 0;

    strcpy(dec[47].instrucao, "laload");
    dec[47].bytes = 0;

    strcpy(dec[48].instrucao, "faload");
    dec[48].bytes = 0;

    strcpy(dec[49].instrucao, "daload");
    dec[49].bytes = 0;

    strcpy(dec[50].instrucao, "aaload");
    dec[50].bytes = 0;

    strcpy(dec[51].instrucao, "baload");
    dec[51].bytes = 0;

    strcpy(dec[52].instrucao, "caload");
    dec[52].bytes = 0;

    strcpy(dec[53].instrucao, "saload");
    dec[53].bytes = 0;

    // STORES

    strcpy(dec[54].instrucao, "istore");
    dec[54].bytes = 1;

    strcpy(dec[55].instrucao, "lstore");
    dec[55].bytes = 1;

    strcpy(dec[56].instrucao, "fstore");
    dec[56].bytes = 1;

    strcpy(dec[57].instrucao, "dstore");
    dec[57].bytes = 1;

    strcpy(dec[58].instrucao, "astore");
    dec[58].bytes = 1;

    strcpy(dec[59].instrucao, "istore_0");
    dec[59].bytes = 0;

    strcpy(dec[60].instrucao, "istore_1");
    dec[60].bytes = 0;

    strcpy(dec[61].instrucao, "istore_2");
    dec[61].bytes = 0;

    strcpy(dec[62].instrucao, "istore_3");
    dec[62].bytes = 0;

    strcpy(dec[63].instrucao, "lstore_0");
    dec[63].bytes = 0;

    strcpy(dec[64].instrucao, "lstore_1");
    dec[64].bytes = 0;

    strcpy(dec[65].instrucao, "lstore_2");
    dec[65].bytes = 0;

    strcpy(dec[66].instrucao, "lstore_3");
    dec[66].bytes = 0;

    // fstore
    strcpy(dec[67].instrucao, "fstore_0");
    dec[67].bytes = 0;

    strcpy(dec[68].instrucao, "fstore_1");
    dec[68].bytes = 0;

    strcpy(dec[69].instrucao, "fstore_2");
    dec[69].bytes = 0;

    strcpy(dec[70].instrucao, "fstore_3");
    dec[70].bytes = 0;

    // dstore
    strcpy(dec[71].instrucao, "dstore_0");
    dec[71].bytes = 0;

    strcpy(dec[72].instrucao, "dstore_1");
    dec[72].bytes = 0;

    strcpy(dec[73].instrucao, "dstore_2");
    dec[73].bytes = 0;

    strcpy(dec[74].instrucao, "dstore_3");
    dec[74].bytes = 0;

    // astore
    strcpy(dec[75].instrucao, "astore_0");
    dec[75].bytes = 0;

    strcpy(dec[76].instrucao, "astore_1");
    dec[76].bytes = 0;

    strcpy(dec[77].instrucao, "astore_2");
    dec[77].bytes = 0;

    strcpy(dec[78].instrucao, "astore_3");
    dec[78].bytes = 0;

    strcpy(dec[79].instrucao, "iastore");
    dec[79].bytes = 0;

    strcpy(dec[80].instrucao, "lastore");
    dec[80].bytes = 0;

    strcpy(dec[81].instrucao, "fastore");
    dec[81].bytes = 0;

    strcpy(dec[82].instrucao, "dastore");
    dec[82].bytes = 0;

    strcpy(dec[83].instrucao, "aastore");
    dec[83].bytes = 0;

    strcpy(dec[84].instrucao, "bastore");
    dec[84].bytes = 0;

    strcpy(dec[85].instrucao, "castore");
    dec[85].bytes = 0;

    strcpy(dec[86].instrucao, "sastore");
	dec[86].bytes = 0;

	// STACK

	strcpy(dec[87].instrucao, "pop");
	dec[87].bytes = 0;

	strcpy(dec[88].instrucao, "pop2");
	dec[88].bytes = 0;

	strcpy(dec[89].instrucao, "dup");
	dec[89].bytes = 0;

	strcpy(dec[90].instrucao, "dup_x1");
	dec[90].bytes = 0;

	strcpy(dec[91].instrucao, "dup_x2");
	dec[91].bytes = 0;

	strcpy(dec[92].instrucao, "dup2");
	dec[92].bytes = 0;

	strcpy(dec[93].instrucao, "dup2_x1");
	dec[93].bytes = 0;

	strcpy(dec[94].instrucao, "dup2_x2");
	dec[94].bytes = 0;

	strcpy(dec[95].instrucao, "swap");
	dec[95].bytes = 0;

	// MATH

	strcpy(dec[96].instrucao, "iadd");
	dec[96].bytes = 0;

	strcpy(dec[97].instrucao, "ladd");
	dec[97].bytes = 0;

	strcpy(dec[98].instrucao, "fadd");
	dec[98].bytes = 0;

	strcpy(dec[99].instrucao, "dadd");
	dec[99].bytes = 0;

	strcpy(dec[100].instrucao, "isub");
	dec[100].bytes = 0;

	strcpy(dec[101].instrucao, "lsub");
	dec[101].bytes = 0;

	strcpy(dec[102].instrucao, "fsub");
	dec[102].bytes = 0;

	strcpy(dec[103].instrucao, "dsub");
	dec[103].bytes = 0;

	strcpy(dec[104].instrucao, "imul");
	dec[104].bytes = 0;

	strcpy(dec[105].instrucao, "lmul");
	dec[105].bytes = 0;

	strcpy(dec[106].instrucao, "fmul");
	dec[106].bytes = 0;

	strcpy(dec[107].instrucao, "dmul");
	dec[107].bytes = 0;

	strcpy(dec[108].instrucao, "idiv");
	dec[108].bytes = 0;

	strcpy(dec[109].instrucao, "ldiv");
	dec[109].bytes = 0;

	strcpy(dec[110].instrucao, "fdiv");
	dec[110].bytes = 0;

	strcpy(dec[111].instrucao, "ddiv");
	dec[111].bytes = 0;

	strcpy(dec[112].instrucao, "irem");
	dec[112].bytes = 0;

	strcpy(dec[113].instrucao, "lrem");
	dec[113].bytes = 0;

	strcpy(dec[114].instrucao, "frem");
	dec[114].bytes = 0;

	strcpy(dec[115].instrucao, "drem");
	dec[115].bytes = 0;

	strcpy(dec[116].instrucao, "ineg");
	dec[116].bytes = 0;

	strcpy(dec[117].instrucao, "lneg");
	dec[117].bytes = 0;

	strcpy(dec[118].instrucao, "fneg");
	dec[118].bytes = 0;

	strcpy(dec[119].instrucao, "dneg");
	dec[119].bytes = 0;

	strcpy(dec[120].instrucao, "ishl");
	dec[120].bytes = 0;

	strcpy(dec[121].instrucao, "lshl");
	dec[121].bytes = 0;

	strcpy(dec[122].instrucao, "ishr");
	dec[122].bytes = 0;

	strcpy(dec[123].instrucao, "lshr");
	dec[123].bytes = 0;

	strcpy(dec[124].instrucao, "iushr");
	dec[124].bytes = 0;

	strcpy(dec[125].instrucao, "lushr");
	dec[125].bytes = 0;

	strcpy(dec[126].instrucao, "iand");
	dec[126].bytes = 0;

	strcpy(dec[127].instrucao, "land");
	dec[127].bytes = 0;

	strcpy(dec[128].instrucao, "ior");
	dec[128].bytes = 0;

	strcpy(dec[129].instrucao, "lor");
	dec[129].bytes = 0;

	strcpy(dec[130].instrucao, "ixor");
	dec[130].bytes = 0;

	strcpy(dec[131].instrucao, "lxor");
	dec[131].bytes = 0;

	strcpy(dec[132].instrucao, "iinc");
	dec[132].bytes = 2;

	// CONVERSIONS

	strcpy(dec[133].instrucao, "i2l");
	dec[133].bytes = 0;

    strcpy(dec[134].instrucao, "i2f");
    dec[134].bytes = 0;

    strcpy(dec[135].instrucao, "i2d");
    dec[135].bytes = 0;

    strcpy(dec[136].instrucao, "l2i");
    dec[136].bytes = 0;

    strcpy(dec[137].instrucao, "l2f");
    dec[137].bytes = 0;

    strcpy(dec[138].instrucao, "l2d");
    dec[138].bytes = 0;

    strcpy(dec[139].instrucao, "f2i");
    dec[139].bytes = 0;

    strcpy(dec[140].instrucao, "f2l");
    dec[140].bytes = 0;

    strcpy(dec[141].instrucao, "f2d");
    dec[141].bytes = 0;

    strcpy(dec[142].instrucao, "d2i");
    dec[142].bytes = 0;

    strcpy(dec[143].instrucao, "d2l");
    dec[143].bytes = 0;

    strcpy(dec[144].instrucao, "d2f");
    dec[144].bytes = 0;

    strcpy(dec[145].instrucao, "i2b");
    dec[145].bytes = 0;

    strcpy(dec[146].instrucao, "i2c");
    dec[146].bytes = 0;

    strcpy(dec[147].instrucao, "i2s");
    dec[147].bytes = 0;

    // COMPARISONS

    strcpy(dec[148].instrucao, "lcmp");
    dec[148].bytes = 0;

    strcpy(dec[149].instrucao, "fcmpl");
    dec[149].bytes = 0;

    strcpy(dec[150].instrucao, "fcmpg");
    dec[150].bytes = 0;

    strcpy(dec[151].instrucao, "dcmpl");
    dec[151].bytes = 0;

    strcpy(dec[152].instrucao, "dcmpg");
    dec[152].bytes = 0;

    strcpy(dec[153].instrucao, "ifeq");
    dec[153].bytes = 2;

    strcpy(dec[154].instrucao, "ifne");
    dec[154].bytes = 2;

    strcpy(dec[155].instrucao, "iflt");
    dec[155].bytes = 2;

    strcpy(dec[156].instrucao, "ifge");
    dec[156].bytes = 2;

    strcpy(dec[157].instrucao, "ifgt");
    dec[157].bytes = 2;

    strcpy(dec[158].instrucao, "ifle");
    dec[158].bytes = 2;

    strcpy(dec[159].instrucao, "if_icmpeq");
    dec[159].bytes = 2;

    strcpy(dec[160].instrucao, "if_icmpne");
    dec[160].bytes = 2;

    strcpy(dec[161].instrucao, "if_icmplt");
    dec[161].bytes = 0;

    strcpy(dec[162].instrucao, "if_icmpge");
    dec[162].bytes = 0;

    strcpy(dec[163].instrucao, "if_icmpgt");
    dec[163].bytes = 0;

    strcpy(dec[164].instrucao, "if_icmple");
    dec[164].bytes = 0;

    strcpy(dec[165].instrucao, "if_acmpeq");
    dec[165].bytes = 2;

    strcpy(dec[166].instrucao, "if_acmpne");
    dec[166].bytes = 2;

    // CONTROL

    strcpy(dec[167].instrucao, "goto");
    dec[167].bytes = 2;

    strcpy(dec[168].instrucao, "jsr");
    dec[168].bytes = 2;

    strcpy(dec[169].instrucao, "ret");
    dec[169].bytes = 1;

    strcpy(dec[170].instrucao, "tableswitch"); // TODO: VERIFICAR A QUANTIDADE DE BYTES
    dec[170].bytes = 14;

    strcpy(dec[171].instrucao, "lookupswitch"); // TODO: VERIFICAR A QUANTIDADE DE BYTES
    dec[171].bytes = 10;

    strcpy(dec[172].instrucao, "ireturn");
    dec[172].bytes = 0;

    strcpy(dec[173].instrucao, "lreturn");
    dec[173].bytes = 0;

    strcpy(dec[174].instrucao, "freturn");
    dec[174].bytes = 0;

    strcpy(dec[175].instrucao, "dreturn");
    dec[176].bytes = 0;

    strcpy(dec[176].instrucao, "areturn");
    dec[176].bytes = 0;

    // return 
    strcpy(dec[177].instrucao, "return");
    dec[177].bytes = 0;

    // REFERENCES

    //getstatic
    strcpy(dec[178].instrucao, "getstatic");
    dec[178].bytes = 2;

    strcpy(dec[179].instrucao, "putstatic");
    dec[179].bytes = 2;

    strcpy(dec[180].instrucao, "getfield");
    dec[180].bytes = 2;

    strcpy(dec[181].instrucao, "putfield");
    dec[181].bytes = 2;
    
    // invokevirtual 
    strcpy(dec[182].instrucao, "invokevirtual");
    dec[182].bytes = 2;

    // invokespecial 
    strcpy(dec[183].instrucao, "invokespecial");
    dec[183].bytes = 2;

    strcpy(dec[184].instrucao, "invokestatic");
    dec[184].bytes = 2;

    // invokeinterface 
    strcpy(dec[185].instrucao, "invokeinterface");
    dec[185].bytes = 4;

    strcpy(dec[186].instrucao, "invokedynamic");
    dec[186].bytes = 4;

    // new 
    strcpy(dec[187].instrucao, "new");
    dec[187].bytes = 2;

    strcpy(dec[188].instrucao, "newarray");
    dec[188].bytes = 1;

    strcpy(dec[189].instrucao, "anewarray");
    dec[189].bytes = 2;

    strcpy(dec[190].instrucao, "arraylength");
    dec[190].bytes = 0;

    strcpy(dec[191].instrucao, "athrow");
    dec[191].bytes = 0;

    strcpy(dec[192].instrucao, "checkcast");
    dec[192].bytes = 2;

    strcpy(dec[193].instrucao, "instanceof");
    dec[193].bytes = 2;

    strcpy(dec[194].instrucao, "monitorenter");
    dec[194].bytes = 0;

    strcpy(dec[195].instrucao, "monitorexit");
    dec[195].bytes = 0;

    strcpy(dec[196].instrucao, "wide"); // TODO: VERIFICAR A QUANTIDADE DE BYTES
    dec[196].bytes = 3;

    strcpy(dec[197].instrucao, "multianewarray");
    dec[197].bytes = 3;

    strcpy(dec[198].instrucao, "ifnull");
    dec[198].bytes = 2;

    strcpy(dec[199].instrucao, "ifnonnull");
    dec[199].bytes = 2;

    strcpy(dec[200].instrucao, "goto_w");
    dec[200].bytes = 4;

    strcpy(dec[201].instrucao, "jsr_w");
    dec[201].bytes = 4;

    //codigos reservados
    strcpy(dec[202].instrucao, "breakpoint");
    dec[202].bytes = 0;

    strcpy(dec[254].instrucao, "impdep1");
    dec[254].bytes = 0;

    strcpy(dec[255].instrucao, "impdep2");
    dec[255].bytes = 0;
}
#endif  
