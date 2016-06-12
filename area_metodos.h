#ifndef AREA_METODOS_H
#define AREA_METODOS_H

#include "leitor.h"

// maximo numero de variaveis um objeto pode ter
#define MAX_VAR 256


// um campo que o objeto pode armazenar
union var
{
    int inteiro;
    char caractere; 
    float pflutuante; 
}; 

/*
 * contem as informacoes para as variaveis de instancias do objeto 
 *
 */
typedef struct info_obj
{
    // tags
    int tag[MAX_VAR]; 

    // array de unions contendo as variaveis de instancia do objeto 
    union var variaveis[MAX_VAR];
}
info_obj;

/*
 * o heap contem um ponteiro para a classfile e um vetor de referencias aos objetos
 * daquela classe
 */
typedef struct heap 
{
    // ponteiro para as informacoes relativas a classe la na area de metodos
    classFile* info_classes;  
    
    // array de ponteiro para as informacoes dos objetos 
    info_obj** objetos; 
    // numero de objetos, assim que o heap for criado deve ser colocado como zero
    int num_obj; 
    
    // array de ponteiros para os arrays - que tambem sao armazenados no heap. 
}
heap; 

/** 
 * struct para a area de metodos
 * 
 */
typedef struct area_metodos
{
    // array de classfiles, contem as classes ja carregadas
    classFile** array_classes; 

    // numero de classes carregadas em memoria 
    int num_classes;  

    // cada classe tem uma referencia ao heap, precisamos entao de uma array de referencias ao heap 
    heap** heap;

}
area_metodos; 

#endif 
