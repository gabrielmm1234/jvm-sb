/*
* Software Basico - 1/2016
* Professor: Marcelo Ladeira
* Arquivo que contém funções para carregar classes nas estruturas
* adequadas.
*/


int32_t carregaMemClasse(char* nomeClass){
	int aux;

	//Se ja esta carregado retorna posição no array de classes.
	for (int32_t i = 0; i < numeroClasses; i++) {
		if (strcmp(nomeClass, retornaNomeClasse(arrayClasses[i])) == 0)
			return i;
	}

	//Se não está carregado carrega e salva no array de classes.

	//uma classe nova vai entrar na lista de classes carregadas.
	numeroClasses++;
	aux = numeroClasses;

	arrayClasses = realloc(arrayClasses, (aux*sizeof(classFile *)));
	arrayClasses[aux-1] = leitorClasse(nomeClass);

}

// Acessa a constant pool no campo bytes a partir do index da classe e 
// retorna o nome da classe.
char* retornaNomeClasse(classFile* classe){
	uint16_t thisClass = classe->this_class;
	uint16_t nameIndex = (classe->constant_pool[thisClass]).info.Class.name_index;

	int i;
	char* retorno = malloc((classe->constant_pool[nameIndex]).info.Utf8.length + 1);

	// Percorre o bytes na constant pool e salva no retorno.
	for (i = 0; i < ( classe->constant_pool[nameIndex]).info.Utf8.length; i++) {
		retorno[i] = (char) (classe->constant_pool[nameIndex]).info.Utf8.bytes[i];
	}

	// \0 no final do nome da classe a ser retornada
	retorno[i] = '\0';

	return retorno;
}