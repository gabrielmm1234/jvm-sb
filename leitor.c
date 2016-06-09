/*
* Software Basico - 1/2016
* Arquivo que contém Funções de leitura do arquivo .class e montagem das estruturas.
* Para salvar a saida em um arquivo execute da seguinte forma:
* ./jvm .class 1 > log.txt
*/

#ifndef LEITOR_EXIBIDOR_C
#define LEITOR_EXIBIDOR_C
#include "leitor.h"
#include "exibidor.h"

//Função que recebe o nome do arquivo  e retorna uma estrutura preenchida
//Com as informações necessárias. Seguindo o JClassLib.
classFile* leitorClasse(char * nomeClass){

    FILE* file;
    file = fopen(nomeClass, "rb");

    if(file == NULL){
        printf("Arquivo não encontrado! Erro ao abrir o arquivo!\n");
        return 0;
    }

    //Aloca memória para a estrutura do .class
    classFile* cf = (classFile*) malloc(sizeof(classFile));

    //Le informações gerais.
    generalInfo(cf,file);

    //Le a constant pool
    constantPool(cf,file);

    //le informações gerais após a constant pool
    secondGeneralInfo(cf,file);

    //liberando ponteiros.
    free(file);

    return cf;
}

void generalInfo(classFile* cf, FILE* file){
	cf->magic = le4Bytes(file);
	if(cf->magic != 0xCAFEBABE){
		printf("Arquivo .class inválido!!\n\n");
		exit(0);
	}
	cf->minor_version = le2Bytes(file);
	cf->major_version = le2Bytes(file);
	cf->constant_pool_count = le2Bytes(file);
}

void constantPool(classFile* cf, FILE* file){
	cf->constant_pool = (cp_info*) malloc((cf->constant_pool_count-1)*sizeof(cp_info));
	cp_info* cp;

    // loop q simplesmente faz a leitura da constant pool 
	int i = 0;
	for(cp = cf->constant_pool; i < (cf->constant_pool_count-1); cp++){
		cp->tag = le1Byte(file);
		switch(cp->tag){
			case CONSTANT_Class:
				cp->info.Class.name_index = le2Bytes(file);
				break;
			case CONSTANT_Fieldref:
				cp->info.Fieldref.class_index = le2Bytes(file);
				cp->info.Fieldref.name_and_type_index = le2Bytes(file);
				break;
			case CONSTANT_NameAndType:
				cp->info.NameAndType.name_index = le2Bytes(file);
				cp->info.NameAndType.descriptor_index = le2Bytes(file);
				break;
			case CONSTANT_Utf8:
				cp->info.Utf8.length = le2Bytes(file);
				cp->info.Utf8.bytes = (uint8_t*) malloc ((cp->info.Utf8.length)*sizeof(uint8_t));
				fread(cp->info.Utf8.bytes,1,cp->info.Utf8.length,file);
				break;
			case CONSTANT_Methodref:
				cp->info.Methodref.class_index = le2Bytes(file);
				cp->info.Methodref.name_and_type_index = le2Bytes(file);
				break;
			case CONSTANT_InterfaceMethodref:
				cp->info.InterfaceMethodref.class_index = le2Bytes(file);
				cp->info.InterfaceMethodref.name_and_type_index = le2Bytes(file);
				break;
			case CONSTANT_String:
				cp->info.String.string_index = le2Bytes(file);
				break;
			case CONSTANT_Integer:
				cp->info.Integer.bytes = le4Bytes(file);
			case CONSTANT_Float:
				cp->info.Float.bytes = le4Bytes(file);
				break;
			case CONSTANT_Double:
				cp->info.Double.high_bytes = le4Bytes(file);
				cp->info.Double.low_bytes = le4Bytes(file);
				cp++;
				i++;
				break;
			default:
				break;
		}
		i++;
	}
}

void interfaceInfo(classFile* cf, FILE* file, uint16_t interfaces_count){
	if(interfaces_count == 0)
		return;
	else{

        // aloca espaco apropriado
        cf->interfaces = (uint16_t *) malloc((interfaces_count) * sizeof(uint16_t));

        // le interface, pondo no array de interfaces
        for (int i = 0; i < interfaces_count; i++)
        {
            cf->interfaces[i] = le2Bytes(file);
        }
	}
}

void fieldInfo(classFile* cf, FILE* file, uint16_t fields_count){
	if(fields_count == 0)
		return;
	else{
       
        // aloca espaco apropriado
        cf->fields = (field_info*) malloc(fields_count * sizeof(field_info)); 
        
        // le field information, pondo no array de field
        for (int i = 0; i < fields_count; i++)
        {
            // pega bits de acesso, indice do nome e indice do descritor
            cf->fields[i].access_flags = le2Bytes(file);
            cf->fields[i].name_index = le2Bytes(file);
            cf->fields[i].descriptor_index = le2Bytes(file);

            cf->fields[i].attributes_count = le2Bytes(file);

            // aloca espaco para o array de atributos
            cf->fields[i].attributes = (attribute_info*) malloc(cf->fields[i].attributes_count * sizeof(attribute_info));
            
            // vai lendo atributos 
            for (int j = 0; j < cf->fields[i].attributes_count; j++)
            {
                 
                // pega indice do nome do atributo e comprimento do atributo
                cf->fields[i].attributes->attribute_name_index = le2Bytes(file);
                cf->fields[i].attributes->attribute_length = le4Bytes(file);

                // espaco para informacao do atributo
                cf->fields[i].attributes->info = (uint8_t*) malloc(cf->fields[i].attributes->attribute_length * sizeof(uint8_t));
                
                // le informacao do atributo
                fread(cf->fields[i].attributes->info, 1, cf->fields[i].attributes->attribute_length, file);

                // le bytecode do atributo
                for (int k = 0; k < cf->fields[i].attributes->attribute_length; k++)
                {
                    fread(&(cf->fields[i].attributes->info[k]), 1, 1, file);   
                }
            }
        }
	}
}

//Função para ler estrutura e informações dos métodos.
void methodInfo(classFile* cf, FILE* file, uint16_t methods_count){
	if(methods_count == 0)
		return;
	else{
		cf->methods = (method_info*) malloc(methods_count*sizeof(method_info));
		method_info* cp = cf->methods;
		for(int i = 0; i < methods_count; cp++){
			cp->access_flags = le2Bytes(file);
			cp->name_index = le2Bytes(file);
			cp->descriptor_index = le2Bytes(file);
			cp->attributes_count = le2Bytes(file);
			cp->attributes = (code_attribute*) malloc(cp->attributes_count*sizeof(code_attribute));

			for(int j = 0; j < cp->attributes_count; j++){
				cp->attributes[j].attribute_name_index = le2Bytes(file);
				cp->attributes[j].attribute_length = le4Bytes(file);

                // posicao do ponteiro
                int posicao_inicial = ftell(file);

                // leitura do bytecode relacionado a informacoes gerais
                cp->attributes[j].max_stack = le2Bytes(file);
                cp->attributes[j].max_locals = le2Bytes(file);
                cp->attributes[j].code_length = le4Bytes(file);
                
                // obtem decodificador de instrucoes 
                decodificador dec[NUM_INSTRUCAO];
                inicializa_decodificador(dec); 

                // leitura do bytecode relacionado a instrucoes do metodo 
                // aloca espaco conveniente
                cp->attributes[j].code = (uint8_t*) malloc(cp->attributes[j].code_length * \
                        sizeof(uint8_t));

                // poe valor no espacos corretos
                for(int k = 0; k < cp->attributes[j].code_length; k++)
                {    
                    // le opcode da instrucao atual
                    fread(&(cp->attributes[j].code[k]), 1, 1, file);
                    
                    int indice = cp->attributes[j].code[k];

                    // obtem quantos operandos a instrucao tem
                    int num_bytes = dec[indice].bytes;
                    for (int l = 0; l < num_bytes; l++)
                    {
                        // atualiza valor de k 
                        k++;

                        // pega operando 
                        fread(&(cp->attributes[j].code[k]), 1, 1, file);
                    }
                }

                // pega tamanho da tabela de excecoes
                cp->attributes[j].exception_table_length = le2Bytes(file);

                // aloca espaco apropriado
                cp->attributes[j].exception_table = (exception_table*) malloc( \
                        cp->attributes[j].exception_table_length * sizeof(exception_table));

                // le dados da tabela de excecoes
                for (int k = 0; k < cp->attributes[j].exception_table_length; k++)
                {
                    cp->attributes[j].exception_table[k].start_pc = le2Bytes(file);
                    cp->attributes[j].exception_table[k].end_pc = le2Bytes(file);
                    cp->attributes[j].exception_table[k].catch_type = le2Bytes(file);
                }

                // pega numero de atributos
                cp->attributes[j].attributes_count = le2Bytes(file);
                
                // aloca espaco apropriado
                cp->attributes[j].attributes = (attribute_info*) malloc ( \
                        cp->attributes[j].attributes_count * sizeof(attribute_info));

                // le atributos opcionais de debug
                // nao precisa preocupar muito com isso 
                while (ftell(file) - posicao_inicial < cp->attributes[j].attribute_length) 
                {
                    le1Byte(file);
                }
                
			}
			i++;
		}
	}
}

void attributeInfo(classFile* cf, FILE* file, uint16_t attributes_count){
	if(attributes_count == 0)
		return;
	else{
		cf->attributes = (attribute_info*) malloc(attributes_count*sizeof(attribute_info));
		attribute_info* cp = cf->attributes;

		for(int i = 0; i < attributes_count; cp++){

			cp->attribute_name_index = le2Bytes(file);
			cp->attribute_length = le4Bytes(file);
			cp->info = (uint8_t*) malloc((cp->attribute_length)*sizeof(uint8_t));
			for(int j = 0; j < cp->attribute_length; j++){
				fread(&cp->info[j],1,1,file);
			}
			i++;
		}
	}
}

void secondGeneralInfo(classFile* cf, FILE* file){
	cf->access_flags = le2Bytes(file);
	cf->this_class = le2Bytes(file);
	cf->super_class = le2Bytes(file);

	cf->interfaces_count = le2Bytes(file);
	interfaceInfo(cf,file,cf->interfaces_count);

	cf->fields_count = le2Bytes(file);
	fieldInfo(cf,file,cf->fields_count);

	cf->methods_count = le2Bytes(file);
	methodInfo(cf,file,cf->methods_count);

	cf->attributes_count = le2Bytes(file);
	attributeInfo(cf,file,cf->attributes_count);
}

// funcoes auxiliares para leitura.
static inline uint8_t le1Byte(FILE* fp){
	uint8_t retorno = getc(fp);
	return retorno;
}

static inline uint16_t le2Bytes(FILE* fp){
	uint16_t retorno = getc(fp); 
	retorno = (retorno << 8) | (getc(fp));
	return retorno;
}

static inline uint32_t le4Bytes(FILE* fp){
	uint32_t retorno = getc(fp);
	retorno = (retorno << 8) | (getc(fp));
	retorno = (retorno << 8) | (getc(fp));
	retorno = (retorno << 8) | (getc(fp));
	return retorno;
}
#endif
