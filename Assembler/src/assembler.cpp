#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/assembler.h"
#include "../../Processor/include/stack.h"
#include "../../Input_to_buf/include/input.h"

//make 2-nd buf for numbers, and work with it. Finally fprintf the result to file

void assembler(struct Text* text)
{
    assert(text);

    FILE* file_adress = fopen("../Assembler.txt", "w");
    assert(text);

    size_t buf_size = text->n_lines * 20;
    char* bin_buf = (char*)calloc(buf_size, sizeof(char));
    assert(bin_buf);

    char* buf_ptr2end = bin_buf;

    size_t counter = 0;

    while(counter < text->n_lines)
    {
        int command_val = read_command_func(text, counter);

        if(command_val == PUSH)
        {
            int val = 0;
            sscanf(text->adress_of_str_parameters[counter].ptr2str + sizeof("push"), "%d", &val);

            *(buf_ptr2end) = PUSH;
              buf_ptr2end += sizeof(char);

            memcpy(buf_ptr2end, &val, sizeof(elem_t));
            buf_ptr2end += sizeof(elem_t);
        }
        else if(command_val == RPUSH)
        {

            char reg_type[20] = {};

            sscanf(text->adress_of_str_parameters[counter].ptr2str + sizeof("push"), "%s", reg_type);

            int reg_code = reg_type[1] - 'a';
            printf("%d", reg_code);
                switch(reg_code)
                {
                case REG_A:
                {
                    *(buf_ptr2end) = RPUSH;
                    buf_ptr2end +=sizeof(char);

                    *(buf_ptr2end) = REG_A;
                    buf_ptr2end +=sizeof(char);
                    break;
                }
                case REG_B:
                {
                    *(buf_ptr2end) = RPUSH;
                    buf_ptr2end +=sizeof(char);

                    *(buf_ptr2end) = REG_B;
                    buf_ptr2end +=sizeof(char);
                    break;
                }
                case REG_C:
                {
                    *(buf_ptr2end) = RPUSH;
                    buf_ptr2end +=sizeof(char);

                    *(buf_ptr2end) = REG_C;
                    buf_ptr2end +=sizeof(char);
                    break;
                }
                case REG_D:
                {
                    *(buf_ptr2end) = RPUSH;
                    buf_ptr2end +=sizeof(char);

                    *(buf_ptr2end) = REG_D;
                    buf_ptr2end +=sizeof(char);
                    break;
                }
                default:
                    printf("This register type doesn't exist on %lu line", counter);
                    break;
                }
        }
        else if(command_val == POP)
        {
            char reg_type[20] = {};
            sscanf(text->adress_of_str_parameters[counter].ptr2str + strlen("pop"), "%s", reg_type);

            int reg_code = reg_type[1] - 'a';

                switch(reg_code)
                {
                case REG_A:
                    *(buf_ptr2end) = POP;
                    buf_ptr2end +=sizeof(char);

                    *(buf_ptr2end) = REG_A;
                    buf_ptr2end +=sizeof(char);
                    break;

                case REG_B:
                    *(buf_ptr2end) = POP;
                    buf_ptr2end +=sizeof(char);

                    *(buf_ptr2end) = REG_B;
                    buf_ptr2end +=sizeof(char);
                    break;

                case REG_C:
                    *(buf_ptr2end) = POP;
                    buf_ptr2end +=sizeof(char);

                    *(buf_ptr2end) = REG_C;
                    buf_ptr2end +=sizeof(char);
                    break;

                case REG_D:
                    *(buf_ptr2end) = POP;
                    buf_ptr2end +=sizeof(char);

                    *(buf_ptr2end) = REG_D;
                    buf_ptr2end +=sizeof(char);
                    break;

                default:
                    printf("This register type doesn't exist on %lu line", counter);
                    break;
                }
        }
        else if(command_val == ERR)
        {
            printf("Syntax error is assemler, %lu line", counter);
            exit(0);
        }
        else
        {
            *(buf_ptr2end) = command_val;
              buf_ptr2end +=sizeof(char);
        }
        counter++;
    }

    for(int i = 0; i < buf_size; i++)
        printf("%d ", *(bin_buf + i));


    fwrite(bin_buf, sizeof(char), buf_size, file_adress);
    free(bin_buf);
}


int read_command_func(struct Text* text, size_t counter)
{
    assert(text);

    char buffer[20] = {};
    sscanf(text->adress_of_str_parameters[counter].ptr2str, "%s", buffer);

    assert(buffer);

    if(!strcmp(buffer, "push"))
    {
        char push_val[20] = {};

        sscanf(text->adress_of_str_parameters[counter].ptr2str + strlen("push"), "%s", push_val);

        if(strlen(push_val) == 3 && push_val[0] == 'r' && push_val[2] == 'x')
            return RPUSH;

        else
            return PUSH;
    }
    else if(!strcmp(buffer, "pop"))
    {
        char pop_val[10] = {};
        sscanf(text->adress_of_str_parameters[counter].ptr2str + strlen("pop"), "%s", pop_val);

        if(strlen(pop_val) == 3 && pop_val[0] == 'r' && pop_val[2] == 'x')
            return POP;

    }
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
