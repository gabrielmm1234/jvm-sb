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

void imprime_arq_pool(cp_info* cp, int pos_pool,FILE* file)
{
    int tag;

    // pega tag 
    tag = cp[pos_pool].tag;

    // se a tag for o de um class info 
    if (tag == CONSTANT_Utf8)
    {
        // imprime informacao e sai
        fprintf(file,"%s  ", cp[pos_pool].info.Utf8.bytes);
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

void imprimeArq(classFile* cf){
	FILE * pFile;
	pFile = fopen ("ClassFile.txt","w");
	fprintf(pFile,"----General Information----\n");
	fprintf(pFile,"CAFEBABE: 0x%0x \n",cf->magic);
	fprintf(pFile,"Minor version: %d \n",cf->minor_version);
	fprintf(pFile,"Major version: %d \n",cf->major_version);
	fprintf(pFile,"Constant Pool Count: %d \n",cf->constant_pool_count);
	fprintf(pFile,"----End General----\n\n");

	// agora imprime-se a cte pool 
	fprintf(pFile,"----Constant Pool----\n");

    // itera pela constante pool de novo, dessa vez para mostrar informacao 
    for (int i = 0; i < cf->constant_pool_count - 1; i++)
    {
        // pega tag
        int tag = cf->constant_pool[i].tag; 

        // de acordo com a tag em que estamos, decide o que fazer   
        switch (tag)
        {
			case CONSTANT_Class:
				fprintf(pFile,"[%d] CONSTANT_Class_info - name_index: cp info #%d ", i+1, cf->constant_pool[i].info.Class.name_index);
                imprime_arq_pool(cf->constant_pool, cf->constant_pool[i].info.Class.name_index - 1,pFile);
                fprintf(pFile,"\n");

				break;

			case CONSTANT_Fieldref:
				fprintf(pFile,"[%d] CONSTANT_Fieldref_info - class_index: cp info #%d ", i+1, cf->constant_pool[i].info.Fieldref.class_index);
                imprime_arq_pool(cf->constant_pool, cf->constant_pool[i].info.Fieldref.class_index - 1,pFile);
                fprintf(pFile,"\n");

				fprintf(pFile,"[%d] CONSTANT_Fieldref_info - name_and_type_index: cp info #%d ", i+1, cf->constant_pool[i].info.Fieldref.name_and_type_index);
                imprime_arq_pool(cf->constant_pool, cf->constant_pool[i].info.Fieldref.name_and_type_index - 1,pFile);
                fprintf(pFile,"\n");

				break;

			case CONSTANT_NameAndType:
				fprintf(pFile,"[%d] CONSTANT_NameAndType_info - name_index: cp info info #%d ", i+1, cf->constant_pool[i].info.NameAndType.name_index);
                imprime_arq_pool(cf->constant_pool, cf->constant_pool[i].info.NameAndType.name_index - 1,pFile);
                fprintf(pFile,"\n");

				fprintf(pFile,"[%d] CONSTANT_NameAndType_info - descriptor_index: cp info #%d ", i+1, cf->constant_pool[i].info.NameAndType.descriptor_index);
                imprime_arq_pool(cf->constant_pool, cf->constant_pool[i].info.NameAndType.descriptor_index - 1,pFile);
                fprintf(pFile,"\n");

				break;

			case CONSTANT_Utf8:
				fprintf(pFile,"[%d] CONSTANT_Utf8_info - length:%d\n",i+1,cf->constant_pool[i].info.Utf8.length);
				fprintf(pFile,"[%d] CONSTANT_Utf8_info - bytes: %s\n",i+1,cf->constant_pool[i].info.Utf8.bytes);
				break;

			case CONSTANT_Methodref:
				fprintf(pFile,"[%d] CONSTANT_Methodref_info - class_index: cp info #%d ",i+1,cf->constant_pool[i].info.Methodref.class_index);
                imprime_arq_pool(cf->constant_pool, cf->constant_pool[i].info.Methodref.class_index - 1,pFile);
                fprintf(pFile,"\n");

				fprintf(pFile,"[%d] CONSTANT_Methodref_info - name_and_type_index: cp info #%d ",i+1,cf->constant_pool[i].info.Methodref.name_and_type_index);
                imprime_arq_pool(cf->constant_pool, cf->constant_pool[i].info.Methodref.name_and_type_index - 1,pFile);
                fprintf(pFile,"\n");

				break;

			case CONSTANT_InterfaceMethodref:
				fprintf(pFile,"[%d] CONSTANT_InterfaceMethodref_info - class_index: cp info #%d ",i+1,cf->constant_pool[i].info.InterfaceMethodref.class_index);
                imprime_arq_pool(cf->constant_pool, cf->constant_pool[i].info.Methodref.class_index - 1,pFile);
                fprintf(pFile,"\n");

				fprintf(pFile,"[%d] CONSTANT_InterfaceMethodref_info - name_and_type_index: cp info #%d ",i+1,cf->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
                imprime_arq_pool(cf->constant_pool, cf->constant_pool[i].info.Methodref.name_and_type_index - 1,pFile);
                fprintf(pFile,"\n");

				break;

			case CONSTANT_String:
				fprintf(pFile,"[%d] CONSTANT_String_info - string_index: cp info #%d ",i+1,cf->constant_pool[i].info.String.string_index);
                imprime_arq_pool(cf->constant_pool, cf->constant_pool[i].info.String.string_index - 1,pFile);
                fprintf(pFile,"\n");
				break;

			case CONSTANT_Integer:
				fprintf(pFile,"[%d] CONSTANT_Integer_info - bytes:%d\n",i+1,cf->constant_pool[i].info.Integer.bytes);
				break;

			case CONSTANT_Float:
				fprintf(pFile,"[%d] CONSTANT_Float_info - bytes:%d\n",i+1,cf->constant_pool[i].info.Float.bytes);
				break;
			case CONSTANT_Double:
				fprintf(pFile,"[%d] CONSTANT_Double_info - high-bytes: 0x%0x\n",i+1,cf->constant_pool[i].info.Double.high_bytes);
				fprintf(pFile,"[%d] CONSTANT_Double_info - low-bytes: 0x%0x\n",i+1,cf->constant_pool[i].info.Double.low_bytes);
				break;
			default:
				break;
        }
    }
	fprintf(pFile,"----End Pool----\n\n");

	fprintf(pFile,"----Second General Info----\n");
	fprintf(pFile,"Access Flags: 0x%0x\n",cf->access_flags);
	fprintf(pFile,"This Class: cp info #%d ",cf->this_class);
	imprime_arq_pool(cf->constant_pool, cf->this_class - 1,pFile);
    fprintf(pFile,"\n");
	fprintf(pFile,"Super Class: cp info #%d ",cf->super_class);
	imprime_arq_pool(cf->constant_pool, cf->super_class - 1,pFile);
    fprintf(pFile,"\n");
	printf("interfaces_count: %d\n",cf->interfaces_count);
	if(cf->interfaces_count != 0){
		printf("---- Interfaces ----\n");
        // le interface, pondo no array de interfaces
        for (int i = 0; i < cf->interfaces_count; i++)
        {
            printf("Interface: cp info #%d ", cf->interfaces[i]);
            imprime_string_pool(cf->constant_pool, cf->interfaces[i] - 1);
    		printf("\n");
        }

    	printf("---- End Interface ----\n");
	}
	printf("Fields Count: %d\n",cf->fields_count);
	if(cf->fields_count != 0){
		printf("----Fields----\n");
        for (int i = 0; i < cf->fields_count; i++)
        {

            // imprime informacoes
            printf("Name: cp info #%d ", cf->fields[i].name_index);
            imprime_string_pool(cf->constant_pool, cf->fields[i].name_index - 1);
    		printf("\n");
            printf("Descriptor: cp info #%d ", cf->fields[i].descriptor_index);
            imprime_string_pool(cf->constant_pool, cf->fields[i].descriptor_index - 1);
    		printf("\n");
            printf("Access Flag: 0x%x\n", cf->fields[i].access_flags);
 
            for (int j = 0; j < cf->fields[i].attributes_count; j++)
            {
                printf("\t\t----Attribute Info do Field----\n");
                
                // imprime informacao dos atributos
                printf("attribute_name_index: cp info #%d\n", cf->fields[i].attributes->attribute_name_index);
                printf("attribute_length: %d\n", cf->fields[i].attributes->attribute_length);

                // imprime bytecode do atributo
                for (int k = 0; k < cf->fields[i].attributes->attribute_length; k++)
                {
                    printf("bytecode: 0x%x\n", cf->fields[i].attributes->info[k]);
                }

                printf("\t\t----Fim da Attribute Info do Field----\n");
            }
        }

        printf("----End Fields----\n");
	}

	printf("Methods Count: %d\n",cf->methods_count);
	if(cf->methods_count != 0){
		method_info* cp = cf->methods;
		for(int i = 0; i < cf->methods_count; cp++){
			printf("----Method Info----\n");
			printf("access_flag: 0x%0x\n",cp->access_flags);
			printf("name_index: cp info #%d ",cp->name_index);
			imprime_string_pool(cf->constant_pool, cp->name_index - 1);
    		printf("\n");
			printf("descriptor_index: cp info #%d ",cp->descriptor_index);
			imprime_string_pool(cf->constant_pool, cp->descriptor_index - 1);
    		printf("\n");
			printf("attributes_count: %d\n",cp->attributes_count);

			for(int j = 0; j < cp->attributes_count; j++){
				printf("----Attributes Info----\n");
				printf("attribute_name_index: cp info #%d ",cp->attributes[j].attribute_name_index);
				imprime_string_pool(cf->constant_pool, cp->attributes[j].attribute_name_index - 1);
    			printf("\n");
				printf("attribute_length: %d\n",cp->attributes[j].attribute_length);
				
                int code_length; // sera importante para saber como parar o segundo loop 

                // leitura do bytecode relacionado a informacoes gerais
				for(int k = 0; k < 8; k++)
                {
                    // imprime profundidade maxima do stack
                    if (k == 1) 
                    {
                        int max_stack_depth =  (cp->attributes[j].info[k-1] << 4) + cp->attributes[j].info[k]; 
                        printf("Maximum stack depth: %d\n", max_stack_depth); 
                    }

                    // imprime numero maximo de local variables 
                    if (k == 3)
                    {
                        int max_local_var = (cp->attributes[j].info[k-1] << 4) + cp->attributes[j].info[k]; 
                        printf("Maximum local variables: %d\n", max_local_var);
                    }

                    // imprime tamanho do codigo 
                    if (k == 7)
                    {
                         code_length = 0;
                         code_length += (cp->attributes[j].info[k-3] << 12);
                         code_length += (cp->attributes[j].info[k-2] << 8);
                         code_length += (cp->attributes[j].info[k-1] << 4);
                         code_length += cp->attributes[j].info[k];
                        printf("Code Length: %d\n", code_length);
                    }

                }
               
                // obtem decodificador de instrucoes 
                decodificador dec[NUM_INSTRUCAO];
                inicializa_decodificador(dec); 

                // leitura do bytecode relacionado a instrucoes do metodo 
				for(int k = 8; k-8 < code_length; k++)
                {    
                    // imprime instrucao
                    int indice = cp->attributes[j].info[k];
                    printf("%d: %s  ", k-8, dec[indice].instrucao);


                    // obtem quantos operandos a instrucao tem e vai imprimindo operandos
                    int num_bytes = dec[indice].bytes;
                    for (int l = 0; l < num_bytes; l++)
                    {
                        // atualiza valor de k 
                        k++;

                        // operandos sao impressos do jeito que saem 
                        printf("%d  ", cp->attributes[j].info[k]);
                        if(cp->attributes[j].info[k] != 0)
                        	imprime_string_pool(cf->constant_pool, cp->attributes[j].info[k] - 1);
                    }
                    
                    // pula linha
                    printf("\n"); 
				}
                
				printf("----End Attribute----\n\n");
			}
			i++;
			printf("----End Method----\n\n");
		}
	}

	printf("attributes_count: %d\n",cf->attributes_count);
	if(cf->attributes_count != 0){
		attribute_info* cp = cf->attributes;
		for(int i = 0; i < cf->attributes_count; cp++){
			printf("----Attributes Info----\n");
			printf("attribute_name_index: cp info #%d ",cp->attribute_name_index);
			imprime_string_pool(cf->constant_pool, cp->attribute_name_index - 1);
    		printf("\n");
			printf("attribute_length: %d\n",cp->attribute_length);
			for(int j = 0; j < cp->attribute_length; cp->info++){
				if(*(cp->info) != 0){
					printf("Source file name index: cp info #%d ",*(cp->info));
					imprime_string_pool(cf->constant_pool, *(cp->info) - 1);
			    	printf("\n");
			    }
				j++;
			}
			printf("----End Attributes----\n\n");
			i++;
		}
	}
	printf("----End Second General----\n\n");
}

void imprimePrompt(classFile* cf){
	printf("----General Information----\n");
	printf("CAFEBABE: 0x%0x \n",cf->magic);
	printf("Minor version: %d \n",cf->minor_version);
	printf("Major version: %d \n",cf->major_version);
	printf("Constant Pool Count: %d \n",cf->constant_pool_count);
	printf("----End General----\n\n");

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
			case CONSTANT_Double:
				printf("[%d] CONSTANT_Double_info - high-bytes: 0x%0x\n",i+1,cf->constant_pool[i].info.Double.high_bytes);
				printf("[%d] CONSTANT_Double_info - low-bytes: 0x%0x\n",i+1,cf->constant_pool[i].info.Double.low_bytes);
				break;
			default:
				break;
        }
    }
	printf("----End Pool----\n\n");

	printf("----Second General Info----\n");
	printf("Access Flags: 0x%0x\n",cf->access_flags);
	printf("This Class: cp info #%d ",cf->this_class);
	imprime_string_pool(cf->constant_pool, cf->this_class - 1);
    printf("\n");
	printf("Super Class: cp info #%d ",cf->super_class);
	imprime_string_pool(cf->constant_pool, cf->super_class - 1);
    printf("\n");
	printf("interfaces_count: %d\n",cf->interfaces_count);
	if(cf->interfaces_count != 0){
		printf("---- Interfaces ----\n");
        // le interface, pondo no array de interfaces
        for (int i = 0; i < cf->interfaces_count; i++)
        {
            printf("Interface: cp info #%d ", cf->interfaces[i]);
            imprime_string_pool(cf->constant_pool, cf->interfaces[i] - 1);
    		printf("\n");
        }

    	printf("---- End Interface ----\n");
	}
	printf("Fields Count: %d\n",cf->fields_count);
	if(cf->fields_count != 0){
		printf("----Fields----\n");
        for (int i = 0; i < cf->fields_count; i++)
        {

            // imprime informacoes
            printf("Name: cp info #%d ", cf->fields[i].name_index);
            imprime_string_pool(cf->constant_pool, cf->fields[i].name_index - 1);
    		printf("\n");
            printf("Descriptor: cp info #%d ", cf->fields[i].descriptor_index);
            imprime_string_pool(cf->constant_pool, cf->fields[i].descriptor_index - 1);
    		printf("\n");
            printf("Access Flag: 0x%x\n", cf->fields[i].access_flags);
 
            for (int j = 0; j < cf->fields[i].attributes_count; j++)
            {
                printf("\t\t----Attribute Info do Field----\n");
                
                // imprime informacao dos atributos
                printf("attribute_name_index: cp info #%d\n", cf->fields[i].attributes->attribute_name_index);
                printf("attribute_length: %d\n", cf->fields[i].attributes->attribute_length);

                // imprime bytecode do atributo
                for (int k = 0; k < cf->fields[i].attributes->attribute_length; k++)
                {
                    printf("bytecode: 0x%x\n", cf->fields[i].attributes->info[k]);
                }

                printf("\t\t----Fim da Attribute Info do Field----\n");
            }
        }

        printf("----End Fields----\n");
	}

	printf("Methods Count: %d\n",cf->methods_count);
	if(cf->methods_count != 0){
		method_info* cp = cf->methods;
		for(int i = 0; i < cf->methods_count; cp++){
			printf("----Method Info----\n");
			printf("access_flag: 0x%0x\n",cp->access_flags);
			printf("name_index: cp info #%d ",cp->name_index);
			imprime_string_pool(cf->constant_pool, cp->name_index - 1);
    		printf("\n");
			printf("descriptor_index: cp info #%d ",cp->descriptor_index);
			imprime_string_pool(cf->constant_pool, cp->descriptor_index - 1);
    		printf("\n");
			printf("attributes_count: %d\n",cp->attributes_count);

			for(int j = 0; j < cp->attributes_count; j++){
				printf("----Attributes Info----\n");
				printf("attribute_name_index: cp info #%d ",cp->attributes[j].attribute_name_index);
				imprime_string_pool(cf->constant_pool, cp->attributes[j].attribute_name_index - 1);
    			printf("\n");
				printf("attribute_length: %d\n",cp->attributes[j].attribute_length);
				
                int code_length; // sera importante para saber como parar o segundo loop 

                // leitura do bytecode relacionado a informacoes gerais
				for(int k = 0; k < 8; k++)
                {
                    // imprime profundidade maxima do stack
                    if (k == 1) 
                    {
                        int max_stack_depth =  (cp->attributes[j].info[k-1] << 4) + cp->attributes[j].info[k]; 
                        printf("Maximum stack depth: %d\n", max_stack_depth); 
                    }

                    // imprime numero maximo de local variables 
                    if (k == 3)
                    {
                        int max_local_var = (cp->attributes[j].info[k-1] << 4) + cp->attributes[j].info[k]; 
                        printf("Maximum local variables: %d\n", max_local_var);
                    }

                    // imprime tamanho do codigo 
                    if (k == 7)
                    {
                         code_length = 0;
                         code_length += (cp->attributes[j].info[k-3] << 12);
                         code_length += (cp->attributes[j].info[k-2] << 8);
                         code_length += (cp->attributes[j].info[k-1] << 4);
                         code_length += cp->attributes[j].info[k];
                        printf("Code Length: %d\n", code_length);
                    }

                }
               
                // obtem decodificador de instrucoes 
                decodificador dec[NUM_INSTRUCAO];
                inicializa_decodificador(dec); 

                // leitura do bytecode relacionado a instrucoes do metodo 
				for(int k = 8; k-8 < code_length; k++)
                {    
                    // imprime instrucao
                    int indice = cp->attributes[j].info[k];
                    printf("%d: %s  ", k-8, dec[indice].instrucao);


                    // obtem quantos operandos a instrucao tem e vai imprimindo operandos
                    int num_bytes = dec[indice].bytes;
                    for (int l = 0; l < num_bytes; l++)
                    {
                        // atualiza valor de k 
                        k++;

                        // operandos sao impressos do jeito que saem 
                        printf("%d  ", cp->attributes[j].info[k]);
                        if(cp->attributes[j].info[k] != 0)
                        	imprime_string_pool(cf->constant_pool, cp->attributes[j].info[k] - 1);
                    }
                    
                    // pula linha
                    printf("\n"); 
				}
                
				printf("----End Attribute----\n\n");
			}
			i++;
			printf("----End Method----\n\n");
		}
	}

	printf("attributes_count: %d\n",cf->attributes_count);
	if(cf->attributes_count != 0){
		attribute_info* cp = cf->attributes;
		for(int i = 0; i < cf->attributes_count; cp++){
			printf("----Attributes Info----\n");
			printf("attribute_name_index: cp info #%d ",cp->attribute_name_index);
			imprime_string_pool(cf->constant_pool, cp->attribute_name_index - 1);
    		printf("\n");
			printf("attribute_length: %d\n",cp->attribute_length);
			for(int j = 0; j < cp->attribute_length; cp->info++){
				if(*(cp->info) != 0){
					printf("Source file name index: cp info #%d ",*(cp->info));
					imprime_string_pool(cf->constant_pool, *(cp->info) - 1);
			    	printf("\n");
			    }
				j++;
			}
			printf("----End Attributes----\n\n");
			i++;
		}
	}
	printf("----End Second General----\n\n");
}
