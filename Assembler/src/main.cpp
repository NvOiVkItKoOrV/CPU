#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"
#include "input.h"

int main(int argc, char* argv[])
{

    if(argc == 0 || argc > 2)
    {
        printf("Wrong command file name!\n");
        exit(0);
    }

    struct Text text = {};
    text.f_name = argv[1];

    buf_ctor(&text);

    assembler(&text);

    buf_dtor(&text);
    return 0;
}
