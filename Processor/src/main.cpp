#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "stack.h"
#include "processor.h"

int main(int argc, char* argv[])
{

    if(argc == 0 || argc > 2)
    {
        printf("Wrong command file name!\n");
        exit(0);
    }

    struct processor_t proc;
    proc.binary_buf.f_name = argv[1];


    proc_ctor(&proc);

    virtual_machine(&proc);

    proc_dtor(&proc);

    return 0;
}
