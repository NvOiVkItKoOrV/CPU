#ifndef PROCESSOR_H
#define PROCESSOR_H
enum commands
{
    ERR  = -2,
    HLT  = -1,
    PUSH =  0,
    ADD  =  1,
    SUB  =  2,
    MUL  =  3,
    DIV  =  4,
    SQRT =  5,
    SIN  =  6,
    COS  =  7,
    IN   =  8,
    OUT  =  9
};

void virtual_machine(struct Text* text, struct stack_t* stk);

int read_command_func(struct Text* text, int counter);

void push_func(struct Text* text, struct stack_t* stk, int counter);
void add_func (struct stack_t* stk);
void sub_func (struct stack_t* stk);
void mul_func (struct stack_t* stk);
void div_func (struct stack_t* stk);
void in_func  (struct stack_t* stk);
void out_func (struct stack_t* stk);

#endif /* PROCESSOR_H */
