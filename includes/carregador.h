#ifndef CARREGADOR_H
#define CARREGADOR_H

#include "leitor.h"
#include "area_metodos.h"

//Area de metodos.
extern area_metodos area_met; 

// funcoes usadas no carregador 
int32_t carregaMemClasse(char* );
char* retornaNomeClasse(classFile* );
classFile* buscaClasseIndice(int );
char * retornaNome(classFile* cf, uint16_t indiceNome);
int32_t carregaObjectClasse();

#endif
