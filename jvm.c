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

int main(int argc, char* argv[]){
	//Abre arquivo passado via linha de comando
	FILE* file;
	file = fopen(argv[1], "rb");

	//Aloca memória para a estrutura do .class
	classFile* cf = (classFile*) malloc(sizeof(classFile));

	//Le e imprime informações gerais.
	generalInfo(cf,file);
	

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
				printf("CONSTANT_Class_info - name_index:%d\n",cp->info.Class.name_index);
				break;
			case CONSTANT_Fieldref:
				cp->info.Fieldref.class_index = u2Read(file);
				cp->info.Fieldref.name_and_type_index = u2Read(file);
				printf("CONSTANT_Fieldref_info - class_index:%d\n",cp->info.Fieldref.class_index);
				printf("CONSTANT_Fieldref_info - name_and_type_index:%d\n",cp->info.Fieldref.name_and_type_index);
				break;
			case CONSTANT_NameAndType:
				cp->info.NameAndType.name_index = u2Read(file);
				cp->info.NameAndType.descriptor_index = u2Read(file);
				printf("CONSTANT_NameAndType_info - name_index:%d\n",cp->info.NameAndType.name_index);
				printf("CONSTANT_NameAndType_info - descriptor_index:%d\n",cp->info.NameAndType.descriptor_index);
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
				printf("CONSTANT_Methodref_info - class_index:%d\n",cp->info.Methodref.class_index);
				printf("CONSTANT_Methodref_info - name_and_type_index:%d\n",cp->info.Methodref.name_and_type_index);
				break;
			case CONSTANT_InterfaceMethodref:
				cp->info.InterfaceMethodref.class_index = u2Read(file);
				cp->info.InterfaceMethodref.name_and_type_index = u2Read(file);
				break;
			case CONSTANT_String:
				cp->info.String.string_index = u2Read(file);
				printf("CONSTANT_String_info - string_index:%d\n",cp->info.String.string_index);
				break;
			case CONSTANT_Integer:
				cp->info.Integer.bytes = u4Read(file);
				break;
			case CONSTANT_Float:
				cp->info.Float.bytes = u4Read(file);
				break;
			default:
				break;
		}
		i++;
	}
	printf("----End----\n");

	return 0;
}