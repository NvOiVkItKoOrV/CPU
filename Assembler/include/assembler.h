#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include"../../Input_to_buf/include/input.h"
#include "labels.h"

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
    JMP = 13,
    LAB = 14,
    COM = 15
};

enum registers
{
    REG_A = 0,
    REG_B = 1,
    REG_C = 2,
    REG_D = 3
};


void assembler(struct Text* text);
int read_command_func(struct Text* text, size_t counter, char* bin_buf, char* buf_ptr2end, label_t* adr_of_lab_array, size_t* labels_counter);
void reg_func(int reg_code, char** buf_ptr2end, size_t counter, int command);
#endif /* ASSEMBLER_H */
