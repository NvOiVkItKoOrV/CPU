#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "../../Input_to_buf/include/input.h"
#include "stack.h"

enum commands
{
    ERR = -1,
    HLT  = 0,

    PUSH  =  1,
    RPUSH = 65,

    POP = 2,
    IN  = 3,
    OUT = 4,

    ADD = 5,
    SUB = 6,
    MUL = 7,
    DIV = 8,

    SIN  = 9,
    COS  = 12,
    SQRT = 11,
    JMP = 13
};

enum registers
{
    REG_A = 0,
    REG_B = 1,
    REG_C = 2,
    REG_D = 3
};

struct processor_t
{
    elem_t rax = 0;
    elem_t rbx = 0;
    elem_t rcx = 0;
    elem_t rdx = 0;
    struct stack_t stk;
    struct Text text;

};

void proc_ctor(struct processor_t* proc);
void proc_dtor(struct processor_t* proc);

void virtual_machine(struct processor_t* proc);

int read_command_func(struct processor_t* proc, size_t* counter);

void push_func(struct processor_t* proc, int push_type, size_t* counter);
void pop_func (struct processor_t* proc, size_t* counter);

void add_func (struct processor_t* proc);
void sub_func (struct processor_t* proc);
void mul_func (struct processor_t* proc);
void div_func (struct processor_t* proc);
void in_func  (struct processor_t* proc);
void out_func (struct processor_t* proc);
void sqrt_func(struct processor_t* proc);
void sin_func (struct processor_t* proc);
void cos_func (struct processor_t* proc);
void jmp_func(struct processor_t* proc, size_t* counter);

#endif /* PROCESSOR_H */
