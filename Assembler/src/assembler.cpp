#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../Input_to_buf/include/input.h"
#include "../include/assembler.h"
#include "../include/labels.h"
#include "../../Processor/include/stack.h"

void assembler(struct Text* text)
{
    assert(text);

    FILE* file_adress = fopen("../Assembler.txt", "w");
    assert(text);

    size_t buf_size = text->n_lines * 30;
    char* bin_buf = (char*)calloc(buf_size, sizeof(char));
    assert(bin_buf);

    char* buf_ptr2end = bin_buf;
    size_t counter = 0;

    label_t* adr_of_lab_array = array_of_labels_ctor();
    size_t labels_counter = 0;

    while(counter < text->n_lines)
    {
        int command_val = read_command_func(text, counter, bin_buf, buf_ptr2end, adr_of_lab_array, &labels_counter);

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

            reg_func(reg_code, &buf_ptr2end, counter, command_val);
        }
        else if(command_val == POP)
        {
            char reg_type[20] = {};
            sscanf(text->adress_of_str_parameters[counter].ptr2str + strlen("pop"), "%s", reg_type);

            int reg_code = reg_type[1] - 'a';

            reg_func(reg_code, &buf_ptr2end, counter, command_val);
        }
        else if(command_val == JMP)
        {
            char label_name[20] = {};
            sscanf(text->adress_of_str_parameters[counter].ptr2str + sizeof("jmp"), "%s", label_name);

            int lab_adr_checker = lab_name_exists_check(adr_of_lab_array, label_name);

            if(lab_adr_checker == incorrect_adress)
            {
                strcat(adr_of_lab_array[labels_counter].lab_name, label_name);
                adr_of_lab_array[labels_counter].sourse_adresses[0] = buf_ptr2end - bin_buf;
                //printf("%d", adr_of_lab_array[labels_counter].sourse_adresses[0]);
                adr_of_lab_array[labels_counter].srs_adr_counter++;
                labels_counter++;
            }
            else
            {
                int srs_counter = adr_of_lab_array[lab_adr_checker].srs_adr_counter;

                if(srs_counter == max_sourse_adresses_array_length - 1)
                    printf("Array of sourse adresses is overflow in line: %lu \n", counter);

                int index = buf_ptr2end - bin_buf;

                adr_of_lab_array[lab_adr_checker].sourse_adresses[srs_counter] = index;
                adr_of_lab_array[lab_adr_checker].srs_adr_counter++;


            }

            *(buf_ptr2end) = JMP;
            buf_ptr2end += sizeof(char);
            buf_ptr2end += sizeof(int);

        }
        else if(command_val == ERR)
        {
            printf("Syntax error is assemler, %lu line", counter);
            exit(0);
        }
        else if(command_val == LAB || command_val == COM)
        {}
        else
        {
            *(buf_ptr2end) = command_val;
              buf_ptr2end +=sizeof(char);
        }
        counter++;
    }

    //put jump values to binary buffer
    fill_adresses2jump(text, bin_buf, buf_size, adr_of_lab_array);

    for(int i = 0; i < buf_size; i++)
        printf("%u ", *(bin_buf + i));

    array_of_labels_dtor(adr_of_lab_array);
    fwrite(bin_buf, sizeof(char), buf_size, file_adress);
    free(bin_buf);
}


int read_command_func(struct Text* text, size_t counter, char* bin_buf, char* buf_ptr2end, label_t* adr_of_lab_array, size_t* labels_counter)
{
    assert(text);
    assert(labels_counter);

    char buffer[20] = {};
    sscanf(text->adress_of_str_parameters[counter].ptr2str, "%s", buffer);
    assert(buffer);

    if(text->adress_of_str_parameters[counter].ptr2str[0] == ';')
    {
        return COM;
    }
    else if(buffer[strlen(buffer) - 1] == ':')   //strchr
    {
        buffer[strlen(buffer) - 1] = '\0';

        int lab_adress = lab_name_exists_check(adr_of_lab_array, buffer);

        if(lab_adress == incorrect_adress)
        {
            lab_adress = *labels_counter;
            strcpy(adr_of_lab_array[*labels_counter].lab_name, buffer);
            (*labels_counter)++;

            printf("counter %d\n", lab_adress);
            adr_of_lab_array[lab_adress].destination_adress = buf_ptr2end - bin_buf;
        }
        else
        {
            printf("debug\n");
            if(adr_of_lab_array[lab_adress].destination_adress == incorrect_adress)
            {
                printf("Debug Addres %d\n", buf_ptr2end - bin_buf);
                adr_of_lab_array[lab_adress].destination_adress = buf_ptr2end - bin_buf;
            }
            else
            {
                printf("Error in %lu line! This label: <%s> already exist!!!\n", counter, buffer);
                abort();
            }
        }
        return LAB;
    }
    else
    {
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

        else if(!strcmp(buffer, "jmp"))
            return JMP;

        else if(!strcmp(buffer, "HLT"))
            return HLT;

        else
            return ERR;
    }
}


void reg_func(int reg_code, char** buf_ptr2end, size_t counter, int command)
{
                switch(reg_code)
                {
                case REG_A:
                    **buf_ptr2end = (char)command;
                    *buf_ptr2end +=sizeof(char);

                    **buf_ptr2end = REG_A;
                    *buf_ptr2end +=sizeof(char);
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
                    printf("This register type doesn't exist on %lu line", counter);
                    break;
                }
}
