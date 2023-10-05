#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/assembler.h"
#include "../../Input_to_buf/include/input.h"

void assembly(struct Text* text)
{
    FILE* fp = fopen("../../Assembler.txt", "w");
    int counter = 0;
    while(counter < text->n_lines)
    {
        int command_val = read_command_func(text, counter);

        if(command_val == PUSH)
        {
            int val = 0;
            fprintf(fp, "%d ", PUSH);
            sscanf(text->adress_of_str_parameters[counter].ptr2str + strlen("push"), "%d", &val);
            fprintf(fp, "%d\n", val);
        }
        if(command_val == HLT)
        {
            fprintf(fp, "%d\n", HLT);
        }
        if(command_val == ADD)
        {
            fprintf(fp, "%d\n", ADD);
        }
        if(command_val == SUB)
        {
            fprintf(fp, "%d\n", SUB);
        }
        if(command_val == MUL)
        {
            fprintf(fp, "%d\n", MUL);
        }
        if(command_val == DIV)
        {
            fprintf(fp, "%d\n", DIV);
        }
        if(command_val == SQRT)
        {
            fprintf(fp, "%d\n", SQRT);
        }
        if(command_val == SIN)
        {
            fprintf(fp, "%d\n", SIN);
        }
        if(command_val == COS)
        {
            fprintf(fp, "%d\n", COS);
        }
        if(command_val == IN)
        {
            fprintf(fp, "%d\n", IN);
        }
        if(command_val == OUT)
        {
            fprintf(fp, "%d\n", OUT);
        }
        if(command_val == ERR)
        {
            fprintf(fp, "%d\n", ERR);
        }
        counter++;
    }



}

int read_command_func(struct Text* text, int counter)
{
    char buffer[20] = {};

    sscanf(text->adress_of_str_parameters[counter].ptr2str, "%s", buffer);

    if(!strcmp(buffer, "push"))
        return PUSH;

    else if(!strcmp(buffer, "add"))
        return ADD;

    else if(!strcmp(buffer, "sub"))
        return SUB;

    else if(!strcmp(buffer, "mul"))
        return MUL;

    else if(!strcmp(buffer, "div"))
        return DIV;

    else if(!strcmp(buffer, "sqrt"))
        return SQRT;

    else if(!strcmp(buffer, "sin"))
        return SIN;

    else if(!strcmp(buffer, "cos"))
        return COS;

    else if(!strcmp(buffer, "in"))
        return IN;

    else if(!strcmp(buffer, "out"))
        return OUT;

    else if(!strcmp(buffer, "HLT"))
        return HLT;

    else
        return ERR;
}
