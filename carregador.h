#ifndef CARREGADOR_H
#define CARREGADOR_H

#include "leitor.h"
#include "area_metodos.h"

//Array de classes carrregadas.
extern classFile** arrayClasses;
extern area_metodos area_met; 

//QUantidade de classes carregas.

// funcoes usadas no carregador 
int32_t carregaMemClasse(char* );
char* retornaNomeClasse(classFile* );
classFile* buscaClasseIndice(int );
char * retornaNome(classFile* cf, uint16_t indiceNome);

#endif
