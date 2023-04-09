
#include "ast.h"
#include <string.h>
#include "y.tab.h"

#define isEntrada -2
#define canNotDetermine -10
int verify_exp(Ast* exp, int* result);
int verify_func_call(Ast* func_call);
void verify_vector_list_decl(Ast* vect,int *result);
void verify_cmd(Ast* cmd,int *result, int function_type);
void verify_bloc(Ast* bloc,int *result, int function_type);
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
    Ast* temp_f;
    for(number_of_declarations =0;temp!=NULL;temp=temp->sons[3])
    {
        number_of_declarations++;
        if(temp->sons[0]->ast_type == function_decl)
        {
            if(temp->sons[0] == NULL)
            {
                fprintf(stderr,"FIRST OF TAIL OF LIST_DECL IS NULL");
                fflush(stderr);
                return 4;
            }
            if(temp->sons[0]->sons[0] == NULL)
            {
                fprintf(stderr,"LIST_IDENT OF FUNCTION IS NULL");
                fflush(stderr);
                return 4;
            }
            if(temp->sons[0]->sons[0]->sons[3] !=NULL)
            {
                for(temp_f=temp->sons[0]->sons[0]->sons[3];temp_f!=NULL;temp_f=temp_f->sons[3])
                number_of_declarations++;
            }
            
        }
    }
        
    char **names_found = (char **) malloc(sizeof(char **)*number_of_declarations);
    printf("number of declaration: %d\n",number_of_declarations);
    int len_names_found =0;
    int current_name_found=0;
    int has_found=0;
    int brk =0;
    Ast* declaration;
    Ast* declaration_f;
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

        if(declaration->ast_type == function_decl)
        {
            printf("verifying paramter names\n");
            if(declaration->sons[0] == NULL)
                printf("FUNCTION FIRST IS NULL\n");
            fflush(stdout);
            declaration_f = declaration->sons[0];
            if(declaration_f->sons[3] != NULL)
            {
                for(temp_f=declaration_f->sons[3];temp_f!=NULL;temp_f=temp_f->sons[3])
                {
                    if(temp_f->sons[0] == NULL && temp_f->ast_type != tail_list_ident )
                        printf("temp_f FIRST IS NULL\n");
                    printf("temp_f ast type = %d\n",temp_f->ast_type);
                    fflush(stdout);
                    printf("verifying paramter name = %s\n",temp_f->symbol->name);
                    fflush(stdout);
                    has_found=0;
                    for(current_name_found=0;current_name_found<len_names_found;current_name_found++)
                    {
                        if(strcmp(names_found[current_name_found],temp_f->symbol->name) ==0)
                        {
                            has_found =1;
                            fprintf(stderr, "\n name %s is being redeclared as a function paramter!\n",names_found[current_name_found]);
                            result =4;
                        }
                    }
                    if(has_found == 0)
                    {
                        printf("did not found");
                        fflush(stdout);
                        if(len_names_found >= number_of_declarations)
                        {
                            fprintf(stderr, "\n IS ADDING MORE NAMES THAN NUMBER OF DECLARATIONS!\n");
                            fflush(stderr);
                            exit(4);
                        }
                        names_found[len_names_found] = temp_f->symbol->name;
                        len_names_found++;
                    }
                    
                }
                
            }
            else
                printf("empty paramter list\n");
            
        }
    }
    return result;
}

int compare_type(int type1,int type2)
{
    if(type1 == isEntrada || type1 == isEntrada)
        return 0;
    if(type1 == KW_INTE || type1 == KW_CARA)
    {
        if(type2 == KW_INTE || type2 == KW_CARA)
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
    int temp_type=0;
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
        switch (decl->ast_type)
        {
        case var_decl:
            if(decl->sons[0]!=NULL && decl->sons[0] !=NULL)
            {
                if(decl->sons[0]!=NULL && decl->sons[0]->symbol!=NULL)
                {
                    if(decl->sons[0]->symbol->symbol_type==0)
                    {
                        result +=compare_type(decl->type,verify_exp(decl->sons[0],&result));
                    }
                    else
                    {
                        fprintf(stderr,"\n %s is being declared with something diferent than a literal!",decl->symbol->name==NULL? "NULL" : decl->symbol->name);
                        result +=4;
                    }
                }
                else
                {
                    fprintf(stderr,"ERROR ON var_decl");
                    result +=4;
                }
            }
            
            break;
        case vector_decl:
            verify_vector_list_decl(decl,&result);
            break;
        case function_decl:
            if(decl->sons[1] ==NULL)
            {
                fprintf(stderr,"second of function(bloc) is NULL");
                fflush(stderr);
                return 4;
            }
            verify_bloc(decl->sons[1],&result,decl->type);
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
                //if(exp->symbol->symbol_type==0)
                //    printf("eh literal type: %d\n",exp->symbol->type);
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
                    if(exp->sons[0] == NULL)
                    {
                        fprintf(stderr,"FIRST OF expression_vector_pos IS NULL");
                        fflush(stderr);
                        return canNotDetermine;
                    }
                    *result += compare_type(KW_INTE,verify_exp(exp->sons[0],result));
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
            type2 = verify_exp(exp->sons[1],result);
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
            type2 = verify_exp(exp->sons[1],result);
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
            type2 = verify_exp(exp->sons[1],result);
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
            type2 = verify_exp(exp->sons[1],result);
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
            type2 = verify_exp(exp->sons[1],result);
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
            type2 = verify_exp(exp->sons[1],result);
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
            type2 = verify_exp(exp->sons[1],result);
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
            type2 = verify_exp(exp->sons[1],result);
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
            type2 = verify_exp(exp->sons[1],result);
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
            type2 = verify_exp(exp->sons[1],result);
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
            type2 = verify_exp(exp->sons[1],result);
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
                fprintf(stderr,"can only negate boolean expression\n");
                return canNotDetermine;
            }
            else
            {
                return LIT_BOOL;
            }
                
            break;
    }
}

int verify_func_call(Ast* func_call)
{
    int number_of_parameters=-1;
    int number_of_arguments=-1;
    int result=0;
    int type_arg=0;
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
    //printf("par second ast_type should be tail = %d\n",par->sons[3]->ast_type);
    //printf("arg second ast_type should be head = %d\n",func_call->sons[0]->sons[3]->ast_type);
    //printf("par second type should be not minus = %d\n",par->sons[3]->type);
    //printf("arg second type should be minus maybe = %d\n",func_call->sons[0]->sons[3]->type);
    for(Ast* arg=func_call->sons[0]->sons[3];arg!=NULL;arg=arg->sons[3])
    {
        par = par->sons[3];
        type_arg = verify_exp(arg->sons[0],&result);
        //printf("comparing function call args arg:%d parameter:%d\n",type_arg,par->type);
        result +=compare_type(par->type,type_arg);
    }
    return result;
}

void verify_vector_list_decl(Ast* vect,int *result)
{
    if(vect->sons[0]==NULL) 
    {
        fprintf(stderr,"\n vect sons[0] eh NULL");
        return;
    }
    if(vect->sons[0]->symbol==NULL) 
    {
        if(vect->sons[0]->ast_type != expression_var)
        {
            fprintf(stderr,"\n vector");
            if(vect->symbol!=NULL && vect->symbol->name != NULL) fprintf(stderr," %s",vect->symbol->name);
            fprintf(stderr," vector size definition MUST be A IMEDIATE INTEGER");
            *result +=4;
            return;
        }
        else
        {
            fprintf(stderr,"\n vect vect->sons[0]->symbol eh NULL");
            return;
        }
        
        
    }
    if( vect->sons[0]->ast_type != expression_var ||  vect->sons[0]->symbol->symbol_type!=0 || vect->sons[0]->symbol->type!=259)
    {
        *result +=4;
        fprintf(stderr,"\n vector size definition MUST be A IMEDIATE INTEGER");
        return;
    }
    int vec_size = atoi(vect->sons[0]->symbol->value);
    int vec_size_count =0;
    Ast* list_exp_head = vect->sons[1];
    Ast* temp = list_exp_head->sons[3];
    int exp_type;
    for(;temp!=NULL;temp=temp->sons[3])
    {   
        vec_size_count++;
        if(temp->sons[0]->ast_type!= expression_var ||( temp->sons[0]->symbol != NULL &&temp->sons[0]->symbol->symbol_type!=0 ))
        {
            fprintf(stderr,"devia printar");

            if(vect->symbol !=NULL)
                fprintf(stderr,"\n vector %s is being declared with something different than a literal!",vect->symbol->name);
            else 
                fprintf(stderr,"\n vector is being declared with something different than a literal!");
            *result +=4;
        }
        exp_type = verify_exp(temp->sons[0],result);
        *result += compare_type(vect->type,exp_type);
    }
    if(vec_size_count>vec_size)
    {
        fprintf(stderr,"\n list to assign to vector(len:%d) is bigger than vector size(len:%d)",vec_size_count,vec_size);
        *result +=4;
    }

}

void verify_bloc(Ast* bloc,int *result, int function_type)
{
    if(bloc->sons[0] == NULL)
    {
        fprintf(stderr,"first of bloc(list of commands) is NULL ");
        fflush(stderr);
        return;
    }
    for(Ast* temp=bloc->sons[0];temp!=NULL;temp=temp->sons[3])
    {
        if(temp->sons[0] == NULL)
        {
             if(temp->ast_type!=head_list_cmd && temp->ast_type!=empty_cmd) 
            {
                fprintf(stderr,"FIRST OF CMD that is not HEAD OR EMPTY CMD is NULL \n");
                fflush(stderr);
                return;
            }
        }
        else
        {
            verify_cmd(temp->sons[0],result,function_type);
        }
            
    }
}

void verify_cmd(Ast* cmd,int *result, int function_type)
{
    Ast* temp;
    int temp_res;
    //printf("cmd->ast_type = %d\n",cmd->ast_type);
    //fflush(stdout);
    switch (cmd->ast_type)
    {
    case escreva_cmd :
        if(cmd->sons[0] == NULL)
        {
            fprintf(stderr,"FIRST THE ESCREVA IS NULL\n");
            fflush(stderr);
            return;
        }
        for(temp=cmd->sons[0];temp!=NULL;temp=temp->sons[3])
        {
            if(temp->ast_type != tail_list_expression && temp->ast_type != head_list_expression)
            {
                fprintf(stderr,"THERE SHOULD NOT SOMETHING DIFERENT THAN A tail_list_expression HERE\n");
                fflush(stderr);
                return;
            }
            if(temp->sons[0] !=NULL)
            {
                temp_res = verify_exp(temp->sons[0],result);
                if(temp_res == canNotDetermine)
                    *result +=1; 
            }
        }
        break;
    case retorne_cmd :
        if(cmd->sons[0] == NULL)
        {
            fprintf(stderr,"FIRST THE ESCREVA IS NULL\n");
            fflush(stderr);
            return;
        }
        temp_res = verify_exp(cmd->sons[0],result);
        if(compare_type(function_type,temp_res) !=0)
            *result +=1;
        break;
    case head_list_cmd :
        fprintf(stderr,"THERE SHOULD NOT BE A HEAD_LIST_CMD HERE\n");
        fflush(stderr);
        return;
        break;
    case tail_list_cmd :
        fprintf(stderr,"THERE SHOULD NOT BE A tail_list_cmd HERE\n");
        fflush(stderr);
        return;
        break;
    case block_dec :
        verify_bloc(cmd,result,function_type);
        break;
    case empty_cmd :
        break;
    case enquanto_cmd :
        if(cmd->sons[0] == NULL)
        {
            fprintf(stderr,"FIRST THE ENQUANTO IS NULL\n");
            fflush(stderr);
            return;
        }
        if(cmd->sons[2] == NULL)
        {
            fprintf(stderr,"THIRD THE ENQUANTO IS NULL\n");
            fflush(stderr);
            return;
        }
        verify_cmd(cmd->sons[0],result,function_type);
        temp_res = verify_exp(cmd->sons[2],result);
        if(temp_res != LIT_BOOL)
        {
            fprintf(stderr,"se expression should be LITBOOL\n");
            *result +=1;
        }
        break;
    case entaum_cmd :
        if(cmd->sons[0] == NULL)
        {
            fprintf(stderr,"FIRST THE entaum_cmd IS NULL\n");
            fflush(stderr);
            return;
        }
        if(cmd->sons[2] == NULL)
        {
            fprintf(stderr,"THIRD THE entaum_cmd IS NULL\n");
            fflush(stderr);
            return;
        }
        verify_cmd(cmd->sons[0],result,function_type);
        temp_res = verify_exp(cmd->sons[2],result);
        if(temp_res != LIT_BOOL)
        {
            fprintf(stderr,"se expression should be LITBOOL\n");
            *result +=1;
        }
        break;
    case senaum_cmd :
        if(cmd->sons[0] == NULL)
        {
            fprintf(stderr,"FIRST THE senaum_cmd IS NULL\n");
            fflush(stderr);
            return;
        }
        if(cmd->sons[1] == NULL)
        {
            fprintf(stderr,"SECOND THE senaum_cmd IS NULL\n");
            fflush(stderr);
            return;
        }
        if(cmd->sons[2] == NULL)
        {
            fprintf(stderr,"THIRD THE senaum_cmd IS NULL\n");
            fflush(stderr);
            return;
        }
        verify_cmd(cmd->sons[0],result,function_type);
        verify_cmd(cmd->sons[1],result,function_type);
        temp_res = verify_exp(cmd->sons[2],result);
        if(temp_res != LIT_BOOL)
        {
            fprintf(stderr,"se expression should be LITBOOL\n");
            *result +=1;
        }
        break; 
    default:
        break;
    }
    
}

int verify_program(Ast* Program)
{
    int result =0;
    printf("\n********* verification **********\n");
    if(Program->ast_type != program_ast)
    {
         fprintf(stderr, "\n VERIFICATION DID NOT RECEIVE PROGRAM\n");
         fflush(stderr);
         exit(4);
    }
    int result_of_redeclarations = verify_redeclarations(Program->sons[3]);
    int result_of_expresions = verify_expressions(Program->sons[3]);
    
    if(result_of_redeclarations+result_of_expresions>0)
    {
        fprintf(stderr,"\nFOUND SEMANTIC ERRORS\n");
        fflush(stderr);
        result =  4;
    }
    printf("\n********* end verification **********\n");
    return result;
}