#ifndef CARREGADOR_H
#define CARREGADOR_H

#include "leitor.h"

//Array de classes carrregadas.
extern classFile** arrayClasses;

//QUantidade de classes carregas.
extern int16_t numeroClasses;

// funcoes usadas no carregador 
int32_t carregaMemClasse(char* );
char* retornaNomeClasse(classFile* );
classFile* buscaClasseIndice(int );

#endif
