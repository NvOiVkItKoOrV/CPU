#ifndef ASSEMBLER_H
#define ASSEMBLER_H


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
    COS  = 10,
    SQRT = 11
};

enum registers
{
    REG_A = 0,
    REG_B = 1,
    REG_C = 2,
    REG_D = 3
};


void assembler(struct Text* text);
int read_command_func(struct Text* text, size_t counter);

#endif /* ASSEMBLER_H */
