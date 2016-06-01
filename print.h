#ifndef PRINT_H
#define PRINT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h> 

void imprimePrompt(classFile* cf);
void imprime_string_pool(cp_info* cp, int pos_pool);

#include "print.c"
#endif
