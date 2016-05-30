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
    dec[17].bytes = 1;

    // ldc
    strcpy(dec[18].instrucao, "ldc");
    dec[18].bytes = 1;
    
    strcpy(dec[19].instrucao, "ldc_w");
    dec[19].bytes = 1;

    strcpy(dec[20].instrucao, "ldc2_w");
    dec[20].bytes = 0;

    strcpy(dec[21].instrucao, "iload");
    dec[21].bytes = 0;

    strcpy(dec[22].instrucao, "lload");
    dec[22].bytes = 0;

    strcpy(dec[23].instrucao, "fload");
    dec[23].bytes = 0;

    strcpy(dec[24].instrucao, "dload");
    dec[24].bytes = 0;

    strcpy(dec[25].instrucao, "aload");
    dec[25].bytes = 0;

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

    strcpy(dec[54].instrucao, "istore");
    dec[54].bytes = 0;

    strcpy(dec[55].instrucao, "lstore");
    dec[55].bytes = 0;

    strcpy(dec[56].instrucao, "fstore");
    dec[56].bytes = 0;

    strcpy(dec[57].instrucao, "dstore");
    dec[57].bytes = 0;

    strcpy(dec[58].instrucao, "astore");
    dec[58].bytes = 0;

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

    strcpy(dec[67].instrucao, "fstore_0");
    dec[67].bytes = 0;

    strcpy(dec[68].instrucao, "fstore_1");
    dec[68].bytes = 0;

    // a_store1 
    strcpy(dec[76].instrucao, "a_store1");
    dec[76].bytes = 0;

    // dup 
    strcpy(dec[89].instrucao, "dup");
    dec[89].bytes = 0;

    // return 
    strcpy(dec[177].instrucao, "return");
    dec[177].bytes = 0;

    //getstatic
    strcpy(dec[178].instrucao, "getstatic");
    dec[178].bytes = 2;
    
    // invokevirtual 
    strcpy(dec[182].instrucao, "invokevirtual");
    dec[182].bytes = 2;

    // invokespecial 
    strcpy(dec[183].instrucao, "invokespecial");
    dec[183].bytes = 2;

    // invokeinterface 
    strcpy(dec[185].instrucao, "invokeinterface");
    dec[185].bytes = 4;

    // new 
    strcpy(dec[187].instrucao, "new");
    dec[187].bytes = 2;

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
