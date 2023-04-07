
#include "ast.h"
#include <string.h>
#include "y.tab.h"

#define isEntrada -2
#define canNotDetermine -10
int verify_exp(Ast* exp, int* result);
int verify_func_call(Ast* func_call);
int verify_vector_list_assig(Ast* vect,int *result);
int verify_redeclarations(Ast* head)
{
    printf("\nverifying redeclarations\n");
    fflush(stdout);
    if(head->sons[3] == NULL)
        return 0;
    int result=0;
    if(head->ast_type != head_list_decl)
    {   
        printf("NOT HEAD\n");
        printf("head receive type = %d ",head->ast_type);
    }
       
    Ast* first_tail =head->sons[3];
    int number_of_declarations =0;
    Ast* temp =first_tail;
    for(number_of_declarations =0;temp->sons[3]!=NULL;temp=temp->sons[3])
        number_of_declarations++;
    char **names_found = (char **) malloc(sizeof(char **)*number_of_declarations);
    printf("number of declaration: %d\n",number_of_declarations);
    int len_names_found =0;
    int current_name_found=0;
    int has_found=0;
    int brk =0;
    Ast* declaration;
    if (first_tail->sons[3]==NULL)
        return 0;
    for(temp =first_tail;brk==0;temp=temp->sons[3])
    {
        if (temp->sons[3]==NULL)
        {
            brk=1;
        }

        if(temp->sons[0] == NULL)
        {
            printf("TAIL SON IS EMPTY\n");
            fflush(stdin);
            exit(4);
        }
            
        declaration = temp->sons[0];
        has_found=0;
        printf("verifying name = %s\n",declaration->symbol->name);
        for(current_name_found=0;current_name_found<len_names_found;current_name_found++)
        {
            if(strcmp(names_found[current_name_found],declaration->symbol->name) ==0)
            {
                has_found =1;
                fprintf(stderr, "\n name %s is being redeclared!\n",names_found[current_name_found]);
                result =4;
            }
        }
        if(has_found == 0)
        {
            if(len_names_found >= number_of_declarations)
            {
                fprintf(stderr, "\n IS ADDING MORE NAMES THAN NUMBER OF DECLARATIONS!\n");
                fflush(stderr);
                exit(4);
            }
            names_found[len_names_found] = declaration->symbol->name;
            len_names_found++;
        }
    }
    return result;
}

int compare_type(int type1,int type2)
{
    if(type1 == isEntrada || type1 == isEntrada)
        return 0;
    if(type1 == LIT_INTEIRO || type1 == LIT_CHAR)
    {
        if(type1 == LIT_INTEIRO || type1 == LIT_CHAR)
            return 0;
        else
            {
                fprintf(stderr,"assigning ");
                decode_language_type(type2,stderr);
                fprintf(stderr," to ");
                decode_language_type(type1,stderr);
                fprintf(stderr,"\n");
            }
            
    }
    else if(type1 ==type2)
            return 0;
        else
            {
                fprintf(stderr,"assigning ");
                decode_language_type(type2,stderr);
                fprintf(stderr," to ");
                decode_language_type(type1,stderr);
                fprintf(stderr,"\n");
                return 1;
            }
}

int verify_expressions(Ast* head)
{
    printf("\nverifying expressions\n\n");
    fflush(stdout);
    if(head->sons[3] == NULL)
        return 0;
    int result=0;
    if(head->ast_type != head_list_decl)
    {   
        printf("NOT HEAD\n");
        printf("head receive type = %d ",head->ast_type);
    }
    Ast* first_tail =head->sons[3];
    Ast* decl;
    int brk=0;
    result =0;
    printf("init veryfing expresions\n");
    for(Ast* temp=first_tail;brk==0;temp = temp->sons[3])
    {
        if(temp->sons[3] == NULL)
            brk=1;
        if(temp->sons[0] == NULL)
        {
            printf("TAIL SON IS EMPTY\n");
            fflush(stdin);
            exit(4);
        }
        decl = temp->sons[0];
        printf("decl type is = %d\n",decl->ast_type);
        switch (decl->ast_type)
        {
        case var_decl:
            printf("var_decl\n");
            result +=compare_type(decl->type,verify_exp(decl->sons[0],&result));
            break;
        case vector_decl:
            printf("vector_decl\n");
            verify_vector_list_assig(decl,&result);
            break;
        case function_decl:
            /* code */
            break;
        default:
            printf("DEFAULTS SHOULD NOT BE HAPPENING\n");
            break;
        }
    }
    if (result >0)
        return 4;
    else
        return 0;
}

int verify_exp(Ast* exp,int* result)
{
    int type1;
    int type2;
    switch (exp->ast_type)
    {
        case expression_var :
            if(exp->symbol->declaration != NULL || exp->symbol->symbol_type==0)
            {
                if(exp->symbol->symbol_type==0)
                    printf("eh literal type: %d\n",exp->symbol->type);
                return exp->symbol->type;
            }
                
            else
            {
                fprintf(stderr,"Undeclared variable %s\n",exp->symbol->name);
                return canNotDetermine;
            }
            break;
        case expression_entrada :
            return isEntrada;
            break;
        case expression_func_call :
            if(exp->symbol->declaration != NULL)
            {
                if(exp->symbol->symbol_type != function_simbol)
                {
                    fprintf(stderr," %s is not a function\n",exp->symbol->name);
                    return canNotDetermine;
                }
                else
                {
                    *result += verify_func_call(exp);
                    return exp->symbol->type;
                }
            }
            else
            {
                fprintf(stderr,"Undeclared function %s\n",exp->symbol->name);
                return canNotDetermine;
            }
            break;
        case expression_vector_pos :
            if(exp->symbol->declaration != NULL)
            {
                if(exp->symbol->symbol_type != vector_simbol)
                {
                    fprintf(stderr," %s is not a vector\n",exp->symbol->name);
                    return canNotDetermine;
                }
                else
                {
                    *result += compare_type(LIT_INTEIRO,verify_exp(exp->sons[0],result));
                    return exp->symbol->type;
                }
            }
            else
            {
                fprintf(stderr,"Undeclared vector %s\n",exp->symbol->name);
                return canNotDetermine;
            }
            break;
        case expression_parentesis :
            return verify_exp(exp->sons[0],result);
            break;
        case expression_add :
            type1 = verify_exp(exp->sons[0],result);
            type2 = verify_exp(exp->sons[1],result);
            if(type1 == LIT_STRING || type2 == LIT_STRING)
            {
                fprintf(stderr,"can not add string");
                return canNotDetermine;
            }
            if(compare_type(type1,type2) ==0)
                return type1;
            else
                return canNotDetermine;
            break;
        case expression_minus :
            type1 = verify_exp(exp->sons[0],result);
            type1 = verify_exp(exp->sons[1],result);
            if(type1 == LIT_STRING || type2 == LIT_STRING)
            {
                fprintf(stderr,"can not subtract string");
                return canNotDetermine;
            }
            if(compare_type(type1,type2) ==0)
                return type1;
            else
                return canNotDetermine;
            break;
        case expression_mult :
            type1 = verify_exp(exp->sons[0],result);
            type1 = verify_exp(exp->sons[1],result);
            if(type1 == LIT_STRING || type2 == LIT_STRING)
            {
                fprintf(stderr,"can not multiplicate string");
                return canNotDetermine;
            }
            if(compare_type(type1,type2) ==0)
                return type1;
            else
                return canNotDetermine;
            break;
        case expression_divison :
            type1 = verify_exp(exp->sons[0],result);
            type1 = verify_exp(exp->sons[1],result);
            if(type1 == LIT_STRING || type2 == LIT_STRING)
            {
                fprintf(stderr,"can not divide string");
                return canNotDetermine;
            }
            if(compare_type(type1,type2) ==0)
                return type1;
            else
                return canNotDetermine;
            break;
        case expression_gt :
            type1 = verify_exp(exp->sons[0],result);
            type1 = verify_exp(exp->sons[1],result);
            if(type1 == LIT_STRING || type2 == LIT_STRING)
            {
                fprintf(stderr,"can not GT string");
                return canNotDetermine;
            }
            if(compare_type(type1,type2) ==0)
                return LIT_BOOL;
            else
                return canNotDetermine;
            break;
        case expression_ge :
            type1 = verify_exp(exp->sons[0],result);
            type1 = verify_exp(exp->sons[1],result);
            if(type1 == LIT_STRING || type2 == LIT_STRING)
            {
                fprintf(stderr,"can not GE string");
                return canNotDetermine;
            }
            if(compare_type(type1,type2) ==0)
                return LIT_BOOL;
            else
                return canNotDetermine;
            break;
        case expression_lt :
            type1 = verify_exp(exp->sons[0],result);
            type1 = verify_exp(exp->sons[1],result);
            if(type1 == LIT_STRING || type2 == LIT_STRING)
            {
                fprintf(stderr,"can not LT string");
                return canNotDetermine;
            }
            if(compare_type(type1,type2) ==0)
                return LIT_BOOL;
            else
                return canNotDetermine;
            break;
        case expression_le :
            type1 = verify_exp(exp->sons[0],result);
            type1 = verify_exp(exp->sons[1],result);
            if(type1 == LIT_STRING || type2 == LIT_STRING)
            {
                fprintf(stderr,"can not LE string");
                return canNotDetermine;
            }
            if(compare_type(type1,type2) ==0)
                return LIT_BOOL;
            else
                return canNotDetermine;
            break;
        case expression_dif :
            type1 = verify_exp(exp->sons[0],result);
            type1 = verify_exp(exp->sons[1],result);
            if(type1 == LIT_STRING || type2 == LIT_STRING)
            {
                fprintf(stderr,"can not DIF string");
                return canNotDetermine;
            }
            if(compare_type(type1,type2) ==0)
                return LIT_BOOL;
            else
                return canNotDetermine;
            break;
        case expression_eq :
            type1 = verify_exp(exp->sons[0],result);
            type1 = verify_exp(exp->sons[1],result);
            if(type1 == LIT_STRING || type2 == LIT_STRING)
            {
                fprintf(stderr,"can not EQ string");
                return canNotDetermine;
            }
            if(compare_type(type1,type2) ==0)
                return LIT_BOOL;
            else
                return canNotDetermine;
            break;
        case expression_and :
            type1 = verify_exp(exp->sons[0],result);
            type1 = verify_exp(exp->sons[1],result);
            if(type1 == LIT_STRING || type2 == LIT_STRING)
            {
                fprintf(stderr,"can not AND string");
                return canNotDetermine;
            }
            if(compare_type(type1,type2) ==0)
                return LIT_BOOL;
            else
                return canNotDetermine;
            break;
        case expression_or :
            type1 = verify_exp(exp->sons[0],result);
            type1 = verify_exp(exp->sons[1],result);
            if(type1 == LIT_STRING || type2 == LIT_STRING)
            {
                fprintf(stderr,"can not OR string");
                return canNotDetermine;
            }
            if(compare_type(type1,type2) ==0)
                return LIT_BOOL;
            else
                return canNotDetermine;
            break;
        case expression_not :
            type1 = verify_exp(exp->sons[0],result);
            if(type1 != LIT_BOOL)
            {
                fprintf(stderr,"can only negate boolean expression");
                return canNotDetermine;
            }
            else
                return LIT_BOOL;
            break;
    }
}

int verify_func_call(Ast* func_call)
{
    int number_of_parameters=-1;
    int number_of_arguments=-1;
    int result=0;
    int type_par=0;
    Ast* func = func_call->symbol->declaration;
    for(Ast* temp=func->sons[0];temp!=NULL;temp=temp->sons[3])
        number_of_parameters++;
        
    for(Ast* temp=func_call->sons[0];temp!=NULL;temp=temp->sons[3])
        number_of_arguments++;
    if(number_of_parameters > number_of_arguments)
    {
        fprintf(stderr,"Too few arguments for function %s\n",func_call->symbol->name);
        return 1;
    }
    if(number_of_parameters < number_of_arguments)
    {
        fprintf(stderr,"Too many arguments for function %s\n",func_call->symbol->name);
        return 1;
    }
    Ast* par = func->sons[0];
    printf("par second type should be tail = %d\n",par->sons[3]->ast_type);
    printf("arg fist type should be head = %d\n",func_call->sons[0]->sons[3]->ast_type);
    for(Ast* arg=func_call->sons[0]->sons[3];arg!=NULL;arg=arg->sons[3])
    {
        par = par->sons[3];
        type_par = verify_exp(par,&result);
        printf("comparing function call args arg:%d parameter:%d\n",arg->type,type_par);
        result +=compare_type(arg->type,type_par);
    }
    return result;
}

int verify_vector_list_assig(Ast* vect,int *result)
{
    Ast* list_exp_head = vect->sons[1];
    Ast* temp = list_exp_head->sons[3];
    int exp_type;
    for(;temp!=NULL;temp=temp->sons[3])
    {
        exp_type = verify_exp(temp->sons[0],result);
        *result += compare_type(vect->type,exp_type);
    }
}

void verify_program(Ast* Program)
{
    printf("\n********* verification **********\n");
    if(Program->ast_type != program_ast)
    {
         fprintf(stderr, "\n VERIFICATION DID NOT RECEIVE PROGRAM\n");
         fflush(stderr);
         exit(4);
    }
    int result_of_redeclarations = verify_redeclarations(Program->sons[3]);
    int result_of_expresions = verify_expressions(Program->sons[3]);
    printf("\n********* end verification **********\n");
    //if(result_of_redeclarations+result_of_expresions>0)
    //    exit(4);
}