#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/labels.h"
#include "../include/assembler.h"

label_t* array_of_labels_ctor()
{
    label_t* array_of_lab = (label_t*) calloc(max_lab_array_sz, sizeof(label_t));

    for(int lab_counter = 0; lab_counter < max_lab_array_sz; lab_counter++)
        {
            array_of_lab[lab_counter].destination_adress = incorrect_adress;
            array_of_lab[lab_counter].srs_adr_counter    = 0;

            for(int sourse_counter = 0; sourse_counter < max_sourse_adresses_array_length; sourse_counter++)
            {
                array_of_lab[lab_counter].sourse_adresses[sourse_counter] = incorrect_adress;
            }
        }

    return array_of_lab;
}


void array_of_labels_dtor(label_t* array_of_lab)
{
    free(array_of_lab);
}


int lab_name_exists_check(label_t* array_of_lab, char* new_lab_name)
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
        if(bin_buf[bin_buf_counter] == PUSH)
        {
            bin_buf_counter += sizeof(char);
            bin_buf_counter += sizeof(int);
        }
        else if(bin_buf[bin_buf_counter] == RPUSH || bin_buf[bin_buf_counter] == POP)
        {
            bin_buf_counter += sizeof(char);
            bin_buf_counter += sizeof(char);
        }
        else if(bin_buf[bin_buf_counter] == JMP)
        {
            size_t lines_counter = 0;
            for(; lines_counter < text->n_lines; lines_counter++)
            {

                char buffer[max_lab_name_length] = {};

                //printf("%s\n", text->adress_of_str_parameters[lines_counter].ptr2str);

                sscanf(text->adress_of_str_parameters[lines_counter].ptr2str,"%s",buffer);
                if(!strcmp(buffer, "jmp"))
                {
                    sscanf(text->adress_of_str_parameters[lines_counter].ptr2str + sizeof("jmp"),"%s",buffer);
                    int adress = lab_name_exists_check(adr_of_lab_array, buffer);
                    if(adress < 0 || adress > max_lab_array_sz)
                    {
                        printf("This label <%s> doesnt exist!!!", buffer);
                        abort();
                    }
                    else
                    {
printf("%d - binary buffer counter\n", bin_buf_counter);
                        bin_buf_counter += sizeof(char);
printf("%d - binary buffer counter1\n", bin_buf_counter);
printf("%d - binary3buffer\n", *((int*)(bin_buf + bin_buf_counter)));
printf("%u - destination adress\n", adr_of_lab_array[adress].destination_adress);
                        *((int*)(bin_buf + bin_buf_counter)) = adr_of_lab_array[adress].destination_adress;
printf("%u - binary buffer1\n", *((int*)(bin_buf + bin_buf_counter)));
printf("%d - destination adress1\n", adr_of_lab_array[adress].destination_adress);
                        bin_buf_counter += sizeof(int);
printf("%d - binary buffer counter2\n", bin_buf_counter);
                        break;

                    }
                }

            }
        }
        else
        {
            bin_buf_counter += sizeof(char);
        }
    }
}


/*push 1
push 3
pop rax
push 4
push 7
mul
next:
push 3
pop rax
push 4
push 7
jmp next
push 3
pop rax
push 4
push 7

labels:*/
