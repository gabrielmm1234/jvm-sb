
void criaFrame();

struct frame
{
    uint32_t* fields;
    cp_info* constant_pool;
    classFile* classe;
    uint16_t max_stack;
    uint32_t max_locals;
    uint32_t code_length;
    uint8_t* code;
    uint32_t pc;
};

struct stackFrame 
{
    struct frame* refFrame;
    struct stackFrame* next; 
};
#include "frame.c"
