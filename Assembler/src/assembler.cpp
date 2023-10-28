#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../Input_to_buf/include/input.h"
#include "../../Processor/include/stack.h"
#include "../include/assembler.h"
#include "../include/labels.h"


void assembler(struct Text* text)
{
    assert(text);

    FILE* file_adress = fopen("../Assembler.txt", "w");
    assert(text);

    size_t buf_size = text->n_lines * SIZE_OF_BUF;
    char* bin_buf = (char*)calloc(buf_size, sizeof(char));

    char* buf_ptr2end = bin_buf;
    size_t counter = 0;
    int cmd_name_length = 0;

    label_t* adr_of_lab_array = array_of_labels_ctor();
    size_t labels_counter = 0;

    while(counter < text->n_lines)
    {
        int command_val = read_command_func(text, counter, bin_buf, buf_ptr2end, adr_of_lab_array, &labels_counter, &cmd_name_length);

        switch(command_val)
        {
        case PUSH:
        {
            elem_t val = 0;
            sscanf(text->adress_of_str_parameters[counter].ptr2str + cmd_name_length, "%d", &val);

            *(buf_ptr2end) = PUSH;
              buf_ptr2end += sizeof(char);

            memcpy(buf_ptr2end, &val, sizeof(elem_t));
            buf_ptr2end += sizeof(elem_t);
            break;
        }
        case RPUSH:
        {

            char reg_type[SIZE_OF_BUF] = {};

            sscanf(text->adress_of_str_parameters[counter].ptr2str + cmd_name_length, "%s", reg_type);

            int reg_code = reg_type[1] - 'a';
            reg_func(reg_code, &buf_ptr2end, counter, command_val);
            break;
        }
        case POP:
        {
            char reg_type[SIZE_OF_BUF] = {};
            sscanf(text->adress_of_str_parameters[counter].ptr2str + cmd_name_length, "%s", reg_type);

            int reg_code = reg_type[1] - 'a';
            reg_func(reg_code, &buf_ptr2end, counter, command_val);
            break;
        }
        case JMP:
        case JA:
        case JAE:
        case JB:
        case JBE:
        case JE:
        case JNE:
        case CALL:
        {
            char label_name[SIZE_OF_BUF] = {};
            sscanf(text->adress_of_str_parameters[counter].ptr2str + cmd_name_length, "%s", label_name);

            int lab_adr_checker = lab_name_exists(adr_of_lab_array, label_name);

            if(lab_adr_checker == incorrect_adress)
            {
                strcat(adr_of_lab_array[labels_counter].lab_name, label_name);//strcpy
                adr_of_lab_array[labels_counter].source_adresses[0] = (buf_ptr2end - bin_buf)/sizeof(char);

                adr_of_lab_array[labels_counter].src_adr_counter++;
                labels_counter++;
            }
            else
            {
                int src_counter = adr_of_lab_array[lab_adr_checker].src_adr_counter;

                if(src_counter == max_source_adresses_array_length - 1)
                    printf("Array of source adresses is overflow in line: %d \n", counter);

                int index = (buf_ptr2end - bin_buf)/sizeof(char);

                adr_of_lab_array[lab_adr_checker].source_adresses[src_counter] = index;
                adr_of_lab_array[lab_adr_checker].src_adr_counter++;


            }

          *(buf_ptr2end) = (char)command_val;
            buf_ptr2end += sizeof(char);
            buf_ptr2end += sizeof(int);
            break;
        }
        case ERR:
        {
            printf("Syntax error is assemler, %lu line", counter);
            exit(0);
            break;
        }
        case COMMENT:
        case LAB:
        {
            break;
        }
        default:
        {
            *(buf_ptr2end) =(char)command_val;
              buf_ptr2end +=sizeof(char);
              break;
        }
        }
        counter++;
    }

    fill_adresses2jump(text, bin_buf, buf_size, adr_of_lab_array);

    array_of_labels_dtor(adr_of_lab_array);

    fwrite(bin_buf, sizeof(char), buf_size, file_adress);
    free(bin_buf);
    fclose(file_adress);

}


int read_command_func(struct Text* text, size_t counter,            char* bin_buf,          char* buf_ptr2end,
                                         label_t* adr_of_lab_array, size_t* labels_counter, int* cmd_name_length)
{
    assert(text);
    assert(labels_counter);

    char buffer[SIZE_OF_BUF] = {};
    sscanf(text->adress_of_str_parameters[counter].ptr2str, "%s", buffer);

    if(buffer[0] == ';')
    {
        return COMMENT;
    }
    else if(buffer[strlen(buffer) - 1] == ':')
    {
        make_or_check_label(text, counter, bin_buf, buf_ptr2end, buffer, adr_of_lab_array, labels_counter, cmd_name_length);
        return LAB;
    }
    else
    {
        if(!strcmp(buffer, "push"))
        {
            *cmd_name_length = sizeof("push");

            char push_val[SIZE_OF_BUF] = {};

            sscanf(text->adress_of_str_parameters[counter].ptr2str + *cmd_name_length, "%s", push_val);

            if(push_val[0] == 'r' && push_val[2] == 'x' && strlen(push_val) == 3)
                return RPUSH;

            else
                return PUSH;
        }
        else if(!strcmp(buffer, "pop"))
        {
            *cmd_name_length = sizeof("pop");

            char pop_val[SIZE_OF_BUF] = {};
            sscanf(text->adress_of_str_parameters[counter].ptr2str + *cmd_name_length, "%s", pop_val);

            if(pop_val[0] == 'r' && pop_val[2] == 'x' && strlen(pop_val) == strlen("r_x"))
                return POP;
            else
            {
                printf("Wrong register in %d line!\n", counter);
                return ERR;
            }
        }
        else if(!strcmp(buffer, "add"))
        {
            *cmd_name_length = sizeof("add");
            return ADD;
        }

        else if(!strcmp(buffer, "sub"))
        {
            *cmd_name_length = sizeof("sub");
            return SUB;
        }

        else if(!strcmp(buffer, "mul"))
        {
            *cmd_name_length = sizeof("mul");
            return MUL;
        }

        else if(!strcmp(buffer, "div"))
        {
            *cmd_name_length = sizeof("div");
            return DIV;
        }

        else if(!strcmp(buffer, "sqrt"))
        {
            *cmd_name_length = sizeof("sqrt");
            return SQRT;
        }

        else if(!strcmp(buffer, "sin"))
        {
            *cmd_name_length = sizeof("sin");
            return SIN;
        }

        else if(!strcmp(buffer, "cos"))
        {
            *cmd_name_length = sizeof("cos");
            return COS;
        }

        else if(!strcmp(buffer, "in"))
        {
            *cmd_name_length = sizeof("in");
            return IN;
        }

        else if(!strcmp(buffer, "out"))
        {
            *cmd_name_length = sizeof("out");
            return OUT;
        }

        else if(!strcmp(buffer, "jmp"))
        {
            *cmd_name_length = sizeof("jmp");
            return JMP;
        }
        else if(!strcmp(buffer, "HLT"))
        {
            *cmd_name_length = sizeof("HLT");
            return HLT;
        }

        else if(!strcmp(buffer, "ja"))
        {
            *cmd_name_length = sizeof("ja");
            return JA;
        }

        else if(!strcmp(buffer, "jae"))
        {
            *cmd_name_length = sizeof("jae");
            return JAE;
        }

        else if(!strcmp(buffer, "jb"))
        {
            *cmd_name_length = sizeof("jb");
            return JB;
        }

        else if(!strcmp(buffer, "jbe"))
        {
            *cmd_name_length = sizeof("jbe");
            return JBE;
        }

        else if(!strcmp(buffer, "je"))
        {
            *cmd_name_length = sizeof("je");
            return JE;
        }

        else if(!strcmp(buffer, "jne"))
        {
            *cmd_name_length = sizeof("jne");
            return JNE;
        }
        else if(!strcmp(buffer, "call"))
        {
            *cmd_name_length = sizeof("call");
            return CALL;
        }
        else if(!strcmp(buffer, "ret"))
        {
            *cmd_name_length = sizeof("ret");
            return RET;
        }
        else
            return ERR;
    }
}


void reg_func(int reg_code, char** buf_ptr2end,size_t counter, int command)
{
    switch(reg_code)
    {
    case REG_A:
        **buf_ptr2end  = (char)command;
            *buf_ptr2end += sizeof(char);

        **buf_ptr2end = REG_A;
            *buf_ptr2end += sizeof(char);
        break;

    case REG_B:
        **buf_ptr2end = (char)command;
            *buf_ptr2end +=sizeof(char);

        **buf_ptr2end = REG_B;
            *buf_ptr2end +=sizeof(char);
        break;

    case REG_C:
        **buf_ptr2end = (char)command;
            *buf_ptr2end +=sizeof(char);

        **buf_ptr2end = (char)REG_C;
            *buf_ptr2end +=sizeof(char);
        break;

    case REG_D:
        **buf_ptr2end = (char)command;
            *buf_ptr2end +=sizeof(char);

        **buf_ptr2end = REG_D;
            *buf_ptr2end +=sizeof(char);
        break;

    default:
        printf("This register type doesn't exist on %d line", counter);
        break;
    }
}

void make_or_check_label(struct Text* text, size_t counter,            char* bin_buf,          char* buf_ptr2end,
                         char* buffer,      label_t* adr_of_lab_array, size_t* labels_counter, int* cmd_name_length)
{
        buffer[strlen(buffer) - 1] = '\0';

        int lab_adress = lab_name_exists(adr_of_lab_array, buffer);

        if(lab_adress == incorrect_adress)
        {
            strcpy(adr_of_lab_array[*labels_counter].lab_name, buffer);

            adr_of_lab_array[*labels_counter].destination_adress = buf_ptr2end - bin_buf;
            printf("Debug %d address %d\n", *labels_counter, adr_of_lab_array[*labels_counter].destination_adress);
            (*labels_counter)++;
        }
        else
        {
            if(adr_of_lab_array[lab_adress].destination_adress == incorrect_adress)
            {
                adr_of_lab_array[lab_adress].destination_adress = (buf_ptr2end - bin_buf)/sizeof(char);
            }
            else
            {
                printf("Error in %lu line! This label: <%s> already exist!!!\n", counter, buffer);
                abort();
            }
        }
}
