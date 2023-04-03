#include "ast.h"
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#define next_son 3
Ast* Create_ast(int ast_type, int type,Hash_node* symbol, Ast* son0, Ast* son1, Ast* son2, Ast* son3)
{
    Ast* new_ast = (Ast *) malloc(sizeof(Ast));
    new_ast->ast_type=ast_type;
    new_ast->type=type;
    new_ast->symbol=symbol;
    new_ast->sons[0]=son0;
    new_ast->sons[1]=son1;
    new_ast->sons[2]=son2;
    new_ast->sons[3]=son3;
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
    if(head->ast_type != head_list_decl && head->ast_type != head_list_expression && head->ast_type != head_list_ident)
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
    case assignment :
        printf("assignment");
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
    case expression_escreva :
        printf("expression_escreva");
        break;
    case expression_func_call :
        printf("expression_func_call");
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
        fprintf(out, ") {}\n");
        break;
    case literal :
        fprintf(out, "literal");
        break;
    case assignment :
        fprintf(out, "assignment");
        break;
    case head_list_expression :
        decode_and_decompile(ast->sons[next_son],out);
        break;
    case tail_list_expression :
        fprintf(out, " ");
        decode_and_decompile(ast->sons[0],out);
        if(ast->sons[next_son] != NULL)
            decode_and_decompile(ast->sons[next_son],out);
        break;
    case head_list_ident :
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
        if(ast->symbol->name[0]== '%')
        {
            fprintf(out, "%s",ast->symbol->value);
        }
        else
        {
            fprintf(out, "%s",ast->symbol->name);
        }
        
        break;
    case expression_escreva :
        fprintf(out, "expression_escreva");
        break;
    case expression_func_call :
        fprintf(out, "expression_func_call");
        break;
    case expression_vector_pos :
        fprintf(out, "expression_vector_pos");
        break;
    case expression_parentesis :
        fprintf(out, "expression_parentesis");
        break;
    case expression_add :
        fprintf(out, "expression_add");
        break;
    case expression_minus :
        fprintf(out, "expression_minus");
        break;
    case expression_mult :
        fprintf(out, "expression_mult");
        break;
    case expression_divison :
        fprintf(out, "expression_divison");
        break;
    case expression_gt :
        fprintf(out, "expression_gt");
        break;
    case expression_ge :
        fprintf(out, "expression_ge");
        break;
    case expression_lt :
        fprintf(out, "expression_lt");
        break;
    case expression_le :
        fprintf(out, "expression_le");
        break;
    case expression_dif :
        fprintf(out, "expression_dif");
        break;
    case expression_eq :
        fprintf(out, "expression_eq");
        break;
    case expression_and :
        fprintf(out, "expression_and");
        break;
    case expression_or :
        fprintf(out, "expression_or");
        break;
    case expression_not :
        fprintf(out, "expression_not");
        break;
    default:
        fprintf(out, "uncoded_type");
        break;
    }
}

void print_program_ast(Ast* program)
{
    decode_and_print_ast_type(program);
    int i=0;
    for(i=0;i<4;i++)
    {
        if(program->sons[i] != NULL)
        print_program_ast(program->sons[i]);
    }
    
}

void write_ast_to_program(Ast* program,FILE* out)
{
    if(out == NULL)
        return;
    fprintf(out, "// program \n");
    decode_and_decompile(program->sons[next_son],out);
}

