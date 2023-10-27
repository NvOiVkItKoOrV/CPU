#ifndef INPUT_H
#define INPUT_H

struct Str_parameters
{
    char* ptr2str;
    int sz_of_str;
};

struct Text
{
     char* adress_of_buf = nullptr;
     size_t size_of_buf = 0;
     size_t n_lines = 0;
     char* f_name ;
     struct Str_parameters* adress_of_str_parameters = nullptr;
 };

void buf_ctor(struct Text* text);
void buf_dtor(struct Text* text);
void make_buf (struct Text* text);
void input_to_buf (struct Text* text);
void make_array_of_ptr_to_str(struct Text* text);
void put_ptr_to_str (struct Text* text);
void symb_counter(struct Text* text);

#endif /* INPUT_H */
