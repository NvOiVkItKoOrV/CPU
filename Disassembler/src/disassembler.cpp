#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/disassembler.h" // -I ../include
#include "../../Input_to_buf/include/input.h"

void disassembler(struct Text* text)
{
    FILE* fp = fopen("Disassembler.txt", "w");
    int counter = 0;
    while(counter < text->n_lines)
    {
        int command_val = read_command_func(text, counter);

        if(command_val == PUSH)
        {
            int command;
            int val = 0;
            fprintf(fp, "push ");
            sscanf(text->adress_of_str_parameters[counter].ptr2str, "%d %d",&command, &val);
            fprintf(fp, "%d\n", val);
        }
        if(command_val == HLT)
        {
            fprintf(fp, "HLT\n");
        }
        if(command_val == ADD)
        {
            fprintf(fp, "add\n");
        }
        if(command_val == SUB)
        {
            fprintf(fp, "sub\n");
        }
        if(command_val == MUL)
        {
            fprintf(fp, "mul\n");
        }
        if(command_val == DIV)
        {
            fprintf(fp, "div\n");
        }
        if(command_val == SQRT)
        {
            fprintf(fp, "sqrt\n");
        }
        if(command_val == SIN)
        {
            fprintf(fp, "sin\n");
        }
        if(command_val == COS)
        {
            fprintf(fp, "%d\n");
        }
        if(command_val == IN)
        {
            fprintf(fp, "cos\n");
        }
        if(command_val == OUT)
        {
            fprintf(fp, "out\n", OUT);
        }
        if(command_val == ERR)
        {
            fprintf(fp, "ERROR!!!\n");
        }
        counter++;
    }
}


int read_command_func(struct Text* text, int counter)
{
    int com_val;

    sscanf(text->adress_of_str_parameters[counter].ptr2str, "%d", &com_val);

    if(com_val == PUSH)
        return PUSH;

    else if(com_val == ADD)
        return ADD;

    else if(com_val == SUB)
        return SUB;

    else if(com_val == MUL)
        return MUL;

    else if(com_val == DIV)
        return DIV;

    else if(com_val == SQRT)
        return SQRT;

    else if(com_val == SIN)
        return SIN;

    else if(com_val == COS)
        return COS;

    else if(com_val == IN)
        return IN;

    else if(com_val == OUT)
        return OUT;

    else if(com_val == HLT)
        return HLT;

    else
        return ERR;
}
