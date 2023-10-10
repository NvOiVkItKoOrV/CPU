#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

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

void disassembly(struct Text* text);
int read_command_func(struct Text* text, int counter);

#endif /* DISASSEMBLER_H */
