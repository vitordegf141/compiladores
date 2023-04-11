

#include "asm.h"
#include "y.tab.h"
#include "hash.h"
void writeASM(Tac* tac,FILE* out)
{
    if(tac==NULL)
        return;
    if(tac->type==TAC_SYMBOL)
        return;
    switch (tac->type)
    {
    case TAC_PROGRAM:
        
        fprintf(out,"\t.data\n");
        print_lit_temp_to_ASM(out);
        fprintf(out,".section\t.rodata\n");
        fprintf(out,".LC0:\n");
        fprintf(out,"\t.string	\"%%d\"\n");
        fprintf(out,".LC1:\n");
        fprintf(out,"\t.string	\"%%s\"\n");
        fprint(out,"\tendbr64\n");
        break;
    case TAC_ADD:
        if(tac->res==NULL) fprintf(stderr,"\n TAC_ADD res eh NULL\n");
        if(tac->op1==NULL) fprintf(stderr,"\n TAC_ADD op1 eh NULL\n");
        if(tac->op2==NULL) fprintf(stderr,"\n TAC_ADD op2 eh NULL\n");
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            if(tac->op1->type == KW_INTE)
                fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op1->name); //move inte value to eax
            else if (tac->op1->type == KW_CARA)
            {
                fprintf(out,"\tmovzbl\t%s(%%rip), %%eax\n", tac->op1->name); //move byte to to eax
            }
            if(tac->op2->type == KW_INTE)
                fprintf(out,"\tmovl\t%s(%%rip), %%edx\n", tac->op2->name); //move inte value to edx
            else if (tac->op2->type == KW_CARA)
            {
                fprintf(out,"\tmovzbl\t%s(%%rip), %%edx\n", tac->op2->name); //move byte to to edx
            }
            fprintf(out,"\taddl\t%%edx, %%eax\n"); //compare eax to edx
            if(tac->res->type == KW_INTE)
                fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name); //move inte value to edx
            else if (tac->res->type == KW_CARA)
            {
                fprintf(out,"\tmovb\t%%al, %s(%%rip)\n", tac->res->name); //move byte to to edx
            }
        }
        break;
    case TAC_SUB:
        if(tac->res==NULL) fprintf(stderr,"\n TAC_SUB res eh NULL\n");
        if(tac->op1==NULL) fprintf(stderr,"\n TAC_SUB op1 eh NULL\n");
        if(tac->op2==NULL) fprintf(stderr,"\n TAC_SUB op2 eh NULL\n");
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            if(tac->op1->type == KW_INTE)
                fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op1->name); //move inte value to eax
            else if (tac->op1->type == KW_CARA)
            {
                fprintf(out,"\tmovzbl\t%s(%%rip), %%eax\n", tac->op1->name); //move byte to to eax
            }
            if(tac->op2->type == KW_INTE)
                fprintf(out,"\tmovl\t%s(%%rip), %%edx\n", tac->op2->name); //move inte value to edx
            else if (tac->op2->type == KW_CARA)
            {
                fprintf(out,"\tmovzbl\t%s(%%rip), %%edx\n", tac->op2->name); //move byte to to edx
            }
            fprintf(out,"\tsubl\t%%edx, %%eax\n"); //compare eax to edx
            if(tac->res->type == KW_INTE)
                fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name); //move inte value to edx
            else if (tac->res->type == KW_CARA)
            {
                fprintf(out,"\tmovb\t%%al, %s(%%rip)\n", tac->res->name); //move byte to to edx
            }
        }
        break;
    case TAC_COPY:
        if(tac->res==NULL) fprintf(stderr,"\n TAC_ADD res eh NULL\n");
        if(tac->op1==NULL) fprintf(stderr,"\n TAC_ADD op1 eh NULL\n");
        if(tac->res!=NULL && tac->op1!=NULL)
        {
            if(tac->op1->type==KW_CARA)
                fprintf(out,"\tmovzbl\t%s(%%rip), %%eax\n", tac->op1->name);
            else
                fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op1->name); //move variable1 value to eax
            if(tac->res->type==KW_CARA)
                fprintf(out,"\tmovb\t%%al, %s(%%rip)\n", tac->op1->name);
            else
                fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->op1->name); //move variable1 value to eax
        }
        break;
    case TAC_MULT:
        if(tac->res==NULL) fprintf(stderr,"\n TAC_ADD res eh NULL\n");
        if(tac->op1==NULL) fprintf(stderr,"\n TAC_ADD op1 eh NULL\n");
        if(tac->op2==NULL) fprintf(stderr,"\n TAC_ADD op2 eh NULL\n");
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            if(tac->op1->type == KW_INTE)
                fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op1->name); //move inte value to eax
            else if (tac->op1->type == KW_CARA)
            {
                fprintf(out,"\tmovzbl\t%s(%%rip), %%eax\n", tac->op1->name); //move byte to to eax
            }
            if(tac->op2->type == KW_INTE)
                fprintf(out,"\tmovl\t%s(%%rip), %%edx\n", tac->op2->name); //move inte value to edx
            else if (tac->op2->type == KW_CARA)
            {
                fprintf(out,"\tmovzbl\t%s(%%rip), %%edx\n", tac->op2->name); //move byte to to edx
            }
            fprintf(out,"\timull\t%%edx, %%eax\n"); //compare eax to edx
            if(tac->res->type == KW_INTE)
                fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name); //move inte value to edx
            else if (tac->res->type == KW_CARA)
            {
                fprintf(out,"\tmovb\t%%al, %s(%%rip)\n", tac->res->name); //move byte to to edx
            }
        }
        break;
    case TAC_DIV:
        if(tac->res==NULL) fprintf(stderr,"\n TAC_ADD res eh NULL\n");
        if(tac->op1==NULL) fprintf(stderr,"\n TAC_ADD op1 eh NULL\n");
        if(tac->op2==NULL) fprintf(stderr,"\n TAC_ADD op2 eh NULL\n");
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            if(tac->op1->type == KW_INTE)
                fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op1->name); //move inte value to eax
            else if (tac->op1->type == KW_CARA)
            {
                fprintf(out,"\tmovzbl\t%s(%%rip), %%eax\n", tac->op1->name); //move byte to to eax
            }
            if(tac->op2->type == KW_INTE)
                fprintf(out,"\tmovl\t%s(%%rip), %%ecx\n", tac->op2->name); //move inte value to edx
            else if (tac->op2->type == KW_CARA)
            {
                fprintf(out,"\tmovzbl\t%s(%%rip), %%edx\n", tac->op2->name); //move byte to to edx
                fprintf(out,"\tmovsbl\t%%dl, %%ecx\n"); //move byte to to edx
            }
            fprintf(out,"\tcltd\n");
            fprintf(out,"\tidivl\t%%ecx\n");
            if(tac->res->type == KW_INTE)
                fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name); //move inte value to edx
            else if (tac->res->type == KW_CARA)
            {
                fprintf(out,"\tmovb\t%%al, %s(%%rip)\n", tac->res->name); //move byte to to edx
            }
        }   
        break;
    case TAC_GT:
        if(tac->res==NULL) fprintf(stderr,"\n%d TAC_GT res eh NULL\n",TAC_LABEL);
        if(tac->op1==NULL) fprintf(stderr,"\n%d TAC_GT op1 eh NULL\n",TAC_LABEL);
        if(tac->op2==NULL) fprintf(stderr,"\n%d TAC_GT op2 eh NULL\n",TAC_LABEL);
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            fprintf(out,"\tmovl\t%s(%%rip), %%edx\n", tac->op1->name); //move variable1 value to edx
            fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op2->name); //move variable2 value to eax
            fprintf(out,"\tcmpl\t%%eax, %%edx\n"); //compare eax to edx
            fprintf(out,"\tsetg\t%%al\n"); //if flag zero is down than set 1 to al
            fprintf(out,"\tmovzbl\t%%al, %%eax\n"); //move al value to eax
            fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name);//move value (eax) to dest
        }
        break;
    case TAC_GE:
        if(tac->res==NULL) fprintf(stderr,"\n%d TAC_GE res eh NULL\n",TAC_LABEL);
        if(tac->op1==NULL) fprintf(stderr,"\n%d TAC_GE op1 eh NULL\n",TAC_LABEL);
        if(tac->op2==NULL) fprintf(stderr,"\n%d TAC_GE op2 eh NULL\n",TAC_LABEL);
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            fprintf(out,"\tmovl\t%s(%%rip), %%edx\n", tac->op1->name); //move variable1 value to edx
            fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op2->name); //move variable2 value to eax
            fprintf(out,"\tcmpl\t%%eax, %%edx\n"); //compare eax to edx
            fprintf(out,"\tsetge\t%%al\n"); //if flag zero is down than set 1 to al
            fprintf(out,"\tmovzbl\t%%al, %%eax\n"); //move al value to eax
            fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name);//move value (eax) to dest
        }
        break;
    case TAC_LT:
        if(tac->res==NULL) fprintf(stderr,"\n%d TAC_GT res eh NULL\n",TAC_LABEL);
        if(tac->op1==NULL) fprintf(stderr,"\n%d TAC_GT op1 eh NULL\n",TAC_LABEL);
        if(tac->op2==NULL) fprintf(stderr,"\n%d TAC_GT op2 eh NULL\n",TAC_LABEL);
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            fprintf(out,"\tmovl\t%s(%%rip), %%edx\n", tac->op1->name); //move variable1 value to edx
            fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op2->name); //move variable2 value to eax
            fprintf(out,"\tcmpl\t%%eax, %%edx\n"); //compare eax to edx
            fprintf(out,"\tsetl\t%%al\n"); //if flag  is down than set 1 to al
            fprintf(out,"\tmovzbl\t%%al, %%eax\n"); //move al value to eax
            fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name);//move value (eax) to dest
        }
        break;
    case TAC_LE:
        if(tac->res==NULL) fprintf(stderr,"\n%d TAC_GT res eh NULL\n",TAC_LABEL);
        if(tac->op1==NULL) fprintf(stderr,"\n%d TAC_GT op1 eh NULL\n",TAC_LABEL);
        if(tac->op2==NULL) fprintf(stderr,"\n%d TAC_GT op2 eh NULL\n",TAC_LABEL);
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            fprintf(out,"\tmovl\t%s(%%rip), %%edx\n", tac->op1->name); //move variable1 value to edx
            fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op2->name); //move variable2 value to eax
            fprintf(out,"\tcmpl\t%%eax, %%edx\n"); //compare eax to edx
            fprintf(out,"\tsetle\t%%al\n"); //if flag  is down than set 1 to al
            fprintf(out,"\tmovzbl\t%%al, %%eax\n"); //move al value to eax
            fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name);//move value (eax) to dest
        }
        break;
    case TAC_DIF:
        if(tac->res==NULL) fprintf(stderr,"\n%d TAC_DIF res eh NULL\n",TAC_LABEL);
        if(tac->op1==NULL) fprintf(stderr,"\n%d TAC_DIF op1 eh NULL\n",TAC_LABEL);
        if(tac->op2==NULL) fprintf(stderr,"\n%d TAC_DIF op2 eh NULL\n",TAC_LABEL);
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            fprintf(out,"\tmovl\t%s(%%rip), %%edx\n", tac->op1->name); //move variable1 value to edx
            fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op2->name); //move variable2 value to eax
            fprintf(out,"\tcmpl\t%%eax, %%edx\n"); //compare eax to edx
            fprintf(out,"\tsetne\t%%al\n"); //if flag zero is down than set 1 to al
            fprintf(out,"\tmovzbl\t%%al, %%eax\n"); //move al value to eax
            fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name);//move value (eax) to dest
        }
        break;
    case TAC_EQ:
        if(tac->res==NULL) fprintf(stderr,"\n%d TAC_EQ res eh NULL\n",TAC_LABEL);
        if(tac->op1==NULL) fprintf(stderr,"\n%d TAC_EQ op1 eh NULL\n",TAC_LABEL);
        if(tac->op2==NULL) fprintf(stderr,"\n%d TAC_EQ op2 eh NULL\n",TAC_LABEL);
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            fprintf(out,"\tmovl\t%s(%%rip), %%edx\n", tac->op1->name); //move variable1 value to edx
            fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op2->name); //move variable2 value to eax
            fprintf(out,"\tcmpl\t%%eax, %%edx\n"); //compare eax to edx
            fprintf(out,"\tsete\t%%al\n"); //if flag zero is up than set 1 to al
            fprintf(out,"\tmovzbl\t%%al, %%eax\n"); //move al value to eax
            fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name);//move value (eax) to dest
        }
        break;
    case TAC_AND:
        if(tac->res==NULL) fprintf(stderr,"\n%d TAC_AND res eh NULL\n",TAC_LABEL);
        if(tac->op1==NULL) fprintf(stderr,"\n%d TAC_AND op1 eh NULL\n",TAC_LABEL);
        if(tac->op2==NULL) fprintf(stderr,"\n%d TAC_AND op2 eh NULL\n",TAC_LABEL);
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            fprintf(out,"\tmovl\t%s(%%rip), %%edx\n", tac->op1->name); //move variable1 value to edx
            fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op2->name); //move variable2 value to eax
            fprintf(out,"\taddl\t%%eax, %%edx\n"); //compare eax to edx
            fprintf(out,"\tcmpl\t$2, %%edx\n"); //abussing the fact that and only operates with bools
            fprintf(out,"\tsete\t%%al\n"); //if flag zero is up than set 1 to al
            fprintf(out,"\tmovzbl\t%%al, %%eax\n"); //move al value to eax
            fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name);//move value (eax) to dest
        }
        break;
    case TAC_OR:
        if(tac->res==NULL) fprintf(stderr,"\n TAC_AND res eh NULL\n");
        if(tac->op1==NULL) fprintf(stderr,"\n TAC_AND op1 eh NULL\n");
        if(tac->op2==NULL) fprintf(stderr,"\n TAC_AND op2 eh NULL\n");
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            fprintf(out,"\tmovl\t%s(%%rip), %%edx\n", tac->op1->name); //move variable1 value to edx
            fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op2->name); //move variable2 value to eax
            fprintf(out,"\taddl\t%%eax, %%edx\n"); //compare eax to edx
            fprintf(out,"\tcmpl\t$1, %%edx\n"); //abussing the fact that and only operates with bools
            fprintf(out,"\tsetge\t%%al\n"); //if flag zero is up than set 1 to al
            fprintf(out,"\tmovzbl\t%%al, %%eax\n"); //move al value to eax
            fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name);//move value (eax) to dest
        }
        break;
    case TAC_JF:
        if(tac->res==NULL) fprintf(stderr,"\n TAC_JF res eh NULL\n");
        if(tac->op1==NULL) fprintf(stderr,"\n TAC_JF op1 eh NULL\n");
        if(tac->res!=NULL && tac->op1!=NULL)
        {
            fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op1->name); //move variable1 value to eax
            fprintf(out,"\ttestl\t%%eax, %%eax\n"); //compare variable to variable
            fprintf(out,"\tje\t%s\n", tac->res->name);//if equal jump ? gcc makes it this way
        }
        break;
    case TAC_NOT:
        if(tac->res==NULL) fprintf(stderr,"\n TAC_JF res eh NULL\n");
        if(tac->op1==NULL) fprintf(stderr,"\n TAC_JF op1 eh NULL\n");
        if(tac->res!=NULL && tac->op1!=NULL)
        {
            fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op1->name); //move variable1 value to eax
            fprintf(out,"\ttestl\t%%eax, %%eax\n"); //compare variable to variable
            fprintf(out,"\tsete\t%%al\n"); //if flag zero is up than set 1 to al ?
            fprintf(out,"\tmovzbl\t%%al, %%eax\n"); //move al value to eax
            fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name);//move value (eax) to dest
        }
        break;
    case TAC_JUMP:
        if(tac->res==NULL) fprintf(stderr,"\nTAC_JUMP res eh NULL\n");
        if(tac->res!=NULL)
            fprintf(out,"\tjmp %s\n",tac->res->name);
        break;
    case TAC_LABEL:
        if(tac->res==NULL) fprintf(stderr,"\nTAC_LABEL res eh NULL\n");
        if(tac->res!=NULL)
            fprintf(out,"%s:\n",tac->res->name);
        break;
    case TAC_VEC_POS:
        if(tac->res==NULL) fprintf(stderr,"\n%d TAC_VEC_POS res eh NULL\n",TAC_LABEL);
        if(tac->op1==NULL) fprintf(stderr,"\n%d TAC_VEC_POS op1 eh NULL\n",TAC_LABEL);
        if(tac->op2==NULL) fprintf(stderr,"\n%d TAC_VEC_POS op2 eh NULL\n",TAC_LABEL);
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op2->name); //move index variable value to eax
            fprintf(out,"\tcltq\n"); //extend long to quad, saves it on %rax
            fprintf(out,"\tleaq\t0(,%%rax,4), %%rdx\n"); //move index variable value to rdx
            fprintf(out,"\tleaq\t%s(%%rip), %%rax\n", tac->op1->name); //move vector adress to rax
            fprintf(out,"\tmovl\t(%%rdx,%%rax), %%eax\n");//move value to vector adress plus eax
            fprintf(out,"\tmovl\t%%eax, %s(%%rip)\n", tac->res->name);//move value (eax) to dest
        }
        break;
    case TAC_VEC_ASS:
        if(tac->res==NULL) fprintf(stderr,"\n%d TAC_VEC_ASS res eh NULL\n",TAC_LABEL);
        if(tac->op1==NULL) fprintf(stderr,"\n%d TAC_VEC_ASS op1 eh NULL\n",TAC_LABEL);
        if(tac->op2==NULL) fprintf(stderr,"\n%d TAC_VEC_ASS op2 eh NULL\n",TAC_LABEL);
        if(tac->res!=NULL && tac->op1!=NULL && tac->op2!=NULL)
        {
            fprintf(out,"\tmovq\t%s(%%rip), %%rdx\n", tac->op1->name); //move index variable adress to rdx
            fprintf(out,"\tleaq\t0(,%%rdx,4), %%rcx\n"); //move index variable value to rcx
            fprintf(out,"\tmovl\t%s(%%rip), %%eax\n", tac->op2->name); //move value variable value to eax
            fprintf(out,"\tleaq\t%s(%%rip), %%rdx\n", tac->res->name); //move vector adress to rdx
            fprintf(out,"\tmovl\t%%eax, (%%rcx,%%rdx)\n");//move value to vector adress plus rcx
        }
        break;
    case TAC_READ:
        fprintf(out,"TAC_READ");
        break;
    case TAC_PRINT:
        if(tac->op1==NULL) fprintf(stderr,"\t%d TAC_VALUE res eh NULL\n",TAC_LABEL);
        if(tac->op1 != NULL)
        {
            switch (tac->op1->type)
            {
            case KW_CARA:
                fprintf(out,"\tmovl	%s(%%rip), %%edi\n",tac->op1->name);  //Move value of variable to edi
                fprintf(out,"\tcall\tputchar@PLT\n"); // call printf
                break;
            case KW_INTE:
                fprintf(out,"\tmovl	%s(%%rip), %%esi\n",tac->op1->name);  //Move value of variable to esi(gcc made it to eax, than moved eax to esi)
                fprintf(out,"\tleaq\t.LC0(%%rip), %%rdi\n");  //Move adress of %d to rdi
                fprintf(out,"\tmovl\t$0, %%eax\n"); //Move 0 to eax, part of printf definition
                fprintf(out,"\tcall\tprintf@PLT\n"); // call printf
                break;
            case KW_REAL:
                fprintf(out,"\tmovl	%s(%%rip), %%esi\n",tac->op1->name);  //Move value of variable to esi(gcc made it to eax, than moved eax to esi)
                fprintf(out,"\tleaq\t.LC0(%%rip), %%rdi\n");  //Move adress of %d to rdi
                fprintf(out,"\tmovl\t$0, %%eax\n"); //Move 0 to eax, part of printf definition
                fprintf(out,"\tcall\tprintf@PLT\n"); // call printf
                break;
            case LIT_STRING:
                fprintf(out,"\tleaq\t%s(%%rip), %%rsi\n",tac->op1->name);  //Move adress of lit to rsi
                fprintf(out,"\tleaq\t.LC1(%%rip), %%rdi\n");  //Move adress of %s to rdi
                fprintf(out,"\tmovl\t$0, %%eax\n"); //Move 0 to eax, part of printf definition
                fprintf(out,"\tcall\tprintf@PLT\n"); // call printf
                break;
            default:
                break;
            }
        }
        break;
    case TAC_FUNC_BEGIN:
        if(tac->res==NULL) fprintf(stderr,"\t%d TAC_FUNC_BEGIN res eh NULL\n",TAC_LABEL);
        if(tac->res!=NULL)
        {
            if(strcmp("_tk_main",tac->res->name)==0)
            {
                fprintf(out,"\t.globl\tmain\n");
                fprintf(out,"\t.type\tmain, @function\n");
                fprintf(out,"main:\n");
            }
            else
            {
                fprintf(out,"\t.globl\t%s\n",tac->res->name);
                fprintf(out,"\t.type\t%s, @function\n",tac->res->name);
                fprintf(out,"%s:\n",tac->res->name);
            }
            
            fprintf(out,"\t.cfi_startproc\n");
            fprintf(out,"\tpushq\t%%rbp\n");
            fprintf(out,"\tmovq\t%%rsp, %%rbp\n");
        }
            
        break;    
    case TAC_FUNC_END:
        
        fprintf(out,"\tpopq\t%%rbp\n");
        fprintf(out,"\tret\n");
        fprintf(out,"\t.cfi_endproc\n");
        break;
    case TAC_FUNC_CALL:
    if(tac->res==NULL) fprintf(stderr,"\t%d TAC_FUNC_BEGIN res eh NULL\n",TAC_LABEL);
    if(tac->res!=NULL)
        fprintf(out,"\tcall	%s\n",tac->res->name);
        break;
    case TAC_VALUE:
        if(tac->res==NULL) fprintf(stderr,"\t%d TAC_VALUE res eh NULL\n",TAC_LABEL);
        if(tac->res != NULL)
        {
            switch (tac->res->type)
            {
            case KW_CARA:
                if( tac->op1 !=NULL)
                    fprintf(out,".byte\t\'%s\'\n",tac->op1->value);
                else
                    fprintf(out,".byte\t0\n");
                break;
            case KW_INTE:
                if( tac->op1 !=NULL)
                    fprintf(out,"\t.long\t%s\n",tac->op1->value);
                else
                    fprintf(out,"\t.long\t0\n");
                break;
            case KW_REAL:
                if( tac->op1 !=NULL)
                    fprintf(out,"\t.long\t%s\n",tac->op1->value);
                else
                    fprintf(out,"\t.long\t0\n");
                break;
            case LIT_STRING:
                if( tac->op1 !=NULL)
                    fprintf(out,"\t.string\t\"%s\"\n",tac->op1->value);
                else
                    fprintf(out,"\t.string\t\"\"\n");
                break;
            default:
                break;
            }
        }
        break;
    case TAC_RET:
        fprintf(out,"\tpopq	%%rbp\n");
        fprintf(out,"\tret\n");
        break;

    default:
        fprintf(out,"TAC_UNKNOWN");
        break;
    }
    fflush(out);
}


void generateAsm(Tac* tac,FILE* out)
{
    if(tac==NULL)
        return;
    generateAsm(tac->prev,out);
    writeASM(tac,out);
    return;
}