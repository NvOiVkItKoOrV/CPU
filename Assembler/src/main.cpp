#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/assembler.h"
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
    //printf("%s", text.f_name);
    constructor(&text);

    assembly(&text);

    destructor(&text);
    return 0;
}
