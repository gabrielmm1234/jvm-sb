#ifndef METODO_H
#define METODO_H

#include "carregador.h"

method_info* buscaMetodoMain();
void empilhaMetodo(method_info* ,classFile* );
void executaFrameCorrente();
objeto* criaObjeto(classFile* );
method_info* buscaMetodo(classFile* indiceClasse,classFile* searchClasse, uint16_t indice);
int32_t retornaNumeroParametros(classFile* classe, method_info* metodo);
classFile* retornaClasseNome(char*);
int32_t buscaCampo(char* className, char* name, char* desc);

#endif