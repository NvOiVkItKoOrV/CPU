
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

    if(argc == 0 || argc > 2)
    {
        printf("Wrong command file name!\n");
        exit(0);
    }

    struct processor_t proc;
    proc.text.f_name = argv[1];

    proc_ctor(&proc);

    //printf("%d\n", proc.text.size_of_buf);
//
    //for(int i = 0; i< proc.text.size_of_buf; i++)
      //  printf("%d ",*(proc.text.adress_of_buf + i));

    //printf("JOPA");
    virtual_machine(&proc);


    proc_dtor(&proc);

    return 0;
}
