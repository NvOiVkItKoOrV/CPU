#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/stack.h"
#include "../include/processor.h"


void proc_ctor(struct processor_t* proc)
{
    stack_ctor(&(proc->stk));
    buf_ctor(&(proc->binary_buf));

    proc->rax = 0;
    proc->rbx = 0;
    proc->rcx = 0;
    proc->rdx = 0;

}


void proc_dtor(struct processor_t* proc)
{
    stack_dtor(&(proc->stk));
    buf_dtor(&(proc->binary_buf));

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

        case JA:
            ja_func(proc, &counter);
            break;

        case JAE:
            jae_func(proc, &counter);
            break;

        case JB:
            jb_func(proc, &counter);
            break;

        case JBE:
            jbe_func(proc, &counter);
            break;

        case JE:
            je_func(proc, &counter);
            break;

        case JNE:
            jne_func(proc, &counter);
            break;

        case CALL:
            call_func(proc, &counter);
            break;

        case RET:
            ret_func(proc, &counter);
            break;

        case HLT:
            exit(0);
            break;

        default:
            printf("Syntax error! Wrong command in %lu byte!\n", counter);
            exit(0);
            break;

        }
    }
}


int read_command_func(struct processor_t* proc, size_t* counter)
{
    char com_val;

    memcpy(&com_val, proc->binary_buf.adress_of_buf + *counter, sizeof(char));
    *counter += sizeof(char);

    switch(com_val)
    {
    case PUSH:
        return PUSH;

    case RPUSH:
        return RPUSH;

    case ADD:
        return ADD;

    case POP:
        return POP;

    case SUB:
        return SUB;

    case MUL:
        return MUL;

    case DIV:
        return DIV;

    case SQRT:
        return SQRT;

    case SIN:
        return SIN;

    case COS:
        return COS;

    case JMP:
        return JMP;

    case IN:
        return IN;

    case OUT:
        return OUT;

    case JA:
        return JA;

    case JAE:
        return JAE;

    case JB:
        return JB;

    case JBE:
        return JBE;

    case JE:
        return JE;

    case JNE:
        return JNE;

    case CALL:
        return CALL;

    case RET:
        return RET;

    case HLT:
        return HLT;

    default:
        return ERR;
    }
}


void push_func(struct processor_t* proc, int push_type, size_t* counter)
{
    switch(push_type)
    {
    case PUSH:
        {
        elem_t val;

        memcpy(&val, (int*)(proc->binary_buf.adress_of_buf + *counter), sizeof(elem_t));

        *counter += sizeof(elem_t);

        stack_push(&proc->stk, val);
        break;
        }
    case RPUSH:
        {
            char reg_code;

            memcpy(&reg_code, proc->binary_buf.adress_of_buf + *counter, sizeof(char));
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
                    printf("Wrong register number in push function on %lu byte\n", *counter);
                    break;
                }
            printf("push rax - <%lu> ",proc->rax);
            printf("rbx - <%lu> ",proc->rbx);
            printf("rcx - <%lu> ",proc->rcx);
            printf("rdx - <%lu>\n",proc->rdx);
        }
    }
}


void pop_func(struct processor_t* proc, size_t* counter)
{
    char reg_code;

    memcpy(&reg_code, proc->binary_buf.adress_of_buf + *counter, sizeof(char));
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
        printf("Wrong register number in pop function on %lu byte\n", *counter);
        break;
    }
            printf("pop rax - <%lu> ",proc->rax);
            printf("rbx - <%lu> ",proc->rbx);
            printf("rcx - <%lu> ",proc->rcx);
            printf("rdx - <%lu>\n",proc->rdx);
}


void jmp_func(struct processor_t* proc, size_t* counter)
{
    int adress2jmp = -1;

    memcpy(&adress2jmp, proc->binary_buf.adress_of_buf + *counter, sizeof(int));
    *counter = adress2jmp;
}


void ja_func(struct processor_t* proc, size_t* counter)
{
    elem_t value = 0;
    stack_pop(&proc->stk, &value);

    if(value > proc->rdx)
        jmp_func(proc, counter);

    else
        (*counter) += sizeof(int);

}


void jae_func(struct processor_t* proc, size_t* counter)
{
    elem_t value = 0;
    stack_pop(&proc->stk, &value);

    if(value >= proc->rdx)
        jmp_func(proc, counter);

    else
        (*counter) += sizeof(int);

}


void jb_func(struct processor_t* proc, size_t* counter)
{
    elem_t value = 0;
    stack_pop(&proc->stk, &value);
    printf("stack_pop - <%d>", value);
    if(value < proc->rdx)
    {
        printf("<%d< c-ter", *counter);
        jmp_func(proc, counter);
        printf("sadfhoiajhds");
        printf("<%d< c-ter", *counter);
    }
    else
    {
        printf("pkfkjsidf");
        (*counter) += sizeof(int);
    }

}


void jbe_func(struct processor_t* proc, size_t* counter)
{
    elem_t value = 0;
    stack_pop(&proc->stk, &value);

    if(value <= proc->rdx)
        jmp_func(proc, counter);

    else
        (*counter) += sizeof(int);

}


void je_func(struct processor_t* proc, size_t* counter)
{
    elem_t value = 0;
    stack_pop(&proc->stk, &value);

    if(value == proc->rdx)
        jmp_func(proc, counter);

    else
        (*counter) += sizeof(int);
}


void jne_func(struct processor_t* proc, size_t* counter)
{
    elem_t value = 0;
    stack_pop(&proc->stk, &value);

    if(value != proc->rdx)
        jmp_func(proc, counter);

    else
        (*counter) += sizeof(int);

}


void call_func(struct processor_t* proc, size_t* counter)
{
    proc->rdx = *counter + sizeof(int);
    printf("%d sdhjflks,dfjgslfdighkjlfdsikhlgifhkj",*(int*)(proc->binary_buf.adress_of_buf + *counter));
    printf("<%d>counter", *counter);
    //memcpy(counter, proc->binary_buf.adress_of_buf + *counter, sizeof(int));
    printf("<%d>counter", *counter);
    jmp_func(proc, counter);
}


void ret_func(struct processor_t* proc, size_t* counter)
{
    int ret_adr = proc->rdx;

    memcpy(counter, &ret_adr, sizeof(int));
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
    printf("<<%d>>\n", val);
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

    val = sin(val);
    stack_push(&proc->stk, val);
}


void cos_func(struct processor_t* proc)
{
    elem_t val;
    stack_pop(&proc->stk, &val);

    val = cos(val);
    stack_push(&proc->stk, val);
}
