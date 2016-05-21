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
	cf->magic = u4Read(file);
	cf->minor_version = u2Read(file);
	cf->major_version = u2Read(file);
	cf->constant_pool_count = u2Read(file);

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

	printf("----Constant Pool----\n");

	int i = 0;
	for(cp = cf->constant_pool; i < (cf->constant_pool_count-1); cp++){
		cp->tag = u1Read(file);
		printf("Tag: %d\n",cp->tag);
		switch(cp->tag){
			case CONSTANT_Class:
				cp->info.Class.name_index = u2Read(file);
				printf("CONSTANT_Class_info - name_index: cp info #%d\n",cp->info.Class.name_index);
				break;
			case CONSTANT_Fieldref:
				cp->info.Fieldref.class_index = u2Read(file);
				cp->info.Fieldref.name_and_type_index = u2Read(file);
				printf("CONSTANT_Fieldref_info - class_index: cp info #%d\n",cp->info.Fieldref.class_index);
				printf("CONSTANT_Fieldref_info - name_and_type_index: cp info #%d\n",cp->info.Fieldref.name_and_type_index);
				break;
			case CONSTANT_NameAndType:
				cp->info.NameAndType.name_index = u2Read(file);
				cp->info.NameAndType.descriptor_index = u2Read(file);
				printf("CONSTANT_NameAndType_info - name_index:cp info #%d\n",cp->info.NameAndType.name_index);
				printf("CONSTANT_NameAndType_info - descriptor_index: cp info #%d\n",cp->info.NameAndType.descriptor_index);
				break;
			case CONSTANT_Utf8:
				cp->info.Utf8.length = u2Read(file);
				cp->info.Utf8.bytes = (uint8_t*) malloc ((cp->info.Utf8.length)*sizeof(uint8_t));
				fread(cp->info.Utf8.bytes,1,cp->info.Utf8.length,file);
				printf("CONSTANT_Utf8_info - length:%d\n",cp->info.Utf8.length);
				printf("CONSTANT_Utf8_info - bytes: %s\n",cp->info.Utf8.bytes);
				break;
			case CONSTANT_Methodref:
				cp->info.Methodref.class_index = u2Read(file);
				cp->info.Methodref.name_and_type_index = u2Read(file);
				printf("CONSTANT_Methodref_info - class_index: cp info #%d\n",cp->info.Methodref.class_index);
				printf("CONSTANT_Methodref_info - name_and_type_index: cp info #%d\n",cp->info.Methodref.name_and_type_index);
				break;
			case CONSTANT_InterfaceMethodref:
				cp->info.InterfaceMethodref.class_index = u2Read(file);
				cp->info.InterfaceMethodref.name_and_type_index = u2Read(file);
				break;
			case CONSTANT_String:
				cp->info.String.string_index = u2Read(file);
				printf("CONSTANT_String_info - string_index: cp info #%d\n",cp->info.String.string_index);
				break;
			case CONSTANT_Integer:
				cp->info.Integer.bytes = u4Read(file);
				printf("CONSTANT_Integer_info - bytes:%d\n",cp->info.Integer.bytes);
				break;
			case CONSTANT_Float:
				cp->info.Float.bytes = u4Read(file);
				printf("CONSTANT_Float_info - bytes:%d\n",cp->info.Float.bytes);
				break;
			default:
				break;
		}
		i++;
	}
	printf("----End Pool----\n\n");
}

void interfaceInfo(classFile* cf, FILE* file, uint16_t interfaces_count){
	if(interfaces_count == 0)
		return;
	else{

        // aloca espaco apropriado
        cf->interfaces = (uint16_t *) malloc((interfaces_count) * sizeof(uint16_t));

        printf("---- Interfaces ----\n");

        // le interface, pondo no array elementos corretos
        for (int i = 0; i < interfaces_count; i++)
        {
            cf->interfaces[i] = u2Read(file);
            printf("Interface: cp info #%d\n", cf->interfaces[i]);
        }

        printf("---- End Interface ----\n");
	}
}

void fieldInfo(classFile* cf, FILE* file, uint16_t fields_count){
	if(fields_count == 0)
		return;
	else{
		// Ler estrutura de fields.
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
			cp->access_flags = u2Read(file);
			cp->name_index = u2Read(file);
			cp->descriptor_index = u2Read(file);
			cp->attributes_count = u2Read(file);
			cp->attributes = (attribute_info*) malloc(cp->attributes_count*sizeof(attribute_info));
			printf("access_flag: 0x%0x\n",cp->access_flags);
			printf("name_index: cp info #%d\n",cp->name_index);
			printf("descriptor_index: cp info #%d\n",cp->descriptor_index);
			printf("attributes_count: %d\n",cp->attributes_count);

			for(int j = 0; j < cp->attributes_count; cp->attributes++){
				printf("----Attributes Info----\n");
				cp->attributes->attribute_name_index = u2Read(file);
				cp->attributes->attribute_length = u4Read(file);
				printf("attribute_name_index: cp info #%d\n",cp->attributes->attribute_name_index);
				printf("attribute_length: %d\n",cp->attributes->attribute_length);
				cp->attributes->info = (uint8_t*) malloc((cp->attributes->attribute_length)*sizeof(uint8_t));
				fread(cp->attributes->info,1,cp->attributes->attribute_length,file);
				printf("bytecode: 0x%0x\n",*cp->attributes->info);
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

			cp->attribute_name_index = u2Read(file);
			cp->attribute_length = u4Read(file);
			printf("attribute_name_index: cp info #%d\n",cp->attribute_name_index);
			printf("attribute_length: %d\n",cp->attribute_length);
			cp->info = (uint8_t*) malloc((cp->attribute_length)*sizeof(uint8_t));
			fread(cp->info,1,cp->attribute_length,file);
			printf("bytecode: 0x%0x\n",*(cp->info));
			i++;
		}
	}
}

void secondGeneralInfo(classFile* cf, FILE* file){
    int i;

	cf->access_flags = u2Read(file);
	cf->this_class = u2Read(file);
	cf->super_class = u2Read(file);

	cf->interfaces_count = u2Read(file);
	interfaceInfo(cf,file,cf->interfaces_count);

	//fieldInfo TODO.
	cf->fields_count = u2Read(file);
	fieldInfo(cf,file,cf->fields_count);

	printf("----Second General Info----\n");
	printf("Access Flags: 0x%0x\n",cf->access_flags);
	printf("This Class: cp info #%d\n",cf->this_class);
	printf("Super Class: cp info #%d\n",cf->super_class);
	printf("interfaces_count: %d\n",cf->interfaces_count);
	printf("Fields Count: %d\n\n",cf->fields_count);

	printf("----Method Info----\n");

	cf->methods_count = u2Read(file);
	printf("Methods Count: %d\n",cf->methods_count);
	methodInfo(cf,file,cf->methods_count);

	printf("----Attributes Info----\n");

	cf->attributes_count = u2Read(file);
	printf("attributes_count: %d\n",cf->attributes_count);
	attributeInfo(cf,file,cf->attributes_count);
	
	printf("----End Attributes----\n\n");

	printf("----End Second General----\n\n");
}



// funcoes auxiliares para leitura.
static inline uint8_t u1Read(FILE* fp){
	uint8_t retorno = getc(fp);
	return retorno;
}

static inline uint16_t u2Read(FILE* fp){
	uint16_t retorno = getc(fp); 
	retorno = (retorno << 8) | (getc(fp));
	return retorno;
}

static inline uint32_t u4Read(FILE* fp){
	uint32_t retorno = getc(fp);
	retorno = (retorno << 8) | (getc(fp));
	retorno = (retorno << 8) | (getc(fp));
	retorno = (retorno << 8) | (getc(fp));
	return retorno;
}
#endif
