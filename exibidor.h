#ifndef PRINT_H
#define PRINT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h> 
#include "leitor.h"

void imprimePrompt(classFile* cf);

/*
 * a funcao recebe uma referencia para a constant pool e a posicao em que estamos na constant_pool 
 * a funcao imprime a UTF8 associada a essa posicao da tabela
 */
void imprime_string_pool(cp_info* cp, int pos_pool);
void imprime_methods(classFile* cf);
void imprime_code(classFile* cf, code_attribute* cd_atrb);
void imprime_exc(classFile* cf, exceptions_attribute* exc_atrb);
#endif
