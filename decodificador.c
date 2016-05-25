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

    // iconst_3
    strcpy(dec[6].instrucao, "iconst_6");
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
    strcpy(dec[15].instrucao, "bipush");
    dec[16].bytes = 1;

    // ldc
    strcpy(dec[18].instrucao, "ldc");
    dec[18].bytes = 1;
    
    /* loads */
    // aload_0
    strcpy(dec[42].instrucao, "aload_0");
    dec[42].bytes = 0;

    // aload_1
    strcpy(dec[43].instrucao, "aload_1");
    dec[43].bytes = 0;

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
    dec[187].bytes = 0;

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
