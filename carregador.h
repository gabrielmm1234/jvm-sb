
//Array de classes carrregadas.
classFile** arrayClasses = NULL;

//QUantidade de classes carregas.
int16_t numeroClasses = 0;

int32_t carregaMemClasse(char* );
char* retornaNomeClasse(classFile* );
classFile* buscaClasseIndice(int );

#include "carregador.c"