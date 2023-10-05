#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/stack.h"
#include "../include/processor.h"
#include "../../Input_to_buf/include/input.h"

void virtual_machine(struct Text* text, struct stack_t* stk)
{
    int counter = 0;
    int command_val;

    while(command_val != HLT)
    {
        command_val = read_command_func(text, counter);
        switch(command_val)
        {
        case PUSH:
            push_func(text, stk, counter);
            break;

        case ADD:
            add_func(stk);
            break;

        case SUB:
            sub_func(stk);
            break;

        case MUL:
            mul_func(stk);
            break;

        case DIV:
            div_func(stk);
            break;

        case SQRT:
            //sqrt_func();
            break;

        case SIN:
            //sin_func();
            break;

        case COS:
            //cos_func();
            break;

        case IN:
            in_func(stk);
            break;

        case OUT:
            out_func(stk);
            break;

        case HLT:
            exit(0);
            break;

        case ERR:
            printf("Wrong command! %d string\n", counter + 1);
            break;

        default:
            abort();

        }

        counter++;
    }

}

int read_command_func(struct Text* text, int counter)
{
    int com_val;

    sscanf(text->adress_of_str_parameters[counter].ptr2str, "%d", com_val);

    if(com_val == PUSH)
        return PUSH;

    else if(com_val == ADD)
        return ADD;

    else if(com_val == SUB)
        return SUB;

    else if(com_val == MUL)
        return MUL;

    else if(com_val == DIV)
        return DIV;

    else if(com_val == SQRT)
        return SQRT;

    else if(com_val == SIN)
        return SIN;

    else if(com_val == COS)
        return COS;

    else if(com_val == IN)
        return IN;

    else if(com_val == OUT)
        return OUT;

    else if(com_val == HLT)
        return HLT;

    else
        return ERR;
}

void push_func(struct Text* text, struct stack_t* stk, int counter)
{
    elem_t val;
    sscanf(text->adress_of_str_parameters[counter].ptr2str + strlen("push"), "%d", &val);

    stack_push(stk, val);
}

void add_func(struct stack_t* stk)
{
    elem_t val_1;
    elem_t val_2;
    elem_t sum;

    stack_pop(stk, &val_1);
    stack_pop(stk, &val_2);

    sum = val_1 + val_2;

    stack_push(stk, sum);
}


void sub_func(struct stack_t* stk)
{
    elem_t val_1;
    elem_t val_2;
    elem_t sub;

    stack_pop(stk, &val_1);
    stack_pop(stk, &val_2);

    sub = val_1 - val_2;

    stack_push(stk, sub);
}

void mul_func(struct stack_t* stk)
{
    elem_t val_1;
    elem_t val_2;
    elem_t mul;

    stack_pop(stk, &val_1);
    stack_pop(stk, &val_2);

    mul = val_1 * val_2;

    stack_push(stk, mul);
}

void div_func(struct stack_t* stk)
{
    elem_t val_1;
    elem_t val_2;
    elem_t div;

    stack_pop(stk, &val_1);
    stack_pop(stk, &val_2);

    div = val_2 / val_1;

    stack_push(stk, div);
}

void in_func(struct stack_t* stk)
{
    printf("IN-parameter: \n");
    elem_t val;
    scanf("%d", &val);

    stack_push(stk, val);
}

void out_func(struct stack_t* stk)
{
    elem_t val = 0;
    stack_pop(stk, &val);
    printf("%d\n", val);
}
