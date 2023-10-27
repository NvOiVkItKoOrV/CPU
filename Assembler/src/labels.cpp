#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/labels.h"
#include "../include/assembler.h"
#include "../../Processor/include/stack.h"

label_t* array_of_labels_ctor()
{
    label_t* array_of_lab = (label_t*) calloc(max_lab_array_sz, sizeof(label_t));

    for(int lab_counter = 0; lab_counter < max_lab_array_sz; lab_counter++)
    {
        array_of_lab[lab_counter].destination_adress = incorrect_adress;
        array_of_lab[lab_counter].src_adr_counter    = 0;

        for(int source_counter = 0; source_counter < max_source_adresses_array_length; source_counter++)
        {
            array_of_lab[lab_counter].source_adresses[source_counter] = incorrect_adress;
        }
    }

    return array_of_lab;
}


void array_of_labels_dtor(label_t* array_of_lab)
{
    assert(array_of_lab);
    free(array_of_lab);
}


int lab_name_exists(label_t* array_of_lab, char* new_lab_name)
{
    for(int lab_counter = 0; lab_counter < max_lab_array_sz; lab_counter++)
    {
       //printf("%d %d %s\n", lab_counter, array_of_lab[lab_counter].destination_adress, array_of_lab[lab_counter].lab_name);
       if(!strcmp(array_of_lab[lab_counter].lab_name, new_lab_name))
           return lab_counter;
    }
    return incorrect_adress;
}


void fill_adresses2jump(struct Text* text, char* bin_buf, size_t bin_buf_size, label_t* adr_of_lab_array)
{

    for(size_t bin_buf_counter = 0; bin_buf_counter < bin_buf_size;)
    {

        switch(bin_buf[bin_buf_counter])
        {
        case PUSH:
        {
            bin_buf_counter += sizeof(char);
            bin_buf_counter += sizeof(elem_t);
            break;
        }
        case RPUSH:
        case POP:
        {
            bin_buf_counter += sizeof(char);
            bin_buf_counter += sizeof(char);
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
            for(size_t lines_counter = 0; lines_counter < text->n_lines; lines_counter++)
            {
                char buffer[max_lab_name_length] = {};

                //printf("%s\n", text->adress_of_str_parameters[lines_counter].ptr2str);

                sscanf(text->adress_of_str_parameters[lines_counter].ptr2str,"%s",buffer);
                if(!strcmp(buffer, "ja")  || !strcmp(buffer, "jae") || !strcmp(buffer, "jb") || !strcmp(buffer, "jmp") ||
                   !strcmp(buffer, "jbe") || !strcmp(buffer, "je") || !strcmp(buffer, "jne") || !strcmp(buffer, "call") )
                {
                    sscanf(text->adress_of_str_parameters[lines_counter].ptr2str + strlen(buffer),"%s",buffer);

                    int adress = lab_name_exists(adr_of_lab_array, buffer);

                    if(adress < 0 || adress > max_lab_array_sz)
                    {
                        printf("This label <%s> doesnt exist!!!", buffer);
                        abort();
                    }
                    else
                    {
                        bin_buf_counter += sizeof(char);
                        *((int*)(bin_buf + bin_buf_counter)) = adr_of_lab_array[adress].destination_adress;
                        bin_buf_counter += sizeof(int);
                        break;

                    }
                }
            }
            break;
        }
        default:
        {
            bin_buf_counter += sizeof(char);
            break;
        }
        }
    }
}
