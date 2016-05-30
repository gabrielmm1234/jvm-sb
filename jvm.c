#ifndef LEITOR_EXIBIDOR_C
#define LEITOR_EXIBIDOR_C
#include "jvm.h"

int main(int argc, char* argv[]){
	//Abre arquivo passado via linha de comando
	FILE* file;
	file = fopen(argv[1], "rb");

	//Aloca memória para a estrutura do .class
	classFile* cf = (classFile*) malloc(sizeof(classFile));

	//Le e imprime informações gerais.
	generalInfo(cf,file);

	//Le e imprime a constant pool
	constantPool(cf,file);

	//le e imprime informações gerais após a constant pool
	secondGeneralInfo(cf,file);
	
	return 0;
}

void generalInfo(classFile* cf, FILE* file){
	cf->magic = le4Bytes(file);
	cf->minor_version = le2Bytes(file);
	cf->major_version = le2Bytes(file);
	cf->constant_pool_count = le2Bytes(file);

	printf("----General Information----\n");
	printf("CAFEBABE: 0x%0x \n",cf->magic);
	printf("Minor version: %d \n",cf->minor_version);
	printf("Major version: %d \n",cf->major_version);
	printf("Constant Pool Count: %d \n",cf->constant_pool_count);
	printf("----End General----\n\n");
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
			default:
				break;
		}
		i++;
	}
    

    // agora imprime-se a cte pool 
	printf("----Constant Pool----\n");

    // itera pela constante pool de novo, dessa vez para mostrar informacao 
    for (int i = 0; i < cf->constant_pool_count - 1; i++)
    {
        // pega tag
        int tag = cf->constant_pool[i].tag; 

        // de acordo com a tag em que estamos, decide o que fazer   
        switch (tag)
        {
			case CONSTANT_Class:
				printf("[%d] CONSTANT_Class_info - name_index: cp info #%d ", i+1, cf->constant_pool[i].info.Class.name_index);
                imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Class.name_index - 1);
                printf("\n");

				break;

			case CONSTANT_Fieldref:
				printf("[%d] CONSTANT_Fieldref_info - class_index: cp info #%d ", i+1, cf->constant_pool[i].info.Fieldref.class_index);
                imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Fieldref.class_index - 1);
                printf("\n");

				printf("[%d] CONSTANT_Fieldref_info - name_and_type_index: cp info #%d ", i+1, cf->constant_pool[i].info.Fieldref.name_and_type_index);
                imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Fieldref.name_and_type_index - 1);
                printf("\n");

				break;

			case CONSTANT_NameAndType:
				printf("[%d] CONSTANT_NameAndType_info - name_index: cp info info #%d ", i+1, cf->constant_pool[i].info.NameAndType.name_index);
                imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.NameAndType.name_index - 1);
                printf("\n");

				printf("[%d] CONSTANT_NameAndType_info - descriptor_index: cp info #%d ", i+1, cf->constant_pool[i].info.NameAndType.descriptor_index);
                imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.NameAndType.descriptor_index - 1 );
                printf("\n");

				break;

			case CONSTANT_Utf8:
				printf("[%d] CONSTANT_Utf8_info - length:%d\n",i+1,cf->constant_pool[i].info.Utf8.length);
				printf("[%d] CONSTANT_Utf8_info - bytes: %s\n",i+1,cf->constant_pool[i].info.Utf8.bytes);
				break;

			case CONSTANT_Methodref:
				printf("[%d] CONSTANT_Methodref_info - class_index: cp info #%d ",i+1,cf->constant_pool[i].info.Methodref.class_index);
                imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Methodref.class_index - 1);
                printf("\n");

				printf("[%d] CONSTANT_Methodref_info - name_and_type_index: cp info #%d ",i+1,cf->constant_pool[i].info.Methodref.name_and_type_index);
                imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Methodref.name_and_type_index - 1);
                printf("\n");

				break;

			case CONSTANT_InterfaceMethodref:
				printf("[%d] CONSTANT_InterfaceMethodref_info - class_index: cp info #%d ",i+1,cf->constant_pool[i].info.InterfaceMethodref.class_index);
                imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Methodref.class_index - 1);
                printf("\n");

				printf("[%d] CONSTANT_InterfaceMethodref_info - name_and_type_index: cp info #%d ",i+1,cf->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
                imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Methodref.name_and_type_index - 1);
                printf("\n");

				break;

			case CONSTANT_String:
				printf("[%d] CONSTANT_String_info - string_index: cp info #%d ",i+1,cf->constant_pool[i].info.String.string_index);
                imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.String.string_index - 1);
                printf("\n");
				break;

			case CONSTANT_Integer:
				printf("[%d] CONSTANT_Integer_info - bytes:%d\n",i+1,cf->constant_pool[i].info.Integer.bytes);
				break;

			case CONSTANT_Float:
				printf("[%d] CONSTANT_Float_info - bytes:%d\n",i+1,cf->constant_pool[i].info.Float.bytes);
				break;

			default:
				break;
        }
    }

	printf("----End Pool----\n\n");
}

void imprime_string_pool(cp_info* cp, int pos_pool)
{
    int tag;

    // pega tag 
    tag = cp[pos_pool].tag;

    // se a tag for o de um class info 
    if (tag == CONSTANT_Utf8)
    {
        // imprime informacao e sai
        printf("%s  ", cp[pos_pool].info.Utf8.bytes);
        return;
    }

    // senao, de acordo com a tag, decide qual sera a proxima posicao da cte pool que iremos olhar
    switch(tag)
    {
        case CONSTANT_Class:
            imprime_string_pool(cp, cp[pos_pool].info.Class.name_index - 1);
            break;

        case CONSTANT_Fieldref:
            imprime_string_pool(cp, cp[pos_pool].info.Fieldref.class_index - 1); 
            imprime_string_pool(cp, cp[pos_pool].info.Fieldref.name_and_type_index - 1); 
            break;

        case CONSTANT_NameAndType:
            imprime_string_pool(cp, cp[pos_pool].info.NameAndType.name_index - 1 ); 
            imprime_string_pool(cp, cp[pos_pool].info.NameAndType.descriptor_index - 1); 
            break;

        case CONSTANT_Methodref:
            imprime_string_pool(cp, cp[pos_pool].info.Methodref.class_index - 1); 
            imprime_string_pool(cp, cp[pos_pool].info.Methodref.name_and_type_index - 1); 
            break;
            
        case CONSTANT_InterfaceMethodref:
            imprime_string_pool(cp, cp[pos_pool].info.InterfaceMethodref.class_index - 1); 
            imprime_string_pool(cp, cp[pos_pool].info.InterfaceMethodref.name_and_type_index - 1); 
            break;
            
        case CONSTANT_String:
            imprime_string_pool(cp, cp[pos_pool].info.String.string_index - 1); 
            break;

        case CONSTANT_Integer:
            // nunca cairemos aqui
            break;

        case CONSTANT_Float:
            // nunca cairemos aqui
            break;

        default:
            break;
    }

}
void interfaceInfo(classFile* cf, FILE* file, uint16_t interfaces_count){
	if(interfaces_count == 0)
		return;
	else{

        // aloca espaco apropriado
        cf->interfaces = (uint16_t *) malloc((interfaces_count) * sizeof(uint16_t));

        printf("---- Interfaces ----\n");

        // le interface, pondo no array de interfaces
        for (int i = 0; i < interfaces_count; i++)
        {
            cf->interfaces[i] = le2Bytes(file);
            printf("Interface: cp info #%d\n", cf->interfaces[i]);
        }

        printf("---- End Interface ----\n");
	}
}

void fieldInfo(classFile* cf, FILE* file, uint16_t fields_count){
	if(fields_count == 0)
		return;
	else{
       
        // aloca espaco apropriado
        cf->fields = (field_info*) malloc(fields_count * sizeof(field_info)); 
        
        printf("----Fields----\n");

        // le field information, pondo no array de field
        for (int i = 0; i < fields_count; i++)
        {
            // pega bits de acesso, indice do nome e indice do descritor
            cf->fields[i].access_flags = le2Bytes(file);
            cf->fields[i].name_index = le2Bytes(file);
            cf->fields[i].descriptor_index = le2Bytes(file);

            // imprime informacoes
            printf("Name: cp info #%d\n", cf->fields[i].name_index);
            printf("Descriptor: cp info #%d\n", cf->fields[i].descriptor_index);
            printf("Access Flag: cp info #0x%x\n", cf->fields[i].access_flags);

            cf->fields[i].attributes_count = le2Bytes(file);

            // aloca espaco para o array de atributos
            cf->fields[i].attributes = (attribute_info*) malloc(cf->fields[i].attributes_count * sizeof(attribute_info));
            
            // vai lendo e imprimindo atributos 
            for (int j = 0; j < cf->fields[i].attributes_count; j++)
            {
                printf("\t\t----Attribute Info do Field----\n");
                
                // pega indice do nome do atributo e comprimento do atributo
                cf->fields[i].attributes->attribute_name_index = le2Bytes(file);
                cf->fields[i].attributes->attribute_length = le4Bytes(file);

                // imprime informacao dos atributos
                printf("attribute_name_index: cp info #%d\n", cf->fields[i].attributes->attribute_name_index);
                printf("attribute_length: %d\n", cf->fields[i].attributes->attribute_length);

                // espaco para informacao do atributo
                cf->fields[i].attributes->info = (uint8_t*) malloc(cf->fields[i].attributes->attribute_length * sizeof(uint8_t));
                
                // le informacao do atributo
                fread(cf->fields[i].attributes->info, 1, cf->fields[i].attributes->attribute_length, file);

                // imprime bytecode do atributo
                for (int k = 0; k < cf->fields[i].attributes->attribute_length; k++)
                {
                    fread(&(cf->fields[i].attributes->info[k]), 1, 1, file);
                    
                    printf("bytecode: 0x%x\n", cf->fields[i].attributes->info[k]);
                }

                printf("\t\t----Fim da Attribute Info do Field----\n");
            }
        }

        printf("----Fields----\n");
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
			cp->attributes = (attribute_info*) malloc(cp->attributes_count*sizeof(attribute_info));
			printf("access_flag: 0x%0x\n",cp->access_flags);
			printf("name_index: cp info #%d ",cp->name_index);
			imprime_string_pool(cf->constant_pool, cp->name_index - 1);
    		printf("\n");
			printf("descriptor_index: cp info #%d ",cp->descriptor_index);
			imprime_string_pool(cf->constant_pool, cp->descriptor_index - 1);
    		printf("\n");
			printf("attributes_count: %d\n",cp->attributes_count);

			for(int j = 0; j < cp->attributes_count; cp->attributes++){
				printf("----Attributes Info----\n");
				cp->attributes->attribute_name_index = le2Bytes(file);
				cp->attributes->attribute_length = le4Bytes(file);
				printf("attribute_name_index: cp info #%d ",cp->attributes->attribute_name_index);
				imprime_string_pool(cf->constant_pool, cp->attributes->attribute_name_index - 1);
    			printf("\n");
				printf("attribute_length: %d\n",cp->attributes->attribute_length);
				cp->attributes->info = (uint8_t*) malloc((cp->attributes->attribute_length)*sizeof(uint8_t));
                
                int code_length; // sera importante para saber como parar o segundo loop 

                // leitura do bytecode relacionado a informacoes gerais
				for(int k = 0; k < 8; k++)
                {
                    fread(&(cp->attributes->info[k]), 1, 1, file);

                    // imprime profundidade maxima do stack
                    if (k == 1) 
                    {
                        int max_stack_depth =  (cp->attributes->info[k-1] << 4) + cp->attributes->info[k]; 
                        printf("Maximum stack depth: %d\n", max_stack_depth); 
                    }

                    // imprime numero maximo de local variables 
                    if (k == 3)
                    {
                        int max_local_var = (cp->attributes->info[k-1] << 4) + cp->attributes->info[k]; 
                        printf("Maximum local variables: %d\n", max_local_var);
                    }

                    // imprime tamanho do codigo 
                    if (k == 7)
                    {
                         code_length = 0;
                         code_length += (cp->attributes->info[k-3] << 12);
                         code_length += (cp->attributes->info[k-2] << 8);
                         code_length += (cp->attributes->info[k-1] << 4);
                         code_length += cp->attributes->info[k];
                        printf("Code Length: %d\n", code_length);
                    }

                }
               
                // obtem decodificador de instrucoes 
                decodificador dec[NUM_INSTRUCAO];
                inicializa_decodificador(dec); 

                // leitura do bytecode relacionado a instrucoes do metodo 
				for(int k = 8; k-8 < code_length; k++)
                {    
                    // le opcode da instrucao atual
                    fread(&(cp->attributes->info[k]), 1, 1, file);
                    
                    // imprime instrucao
                    int indice = cp->attributes->info[k];
                    printf("%d: %s  ", k-8, dec[indice].instrucao);

                    // obtem quantos operandos a instrucao tem e vai imprimindo operandos
                    int num_bytes = dec[indice].bytes;
                    for (int l = 0; l < num_bytes; l++)
                    {
                        // atualiza valor de k 
                        k++;

                        // pega operando 
                        fread(&(cp->attributes->info[k]), 1, 1, file);
                        
                        // operandos sao impressos do jeito que saem 
                        printf("0x%0x  ", cp->attributes->info[k]);
                    }
                    
                    // pula linha
                    printf("\n"); 
				}
                
                // leitura dos demais bytecodes - NAO SEI PARA QUE ISSO SERVE 
                for (int k = 8 + code_length; k < cp->attributes->attribute_length; k++)
                {
                    fread(&(cp->attributes->info[k]), 1, 1, file);
                }
                
				printf("----End Attribute----\n\n");
				j++;
			}
			i++;
			printf("----End Method----\n\n");
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
			printf("attribute_name_index: cp info #%d ",cp->attribute_name_index);
			imprime_string_pool(cf->constant_pool, cp->attribute_name_index - 1);
    		printf("\n");
			printf("attribute_length: %d\n",cp->attribute_length);
			cp->info = (uint8_t*) malloc((cp->attribute_length)*sizeof(uint8_t));
			for(int j = 0; j < cp->attribute_length; cp->info++){
			fread(cp->info,1,1,file);
			printf("Source file name index: cp info #%d ",*(cp->info));
			if(*(cp->info) != 0)
				imprime_string_pool(cf->constant_pool, *(cp->info) - 1);
	    	printf("\n");
			j++;
			}
			i++;
		}
	}
}

void secondGeneralInfo(classFile* cf, FILE* file){
    int i;

	cf->access_flags = le2Bytes(file);
	cf->this_class = le2Bytes(file);
	cf->super_class = le2Bytes(file);

	cf->interfaces_count = le2Bytes(file);
	interfaceInfo(cf,file,cf->interfaces_count);

	cf->fields_count = le2Bytes(file);
	fieldInfo(cf,file,cf->fields_count);

	printf("----Second General Info----\n");
	printf("Access Flags: 0x%0x\n",cf->access_flags);
	printf("This Class: cp info #%d ",cf->this_class);
	imprime_string_pool(cf->constant_pool, cf->this_class - 1);
    printf("\n");
	printf("Super Class: cp info #%d ",cf->super_class);
	imprime_string_pool(cf->constant_pool, cf->super_class - 1);
    printf("\n");
	printf("interfaces_count: %d\n",cf->interfaces_count);
	printf("Fields Count: %d\n\n",cf->fields_count);

	printf("----Method Info----\n");

	cf->methods_count = le2Bytes(file);
	printf("Methods Count: %d\n",cf->methods_count);
	methodInfo(cf,file,cf->methods_count);

	printf("----Attributes Info----\n");

	cf->attributes_count = le2Bytes(file);
	printf("attributes_count: %d\n",cf->attributes_count);
	attributeInfo(cf,file,cf->attributes_count);
	
	printf("----End Attributes----\n\n");

	printf("----End Second General----\n\n");
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
