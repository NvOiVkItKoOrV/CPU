#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../Input_to_buf/include/input.h"
#include "../include/stack.h"
#include "../include/processor.h"

int main(int argc, char* argv[])
{

    if(argc == 0 || argc > 2)
    {
        printf("Wrong command file name!\n");
        exit(0);
    }

    struct processor_t proc;
    proc.text.f_name = argv[1];


    proc_ctor(&proc);

    for(int i = 0; i < proc.text.size_of_buf; i++)
        printf("%d ", *(proc.text.adress_of_buf + i));

    virtual_machine(&proc);

    proc_dtor(&proc);

    return 0;
}
