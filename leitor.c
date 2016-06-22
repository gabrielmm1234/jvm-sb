/**
 *@file
 *@section DESCRIPTION
 *Universidade de Brasilia
 *
 *Gabriel Mesquita de Araujo 13/0009121\n
 *Gabriel Ferreira Silva 14/0140131\n
 *Renato 13/0009121\n
 *Leandro 13/0009121\n
 *Carlos 13/0009121\n\n
 *
 * Software Basico - 1/2016\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Arquivo que contém Funções de leitura do arquivo .class e montagem das estruturas.
 * Para salvar a saida em um arquivo execute da seguinte forma:
 * ./jvm.exe .class 1 > log.txt* 
 */



#include "./includes/leitor.h"
#include "./includes/exibidor.h"


/**
 * Função que recebe o nome do arquivo .class a ser lido. Seguindo o jclasslib.
 * 
 * @param nome do arquivo ".class" a ser lido.
 * @return estrutura que representa um classFile.
 */
classFile* leitorClasse(char * nomeClass){

    FILE* file;
    file = fopen(nomeClass, "rb");

    if(file == NULL){
        printf("Arquivo não encontrado! Erro ao abrir o arquivo!\n");
        return 0;
    }

    //Aloca memória para a estrutura do .class
    classFile* cf = NULL;

    cf = (classFile*) calloc(sizeof(classFile),1);

    if(cf == NULL)
    	printf("taNULL");

    //Le informações gerais.
    generalInfo(cf,file);

    //Le a constant pool
    constantPool(cf,file);

    //le informações gerais após a constant pool
    secondGeneralInfo(cf,file);

    //liberando ponteiros.
    fclose(file);

    //Retorna referencia ao classFile preenchido.
    return cf;
}

/**
 * Função que le as informações gerais de um arquivo .class
 * 
 * @param referência ao classfile.
 * @param referência ao arquivo sendo lido.
 */
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

/**
 * Função que le a constant pool de um arquivo .class
 * 
 * @param referência ao classfile.
 * @param referência ao arquivo sendo lido.
 */
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
				cp->info.Utf8.bytes = (uint8_t*) calloc ((cp->info.Utf8.length) + 1 ,sizeof(uint8_t));
				fread(cp->info.Utf8.bytes,1,cp->info.Utf8.length,file);
				cp->info.Utf8.bytes[cp->info.Utf8.length] = '\0';
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

/**
 * Função que le as interfaces de um arquivo .class
 * 
 * @param referência ao classfile.
 * @param referência ao arquivo sendo lido.
 * @param Quantidade de interfaces a serem lidas.
 */
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

/**
 * Função que le os fields de um arquivo .class
 * 
 * @param referência ao classfile.
 * @param referência ao arquivo sendo lido.
 * @param Quantidade de fields a serem lidas.
 */
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
            cf->fields[i].attributes = (CV_info*) malloc(cf->fields[i].attributes_count * sizeof(CV_info));
            
            // vai lendo atributos 
            for (int j = 0; j < cf->fields[i].attributes_count; j++)
            {
                // pega indice do nome do atributo e comprimento do atributo
                cf->fields[i].attributes->attribute_name_index = le2Bytes(file);
                cf->fields[i].attributes->attribute_length = le4Bytes(file);

                // pega constant value index
                cf->fields[i].attributes->constantvalue_index = le2Bytes(file);
            }
        }
	}
}

/**
 * Função que le os methods de um arquivo .class
 * 
 * @param referência ao classfile.
 * @param referência ao arquivo sendo lido.
 * @param Quantidade de methods a serem lidas.
 */
void methodInfo(classFile* cf, FILE* file, uint16_t methods_count){
    uint16_t name_ind; 
    uint32_t att_len; 

    if(methods_count == 0)
        return;
    else{
        cf->methods = (method_info*) malloc(methods_count*sizeof(method_info));
        method_info* cp = cf->methods;
        for(int i = 0; i < methods_count; cp++){

            cp->access_flags = le2Bytes(file);

            if(cp->access_flags == 0x010a ||cp->access_flags == 0x0101||cp->access_flags == 0x0111){
                cp->name_index = le2Bytes(file);
                cp->descriptor_index = le2Bytes(file);
                cp->attributes_count = le2Bytes(file);
                
                i++;
                for (int j = 0; j < cp->attributes_count; j++)
                {
                    int64_t temp, temp2; 

                    // pega atributo name index do metodo 
                    temp = le2Bytes(file); 
                    
                    // pega attributo length do metodo 
                    temp = le4Bytes(file); 

                    // vai lendo info 
                    for (int k = 0; k < temp; k++)
                    {
                        temp2 = le1Byte(file);
                    }
                    
                    
                }
                continue; 
            }

            cp->name_index = le2Bytes(file);
            cp->descriptor_index = le2Bytes(file);
            cp->attributes_count = le2Bytes(file);
            for(int j = 0; j < cp->attributes_count; j++)
            {
                // pega nome e indice 
                name_ind = le2Bytes(file);
                att_len = le4Bytes(file); 
                
                // se for um code 
                if (strcmp( (char*) cf->constant_pool[name_ind - 1].info.Utf8.bytes, "Code") == 0)
                {
                    // aloca espaco para o attribute
                    cp->cd_atrb = (code_attribute*) malloc(sizeof(code_attribute));

                    // le atribute
                    le_code(&(cp->cd_atrb), name_ind, att_len, file);
                }

                // senao, se for um exceptions
                else if (strcmp( (char*) cf->constant_pool[name_ind - 1].info.Utf8.bytes, "Exceptions") == 0) 
                {
                    // aloca espaco para o exceptions
                    cp->exc_atrb = (exceptions_attribute*) malloc(sizeof(exceptions_attribute));

                    // le exceptions
                    le_exc(&(cp->exc_atrb), name_ind, att_len, file);
                }
            }
            i++;
        }
    }
}

void le_exc(exceptions_attribute** exc_atrb, uint16_t name_ind, uint32_t att_len, FILE* file)
{
    // transfere informacoes relacionadas ao atributo 
    (*exc_atrb)->attribute_name_index = name_ind; 
    (*exc_atrb)->attribute_length = att_len; 

    // pega numero de excecoes 
    (*exc_atrb)->number_of_exceptions = le2Bytes(file);

    // aloca espaco apropriado para indices da tabela de excecoes
    (*exc_atrb)->exception_index_table = (uint16_t*) malloc( \
            (*exc_atrb)->number_of_exceptions * sizeof(exception_table));

    // vai lendo dados e imprimindo
    for (int k = 0; k < (*exc_atrb)->number_of_exceptions; k++)
    {
        (*exc_atrb)->exception_index_table[k] = le2Bytes(file);
        //printf("%d -  %d", k, (*exc_atrb)->exception_index_table[k]);
    }
}

void le_code(code_attribute** cd_atrb, uint16_t name_ind, uint32_t att_len, FILE* file)
{
    int posicao_inicial = ftell(file); 

    // transfere informacoes relacionadas ao atributo 
    (*cd_atrb)->attribute_name_index = name_ind; 
    (*cd_atrb)->attribute_length = att_len; 
    
    // leitura do bytecode relacionado a informacoes gerais
    (*cd_atrb)->max_stack = le2Bytes(file);
    (*cd_atrb)->max_locals = le2Bytes(file);
    (*cd_atrb)->code_length = le4Bytes(file);
    
    // salva instrucoes 
    salva_instrucoes(cd_atrb, file); 

    // pega tamanho da tabela de excecoes
    (*cd_atrb)->exception_table_length = le2Bytes(file);

    // aloca espaco apropriado
    (*cd_atrb)->exception_table = (exception_table*) malloc( \
            (*cd_atrb)->exception_table_length * sizeof(exception_table));

    // le dados da tabela de excecoes
    for (int k = 0; k < (*cd_atrb)->exception_table_length; k++)
    {
        (*cd_atrb)->exception_table[k].start_pc = le2Bytes(file);
        (*cd_atrb)->exception_table[k].end_pc = le2Bytes(file);
        (*cd_atrb)->exception_table[k].catch_type = le2Bytes(file);
    }

    // pega numero de atributos
    (*cd_atrb)->attributes_count = le2Bytes(file);
    
    // aloca espaco apropriado
    (*cd_atrb)->attributes = (attribute_info*) malloc ( \
            (*cd_atrb)->attributes_count * sizeof(attribute_info));

    // le atributos opcionais de debug
    // nao precisa preocupar muito com isso 
    while (ftell(file) - posicao_inicial < (*cd_atrb)->attribute_length) 
    {
        le1Byte(file);
    }
}

void salva_instrucoes(code_attribute** cd_atrb, FILE* file)
{
    int opcode, pos_referencia; 
    int bytes_preench, offsets;
    uint32_t default_v, low, high, npairs; 

    // obtem decodificador de instrucoes 
    decodificador dec[NUM_INSTRUCAO];
    inicializa_decodificador(dec); 

    // leitura do bytecode relacionado a instrucoes do metodo 
    // aloca espaco conveniente
    (*cd_atrb)->code = (uint8_t*) malloc((*cd_atrb)->code_length * \
            sizeof(uint8_t));

    // poe valor no espacos corretos
    // incrementamos k conforme formos passando no loop
    for(uint32_t k = 0; k < (*cd_atrb)->code_length; ) 
    {    
        // le opcode da instrucao atual
        fread(&((*cd_atrb)->code[k]), 1, 1, file);
        
        // pega opcode da instrucao
        opcode = (*cd_atrb)->code[k];
        k++; 

        if (opcode == TABLESWITCH)
        {
            // a posicao de referencia eh o label numerico associado a tableswitch 
            // k - 1 pois ja incrementamos o k para a proxima instrucao 
            pos_referencia = k - 1;

            // pega bytes de preenchimento 
            bytes_preench = k % 4;  
            for (int l = 0; l < bytes_preench; l++)
            {
                k++; 
                fread(&((*cd_atrb)->code[k]), 1, 1, file);
            }

            // pega bytes do target default
            default_v = 0;
            for (int l = 0; l < 4; l++)
            {
                fread(&((*cd_atrb)->code[k]), 1, 1, file);
                default_v = (default_v << 4) + (*cd_atrb)->code[k];   
                k++; 
            }       

            // pega bytes low
            low = 0;
            for (int l = 0; l < 4; l++)
            {
                fread(&((*cd_atrb)->code[k]), 1, 1, file);
                low = (low << 4) + (*cd_atrb)->code[k];   
                k++; 
            }       

            // pega bytes high 
            high = 0;
            for (int l = 0; l < 4; l++)
            {
                fread(&((*cd_atrb)->code[k]), 1, 1, file);
                high = (high << 4) + (*cd_atrb)->code[k];   
                k++; 
            }       
            
            // pega bytes de offset 
            offsets = 1 + high - low;
            for (int l = 0; l < offsets; l++)
            {
                // pega valor do offset atual 
                for (int i = 0; i < 4; i++)
                {
                    fread(&((*cd_atrb)->code[k]), 1, 1, file);
                    k++; 
                }

            } 
        }

        else if (opcode == LOOKUPSWITCH)
        {
            // a posicao de referencia eh o label numerico associado a tableswitch 
            // k - 1 pois ja incrementamos o k para a proxima instrucao 
            pos_referencia = k - 1;

            // pega bytes de preenchimento - nao salva em nenhum lugar
            bytes_preench = k % 4;  
            for (int l = 0; l < bytes_preench; l++)
            {
                k++; 
                fread(&((*cd_atrb)->code[k]), 1, 1, file);
            }

            // pega bytes do target default
            default_v = 0;
            for (int l = 0; l < 4; l++)
            {
                fread(&((*cd_atrb)->code[k]), 1, 1, file);
                default_v = (default_v << 4) + (*cd_atrb)->code[k];   
                k++; 
            }       

            // pega bytes low
            npairs = 0;
            for (int l = 0; l < 4; l++)
            {
                fread(&((*cd_atrb)->code[k]), 1, 1, file);
                npairs = (npairs << 4) + (*cd_atrb)->code[k];   
                k++; 
            }       

            // pega npairs 
            for (uint32_t l = 0; l < npairs; l++)
            {
                // pega valor do match atual 
                for (int i = 0; i < 4; i++)
                {
                    fread(&((*cd_atrb)->code[k]), 1, 1, file);
                    k++; 
                }

                // pega valor do offset 
                for (int i = 0; i < 4; i++)
                {
                    fread(&((*cd_atrb)->code[k]), 1, 1, file);
                    k++; 
                }

            } 

        }

        else if (opcode == WIDE)
        {

            // pega opcode que segue
            fread(&((*cd_atrb)->code[k]), 1, 1, file);
            opcode = (*cd_atrb)->code[k];
            k++; 

            // se o opcode for um iload, fload, ...
            if (opcode == ILOAD || opcode == FLOAD || opcode == ALOAD || opcode == LLOAD || \
                    opcode == DLOAD || opcode == ISTORE || opcode == FSTORE || opcode == ASTORE || \
                    opcode == LSTORE || opcode == DSTORE || opcode == RET)
            {
                // pega index byte1 
                fread(&((*cd_atrb)->code[k]), 1, 1, file);
                k++; 

                // pega index byte2
                fread(&((*cd_atrb)->code[k]), 1, 1, file);
                k++; 
                
            }

            // se for um iinc 
            else if (opcode == IINC)
            {

                // pega indexbyte1
                fread(&((*cd_atrb)->code[k]), 1, 1, file);
                k++; 

                // pega indexbyte2
                fread(&((*cd_atrb)->code[k]), 1, 1, file);
                k++; 

                // pega constbyte1
                fread(&((*cd_atrb)->code[k]), 1, 1, file);
                k++; 

                // pega constbyte2
                fread(&((*cd_atrb)->code[k]), 1, 1, file);
                k++; 

            }

            // senao
            else
            { 
                // arquivo .class corrompido! 
                printf("arquivo .class invalido na instrucao wide");
                exit(1);
            }
        }

        else
        {

            // obtem quantos operandos a instrucao tem e vai lendo operandos
            int num_bytes = dec[opcode].bytes;
            for (int l = 0; l < num_bytes; l++)
            {

                // pega operando 
                fread(&((*cd_atrb)->code[k]), 1, 1, file);

                // atualiza valor de k 
                k++;
            }

        }
    }
}

/**
 * Função que le os attributes de um arquivo .class
 * 
 * @param referência ao classfile.
 * @param referência ao arquivo sendo lido.
 * @param Quantidade de attributes a serem lidas.
 */
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
			for(uint32_t j = 0; j < cp->attribute_length; j++){
				fread(&cp->info[j],1,1,file);
			}
			i++;
		}
	}
}

/**
 * Função que le a segunda parte de informações gerais de um arquivo .class
 * 
 * @param referência ao classfile.
 * @param referência ao arquivo sendo lido.
 */
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

/**
 * Função que le 1 byte de um arquivo.
 * 
 * @param referência ao arquivo a ser lido
 */
static inline uint8_t le1Byte(FILE* fp){
	uint8_t retorno = getc(fp);
	return retorno;
}

/**
 * Função que le 2 bytes de um arquivo.
 * 
 * @param referência ao arquivo a ser lido
 */

static inline uint16_t le2Bytes(FILE* fp){
	uint16_t retorno = getc(fp); 
	retorno = (retorno << 8) | (getc(fp));
	return retorno;
}

/**
 * Função que le 4 bytes de um arquivo.
 * 
 * @param referência ao arquivo a ser lido
 */
static inline uint32_t le4Bytes(FILE* fp){
	uint32_t retorno = getc(fp);
	retorno = (retorno << 8) | (getc(fp));
	retorno = (retorno << 8) | (getc(fp));
	retorno = (retorno << 8) | (getc(fp));
	return retorno;
}
