#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/stack.h"
#include "../include/processor.h"



void proc_ctor(struct processor_t* proc)
{
    stack_ctor(&(proc->stk));
    text_ctor(&(proc->text));

    proc->rax = 0;
    proc->rbx = 0;
    proc->rcx = 0;
    proc->rdx = 0;

}


void proc_dtor(struct processor_t* proc)
{
    stack_dtor(&(proc->stk));
    text_dtor(&(proc->text));

    proc->rax = 0;
    proc->rbx = 0;
    proc->rcx = 0;
    proc->rdx = 0;

}


void virtual_machine(struct processor_t* proc)
{

    size_t counter = 0;
    int command_val = ERR;

    while(command_val != HLT)
    {
        command_val = read_command_func(proc, &counter);

        switch(command_val)
        {
        case PUSH:
            push_func(proc, PUSH, &counter);
            break;

        case RPUSH:
            push_func(proc, RPUSH, &counter);
            break;

        case POP:
            pop_func(proc, &counter);
            break;

        case ADD:
            add_func(proc);
            break;

        case SUB:
            sub_func(proc);
            break;

        case MUL:
            mul_func(proc);
            break;

        case DIV:
            div_func(proc);
            break;

        case SQRT:
            sqrt_func(proc);
            break;

        case SIN:
            sin_func(proc);
            break;

        case COS:
            cos_func(proc);
            break;

        case IN:
            in_func(proc);
            break;

        case OUT:
            out_func(proc);
            break;

        case JMP:
            jmp_func(proc, &counter);
            break;

        case HLT:
            exit(0);
            break;

        default:
            printf("Syntax error! Wrong command in %lu line!\n", counter);
            exit(0);
            break;

        }
    }
}


int read_command_func(struct processor_t* proc, size_t* counter)
{
    char com_val;

    //sscanf(proc->text.adress_of_buf + *counter, "%d", &com_val);
    memcpy(&com_val, proc->text.adress_of_buf + *counter, sizeof(char));
    *counter += sizeof(char);

    char com_check = 63;// 1 1 1 1 1 1 0 0

    com_check = (com_check & com_val);

    if(com_check == PUSH)
    {
        if(com_val == RPUSH)
            return RPUSH;

        else if(com_val == PUSH)
            return PUSH;

        else
        {
            printf("Error in reading command in push checking!\n");
            return ERR;
        }
    }
    else if(com_check == ADD)
        return ADD;

    else if(com_check == POP)
        return POP;

    else if(com_check == SUB)
        return SUB;

    else if(com_check == MUL)
        return MUL;

    else if(com_check == DIV)
        return DIV;

    else if(com_check == SQRT)
        return SQRT;

    else if(com_check == SIN)
        return SIN;

    else if(com_check == JMP)
        return JMP;

    else if(com_check == COS)
        return COS;

    else if(com_check == IN)
        return IN;

    else if(com_check == OUT)
        return OUT;

    else if(com_check == HLT)
        return HLT;

    else
        return ERR;
}


void push_func(struct processor_t* proc,int push_type, size_t* counter)
{
    switch(push_type)
    {
    case PUSH:
        {

        elem_t val;
        //sscanf((int*)(proc->text.adress_of_buf + *counter), "%d",&val);
        memcpy(&val, (int*)(proc->text.adress_of_buf + *counter), sizeof(elem_t));

        //printf("\n %d \n", val);

        *counter += sizeof(elem_t);

        stack_push(&proc->stk, val);
        break;
        }
    case RPUSH:
        {
            char reg_code;

            memcpy(&reg_code, proc->text.adress_of_buf + *counter, sizeof(char));
            *counter += sizeof(char);

                switch(reg_code)
                {
                case REG_A:
                    stack_push(&proc->stk, proc->rax);
                    break;

                case REG_B:
                    stack_push(&proc->stk, proc->rbx);
                    break;

                case REG_C:
                    stack_push(&proc->stk, proc->rcx);
                    break;

                case REG_D:
                    stack_push(&proc->stk, proc->rdx);
                    break;

                default:
                    printf("Wrong register number in push function on %lu line\n", *counter);
                    break;
                }
        }
    }
}


void pop_func(struct processor_t* proc, size_t* counter)
{
    char reg_code;

    memcpy(&reg_code, proc->text.adress_of_buf + *counter, sizeof(char));
    *counter += sizeof(char);

    switch(reg_code)
    {
    case REG_A:
        stack_pop(&proc->stk, &proc->rax);
        break;

    case REG_B:
        stack_pop(&proc->stk, &proc->rbx);
        break;

    case REG_C:
        stack_pop(&proc->stk, &proc->rcx);
        break;

    case REG_D:
        stack_pop(&proc->stk, &proc->rdx);
        break;

    default:
        printf("Wrong register number in pop function on %lu line\n", *counter);
        break;
    }

}


void jmp_func(struct processor_t* proc, size_t* counter)
{
    int adress2jmp;

    memcpy(&adress2jmp, proc->text.adress_of_buf + *counter, sizeof(int));
    *counter = adress2jmp;


}


void add_func(struct processor_t* proc)
{
    elem_t val_1;
    elem_t val_2;
    elem_t sum;

    stack_pop(&proc->stk, &val_1);
    stack_pop(&proc->stk, &val_2);

    sum = val_1 + val_2;

    stack_push(&proc->stk, sum);
}


void sub_func(struct processor_t* proc)
{
    elem_t val_1;
    elem_t val_2;
    elem_t sub;

    stack_pop(&proc->stk, &val_1);
    stack_pop(&proc->stk, &val_2);

    sub = val_1 - val_2;

    stack_push(&proc->stk, sub);
}


void mul_func(struct processor_t* proc)
{
    elem_t val_1;
    elem_t val_2;
    elem_t mul;

    stack_pop(&proc->stk, &val_1);
    stack_pop(&proc->stk, &val_2);

    mul = val_1 * val_2;

    stack_push(&proc->stk, mul);
}


void div_func(struct processor_t* proc)
{
    elem_t val_1;
    elem_t val_2;
    elem_t div;

    stack_pop(&proc->stk, &val_1);
    stack_pop(&proc->stk, &val_2);

    div = val_2 / val_1;

    stack_push(&proc->stk, div);
}


void in_func(struct processor_t* proc)
{
    printf("IN-parameter: \n");
    elem_t val;
    scanf("%d", &val);

    stack_push(&proc->stk, val);
}


void out_func(struct processor_t* proc)
{
    elem_t val = 0;
    stack_pop(&proc->stk, &val);
    printf("%d\n", val);
}


void sqrt_func(struct processor_t* proc)
{
    elem_t val;
    stack_pop(&proc->stk, &val);

    val = sqrt(val);
    stack_push(&proc->stk, val);
}

void sin_func(struct processor_t* proc)
{
    elem_t val;
    stack_pop(&proc->stk, &val);
printf("---------------------lfkjghkjhlkjdhgskdlfhgjlksfdjhg---------------------");
    val = sin(val);
    stack_push(&proc->stk, val);
}

void cos_func(struct processor_t* proc)
{
printf("---------------------------------------------------------------------------------------");
    elem_t val;
    stack_pop(&proc->stk, &val);

    val = cos(val);
    stack_push(&proc->stk, val);
}
