/*Includes*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>


/*Defines*/
#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1



/*Struct de informações da constant pool*/

typedef struct attribute_info{
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	uint8_t* info;
}attribute_info;

typedef struct field_info{
	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	attribute_info* attributes;
}field_info;

typedef struct cp_info{
	uint8_t tag;
	union{
		struct {
			uint16_t name_index;
		}Class;
		struct{
			uint16_t class_index;
			uint16_t name_and_type_index;
		}Fieldref;
		struct{
			uint16_t name_index;
			uint16_t descriptor_index;
		}NameAndType;
		struct{
			uint16_t length;
			uint8_t* bytes;
		}Utf8;
		struct{
			uint16_t class_index;
			uint16_t name_and_type_index;
		}Methodref;
		struct{
			uint16_t class_index;
			uint16_t name_and_type_index;
		}InterfaceMethodref;
		struct{
			uint16_t string_index;
		}String;
		struct{
			uint32_t bytes;
		}Integer;
		struct{
			uint32_t bytes;
		}Float;
		struct{
			uint32_t high_bytes;
			uint32_t low_bytes;
		}Long;
		struct{
			uint32_t high_bytes;
			uint32_t low_bytes;
		}Double;
	}info;
}cp_info;

/*Struct que representa o .class*/
typedef struct ClassFile{
	uint32_t magic;
	uint16_t minor_version;
	uint16_t major_version;
	uint16_t constant_pool_count;
	cp_info* constant_pool;
	uint16_t access_flags;
	uint16_t this_class;
	uint16_t super_class;
	uint16_t interfaces_count;
	uint16_t* interfaces;
	uint16_t fields_count;
	field_info* fields;
	uint16_t methods_count;
}classFile;



/*Funções auxiliares*/

// Função que le 1 byte do arquivo
static inline uint8_t u1Read(FILE* fp){
	uint8_t retorno = getc(fp);
	return retorno;
}

// Função que le 2 bytes do arquivo
static inline uint16_t u2Read(FILE* fp){
	uint16_t retorno = getc(fp); 
	retorno = (retorno << 8) | (getc(fp));
	return retorno;
}

// Função que le 4 bytes de um arquivo
static inline uint32_t u4Read(FILE* fp){
	uint32_t retorno = getc(fp);
	retorno = (retorno << 8) | (getc(fp));
	retorno = (retorno << 8) | (getc(fp));
	retorno = (retorno << 8) | (getc(fp));
	return retorno;
}

// Função que le informações gerais do arquivo - Antes da constant pool
void generalInfo(classFile* cf,FILE* file){
	cf->magic = u4Read(file);
	cf->minor_version = u2Read(file);
	cf->major_version = u2Read(file);
	cf->constant_pool_count = u2Read(file);

	printf("----General Information----\n");
	printf("CAFEBABE: 0x%0x \n",cf->magic);
	printf("Minor version: %d \n",cf->minor_version);
	printf("Major version: %d \n",cf->major_version);
	printf("Constant Pool Count: %d \n",cf->constant_pool_count);
	printf("----End----\n\n");
}

void constantPool(classFile* cf,FILE* file){
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
				char* string_aux = (char*) malloc((cp->info.Utf8.length)*sizeof(char));
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
	printf("----End----\n\n");
}

void le_interfaces(classFile* cf, FILE* file, int qtd_a_ler)
{
    // aloca espaco apropriado
    cf->interfaces = (uint16_t *) malloc((qtd_a_ler) * sizeof(uint16_t));

    // le interface, pondo no array elementos corretos
    for (int i = 0; i < qtd_a_ler; i++)
    {
        cf->interfaces[i] = u2Read(file);
    }
}

void secondGeneralInfo(classFile* cf,FILE* file){
	cf->access_flags = u2Read(file);
	cf->this_class = u2Read(file);
	cf->super_class = u2Read(file);
	cf->interfaces_count = u2Read(file);
	
    // LER INTERFACES TODO
    le_interfaces(cf, file, cf->interfaces_count);

	cf->fields_count = u2Read(file);
	// LER FIELDS TODO
	cf->methods_count = u2Read(file);
	// LER METHODS TODO
	printf("----Second General Info----\n");
	printf("Access Flags: 0x%0x\n",cf->access_flags);
	printf("This Class: cp info #%d\n",cf->this_class);
	printf("Super Class: cp info #%d\n",cf->super_class);
	printf("interfaces_count: %d\n",cf->interfaces_count);
	printf("Fields Count: %d\n",cf->fields_count);
	printf("Methods Count: %d\n",cf->methods_count);
	printf("----End----\n\n");
}

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
