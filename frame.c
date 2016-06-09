/*
* Software Basico - 1/2016
* Arquivo que contém funções que manipulam os frames criados
* e a stack de frames.
*/

//Topo da pilha de frames.
static struct stackFrame* topo = NULL;

//Cria uma estrutura de frame e coloca na pilha. Precisa dos bytecodes
//de uma referencia a constantPool e da classe que contém o método.
void criaFrame(cp_info* cp, classFile* classe, code_attribute* code){
	printf("Criando Frame.\n");

	//Aloca espaço para o frame.
	struct stackFrame* sf;
	sf = malloc(sizeof(struct stackFrame));
	sf->refFrame = malloc(sizeof(struct frame));

	//Atualizando o topo da pilha.
	sf->next = topo;
	topo = sf;

	//Preenche a estrutura com as informações do frame.
	sf->refFrame->classe = classe;
	sf->refFrame->constant_pool = cp;
	sf->refFrame->max_locals = code->max_locals;
	sf->refFrame->max_stack = code->max_stack;
	sf->refFrame->code_length = code->code_length;

	//Bytecodes.
	sf->refFrame->code = code->code;

	//pc começa na primeira instrução.
	sf->refFrame->pc = 0;
	
	//Aloca espaço para o fields do método. Max_locals -> máximo de fields.
	//Vetor de variáveis locais.
	sf->refFrame->fields = malloc(code->max_locals * sizeof(uint32_t));

	//Atualiza o frame corrente. Será o frame em execução no momento.
	frameCorrente = sf->refFrame;

	//TODO criar pilha de operandos.
}
