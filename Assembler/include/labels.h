#ifndef LABELS_H
#define LABELS_H

#include "../../Input_to_buf/include/input.h"

const int max_lab_name_length = 30;
const int max_lab_array_sz = 10;
const int max_sourse_adresses_array_length = 10;
const int incorrect_adress = -1;

struct label_t
{
    char lab_name[max_lab_name_length] = {};
    int destination_adress;
    long int sourse_adresses[max_sourse_adresses_array_length];
    int srs_adr_counter;

};

label_t* array_of_labels_ctor ();
void    array_of_labels_dtor (label_t* array_of_lab);
int     lab_name_exists_check(label_t* array_of_lab, char* new_lab_name);
void fill_adresses2jump(struct Text* text, char* bin_buf, size_t bin_buf_size, label_t* adr_of_lab_array);

#endif /* LABELS_h */
