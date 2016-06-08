/*
* Software Basico - 1/2016
* Professor: Marcelo Ladeira
* Arquivo que contém funções responsáveis por manipular os métodos que 
* serão usados nos frames.
*/


//Função para retornar o método main do primeiro .class carregado.
method_info* buscaMetodoMain(){
	classFile * main;
	uint16_t nome_tam,desc_tam;
	uint8_t* nome;
	uint8_t* desc;
	//Busca a classe que contém o método main. Foi a primeira classe a ser carregada.
	main = buscaClasseIndice(0);

	//Percorre o method_info em busca do method main.
	for(int i = 0; i < main->methods_count; i++) {
		nome = main->constant_pool[(main->methods[i].name_index -1 )].info.Utf8.bytes;

		nome_tam = main->constant_pool[(main->methods[i].name_index - 1)].info.Utf8.length;

		desc = main->constant_pool[(main->methods[i].descriptor_index - 1)].info.Utf8.bytes;

		desc_tam = main->constant_pool[(main->methods[i].descriptor_index - 1)].info.Utf8.length;

		//Se encontrou método main retorna uma referencia.
		if((strncmp("main",(char *)nome, nome_tam) == 0) &&(strncmp("([Ljava/lang/String;)V",(char *)desc, desc_tam) == 0)) {
			return &(main->methods[i]);
		}
	}

	//Se não encontra não possui método main na classe carregada.
	return NULL;
}