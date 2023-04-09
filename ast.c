#include "ast.h"
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#define next_son 3

Ast* Create_ast(int ast_type, int type,Hash_node* symbol, Ast* son0, Ast* son1, Ast* son2, Ast* son3)
{
    //printf("erro antes do malloc do create ast\t");
    //fflush(stdout);
    Ast* new_ast = (Ast *) malloc(sizeof(Ast));
    //printf("pos malloc\t");
    //fflush(stdout);
    new_ast->ast_type=ast_type;
    new_ast->type=type;
    new_ast->symbol=symbol;
    new_ast->sons[0]=son0;
    new_ast->sons[1]=son1;
    new_ast->sons[2]=son2;
    new_ast->sons[3]=son3;
    switch (ast_type)
    {
    case program_ast :
    break;
    case head_list_decl :
        break;
    case tail_list_decl :
        break;
    case var_decl :
        symbol->declaration=new_ast;
        symbol->type=type;
        symbol->symbol_type=var_simbol;
        break;
    case vector_decl :
        symbol->declaration=new_ast;
        symbol->type=type;
        symbol->symbol_type=vector_simbol;
        break;
    case function_decl :
        printf("\nfunc name %s",symbol->name);
        symbol->declaration=new_ast;
        symbol->type=type;
        symbol->symbol_type=function_simbol;
        break;
    case head_list_expression :
        break;
    case tail_list_expression :
        break;
    case head_list_ident :
        break;
    case tail_list_ident :
        symbol->symbol_type=parameter_simbol;
        break;
    case expression_var :
        break;
    case expression_entrada :
        break;
    case expression_func_call :
        if(symbol->declaration != NULL)
        {
            new_ast->type=symbol->type;
        }
        break;
    case expression_vector_pos :
        break;
    case expression_parentesis :
        break;
    case expression_add :
        break;
    case expression_minus :
        break;
    case expression_mult :
        break;
    case expression_divison :
        break;
    case expression_gt :
        break;
    case expression_ge :
        break;
    case expression_lt :
        break;
    case expression_le :
        break;
    case expression_dif :
        break;
    case expression_eq :
        break;
    case expression_and :
        break;
    case expression_or :
        break;
    case expression_not :
        break;
    case var_assignment :
        break;
    case vec_assignment :
        break;
    case escreva_cmd :
        break;
    case retorne_cmd :
        break;
    case head_list_cmd :
        break;
    case tail_list_cmd :
        
        break;
    case block_dec :
        break;
    case empty_cmd :
        break;
    case enquanto_cmd :
        break;
    case entaum_cmd :
        break;
    case senaum_cmd :
        break;
    default:
        break;
    }
    //printf("erro depois do malloc do create ast\n");
    //fflush(stdout);
    return new_ast;
}



Ast* Add_to_tail(Ast* head, Ast* new_son)
{
    if(head == NULL || new_son == NULL)
        {
            printf("\nHEAD AND SONS CAN NOT BE NULL");
            fflush(stdout);
            exit(3);
        }
    if(head->ast_type != head_list_decl && head->ast_type != head_list_expression && head->ast_type != head_list_ident && head->ast_type != head_list_cmd)
    {
        printf("\n head should be of type head_list, head ast_type %d head_list_decl number = %d\n",head->ast_type,head_list_decl);
        fflush(stdout);
        exit(3);
    }
    Ast* temp = head;
    for(;temp->sons[next_son]!=NULL;temp=temp->sons[next_son]){

    }
    temp->sons[next_son]=new_son;
    new_son->parent=temp;
    return head;
}
void print_lit_string(char* string,FILE* out)
{
    int i =0;
    for (i=0;string[i] !='\0';i++)
    {
            switch (string[i])
            {
            case '\a': fprintf(out, "\\a");break;
            case '\b': fprintf(out, "\\b");break;
            case '\e': fprintf(out, "\\e");break;
            case '\f': fprintf(out, "\\f");break;
            case '\n': fprintf(out, "\\n");break;
            case '\r': fprintf(out, "\\r");break;
            case '\t': fprintf(out, "\\t");break;
            case '\v': fprintf(out, "\\v");break;
            case '\\': fprintf(out, "\\");break;
            case '\'': fprintf(out, "\\\'");break;
            case '\"': fprintf(out, "\\\"");break;
            case '?': fprintf(out, "\\?");break;
            default:
                fprintf(out, "%c",string[i]);
                break;
            }
    }
}

void decode_TK_identifier(Hash_node* symbol,FILE* out)
{
     if(symbol->symbol_type==0)
        {
            if(symbol->type == 259 || symbol->type == 260)
                fprintf(out, "%s",symbol->value);
            else if(symbol->type ==258)
                fprintf(out, "\'%s\'",symbol->value);
            else if((symbol->type ==276))
            {
                fprintf(out, "\"");
                print_lit_string(symbol->value,out);
                fprintf(out, "\"");
            }
                
        }
        else
        {
            fprintf(out, "%s",symbol->name);
        }
}

void decode_language_type(int type,FILE* out)
{
    switch (type)
    {
        case 258 :
            fprintf(out,"cara");
            break;
        case 259 :
            fprintf(out,"inte");
            break;
        case 260 :
            fprintf(out,"real");
            break;
        case 276 :
            fprintf(out,"string");
            break;
        case 277 :
            fprintf(out,"bool");
            break;  
        case -10 :
            fprintf(out,"canNotDetermine");
            break;
        default:
            fprintf(out,"0");

    }
   // KW_CARA = 258,
   // KW_INTE = 259,
   // KW_REAL = 260,
}

void decode_and_print_ast_type(Ast* ast)
{
    printf("\n ast_type: ");
    switch (ast->ast_type)
    {
    case program_ast :
    printf("program_ast");
    break;
    case head_list_decl :
        printf("head_list_decl");
        break;
    case tail_list_decl :
        printf("tail_list_decl");
        break;
    case var_decl  :
        printf("var_decl, name: %s",ast->symbol->name);
        break;
    case vector_decl :
        printf("vector_decl, name: %s",ast->symbol->name);
        break;
    case function_decl :
        printf("function_decl, name: %s",ast->symbol->name);
        break;
    case literal :
        printf("literal");
        break;
    case head_list_expression :
        printf("head_list_expression");
        break;
    case tail_list_expression :
        printf("tail_list_expression");
        break;
    case expression_var :
        printf("expression_var, name: %s",ast->symbol->name);
        break;
    case expression_entrada :
        printf("expression_entrada");
        break;
    case expression_func_call :
        printf("expression_func_call, name: %s",ast->symbol->name);
        break;
    case expression_vector_pos :
        printf("expression_vector_pos");
        break;
    case expression_parentesis :
        printf("expression_parentesis");
        break;
    case expression_add :
        printf("expression_add");
        break;
    case expression_minus :
        printf("expression_minus");
        break;
    case expression_mult :
        printf("expression_mult");
        break;
    case expression_divison :
        printf("expression_divison");
        break;
    case expression_gt :
        printf("expression_gt");
        break;
    case expression_ge :
        printf("expression_ge");
        break;
    case expression_lt :
        printf("expression_lt");
        break;
    case expression_le :
        printf("expression_le");
        break;
    case expression_dif :
        printf("expression_dif");
        break;
    case expression_eq :
        printf("expression_eq");
        break;
    case expression_and :
        printf("expression_and");
        break;
    case expression_or :
        printf("expression_or");
        break;
    case expression_not :
        printf("expression_not");
        break;
    case var_assignment :
        printf("var_assignment");
        break;
    case vec_assignment :
        printf("vec_assignment");
        break;
    case escreva_cmd :
        printf("escreva_cmd");
        break;
    case retorne_cmd :
        printf("retorne_cmd");
        break;
    case head_list_cmd :
        printf("head_list_cmd");
        break;
    case tail_list_cmd :
        printf("tail_list_cmd");
        break;
    case block_dec :
        printf("block_dec");
        break;   
    default:
        printf("uncoded_type");
        break;
    }
}



void decode_and_decompile(Ast* ast,FILE* out)
{
    if(ast == NULL)
    {
        printf("AST NULL");
        fflush(stdout);
        exit(3);
    }
    switch (ast->ast_type)
    {
    case program_ast :
    fprintf(out, "program_ast");
    decode_and_decompile(ast->sons[next_son],out);
    break;
    case head_list_decl :
        decode_and_decompile(ast->sons[next_son],out);
        break;
    case tail_list_decl :
        
        decode_and_decompile(ast->sons[0],out);
        if(ast->sons[next_son] != NULL)
            decode_and_decompile(ast->sons[next_son],out);
        break;
    case var_decl  :
        decode_language_type(ast->type,out);
        fprintf(out, " %s = ",ast->symbol->name);
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " ;\n");
        break;
    case vector_decl :
        decode_language_type(ast->type,out);
        fprintf(out, " %s [ ",ast->symbol->name);
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " ] ");
        decode_and_decompile(ast->sons[1],out);
         fprintf(out, " ;\n");
        break;
    case function_decl :
        decode_language_type(ast->type,out);
        fprintf(out, " %s (",ast->symbol->name);
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, ")");
        if(ast->sons[1] == NULL)
            fprintf(out, "function_decl 1 is NULL");
        decode_and_decompile(ast->sons[1],out);
        break;
    case head_list_expression :
        if(ast->sons[next_son] != NULL)
            decode_and_decompile(ast->sons[next_son],out);
        break;
    case tail_list_expression :
        fprintf(out, " ");
        decode_and_decompile(ast->sons[0],out);
        if(ast->sons[next_son] != NULL)
            decode_and_decompile(ast->sons[next_son],out);
        break;
    case head_list_ident :
        if(ast->sons[next_son] != NULL)
            decode_and_decompile(ast->sons[next_son],out);
        break;
    case tail_list_ident :
        fprintf(out, " ");
        decode_language_type(ast->type,out);
        fprintf(out, " %s",ast->symbol->name);
        if(ast->sons[next_son] != NULL)
            decode_and_decompile(ast->sons[next_son],out);
        break;
    case expression_var :
        decode_TK_identifier(ast->symbol,out);        
        break;
    case expression_entrada :
        fprintf(out, "entrada");
        break;
    case expression_func_call :
        fprintf(out, "%s (",ast->symbol->name);
        decode_and_decompile(ast->sons[0],out);
        fprintf(out,")");
        break;
    case expression_vector_pos :
        fprintf(out, "%s[",ast->symbol->name);
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, "]");
        break;
    case expression_parentesis :
        fprintf(out, "(");
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, ")");
        break;
    case expression_add :
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " + ");
        decode_and_decompile(ast->sons[1],out);
        break;
    case expression_minus :
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " - ");
        decode_and_decompile(ast->sons[1],out);
        break;
    case expression_mult :
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " * ");
        decode_and_decompile(ast->sons[1],out);
        break;
    case expression_divison :
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " / ");
        decode_and_decompile(ast->sons[1],out);
        break;
    case expression_gt :
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " > ");
        decode_and_decompile(ast->sons[1],out);
        break;
    case expression_ge :
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " >= ");
        decode_and_decompile(ast->sons[1],out);
        break;
    case expression_lt :
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " < ");
        decode_and_decompile(ast->sons[1],out);
        break;
    case expression_le :
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " <= ");
        decode_and_decompile(ast->sons[1],out);
        break;
    case expression_dif :
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " != ");
        decode_and_decompile(ast->sons[1],out);
        break;
    case expression_eq :
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " == ");
        decode_and_decompile(ast->sons[1],out);
        break;
    case expression_and :
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " & ");
        decode_and_decompile(ast->sons[1],out);
        break;
    case expression_or :
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " | ");
        decode_and_decompile(ast->sons[1],out);
        break;
    case expression_not :
        fprintf(out, " ~ ");
        decode_and_decompile(ast->sons[0],out);
        break;
    case var_assignment :
        fprintf(out, " %s  = ",ast->symbol->name);
        decode_and_decompile(ast->sons[0],out);
        break;
    case vec_assignment :
        fprintf(out, " %s [ ",ast->symbol->name);
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " ] = ");
        decode_and_decompile(ast->sons[1],out);
        break;
    case escreva_cmd :
        fprintf(out, " escreva ");
        decode_and_decompile(ast->sons[0],out);
        break;
    case retorne_cmd :
        fprintf(out, " retorne ");
        decode_and_decompile(ast->sons[0],out);
        break;
    case head_list_cmd :
        if(ast->sons[next_son] == NULL)
            fprintf(out, "HEAD NEXT IS NULL");
        decode_and_decompile(ast->sons[next_son],out);
        break;
    case tail_list_cmd :
        if(ast->sons[0] == NULL)
            fprintf(out, "tail_list_cmd first IS NULL");
        fprintf(out, "\t");
        decode_and_decompile(ast->sons[0],out);
        if(ast->sons[next_son] != NULL)
        {
            fprintf(out, " ;\n");
            decode_and_decompile(ast->sons[next_son],out);
        }
        break;
    case block_dec :
        fprintf(out, "\n{\n");
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, "\n}\n");
        break;
    case empty_cmd :
        break;
    case enquanto_cmd :
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " enquanto ");
        fprintf(out, " ( ");
        decode_and_decompile(ast->sons[2],out);
        fprintf(out, " ) ");
        break;
    case entaum_cmd :
        fprintf(out, " entaum ");
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " se ");
        fprintf(out, " ( ");
        decode_and_decompile(ast->sons[2],out);
        fprintf(out, " ) ");
        break;
    case senaum_cmd :
        fprintf(out, "entaum ");
        decode_and_decompile(ast->sons[0],out);
        fprintf(out, " senaum ");
        decode_and_decompile(ast->sons[1],out);
        fprintf(out, " se ");
        fprintf(out, " ( ");
        decode_and_decompile(ast->sons[2],out);
        fprintf(out, " ) ");
        break;
    default:
        fprintf(out, "uncoded_type");
        break;
    }
}

void print_program_ast(Ast* program,int level,int son_number)
{
    level++;   
    decode_and_print_ast_type(program);
    printf("\tlevel = %d",level);
    printf("\t son_number = %d",son_number);
    int i=0;
    for(i=0;i<4;i++)
    {
        if(program->sons[i] != NULL)
        {
            print_program_ast(program->sons[i],level,i);
        }
        
    }
    
}

void write_ast_to_program(Ast* program,FILE* out)
{
    if(out == NULL)
        return;
    fprintf(out, "// program \n");
    decode_and_decompile(program->sons[next_son],out);
}

