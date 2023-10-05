
//rename dir
// ./cpu --flags <names>
//главный main (drive)
// makefileодна главнвая цель и разбитые цели

//make
//make run -главное

//make build_asm
//./assembler

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/stack.h"
#include "../include/processor.h"
#include "../../Input_to_buf/include/input.h"

int main(int argc, char* argv[])
{

    if(argc = 0 || argc > 2)
    {
        printf("Wrong command file name!\n");
        exit(0);
    }
    struct Text text = {};
    text.f_name = argv[1];
    constructor(&text);

    struct stack_t stk;
    stack_ctor(&stk);

    for(int i = 0; i < text.n_lines; i++)
    {
        printf("%s\n", text.adress_of_str_parameters[i].ptr2str);
    }
    printf("JOPA");
    virtual_machine(&text, &stk);

    destructor(&text);

    /*char a[] = "svinina blyat";

    char b[30];

    sscanf(a, "%s", b);

    printf("%s", b);*/
    return 0;
}
