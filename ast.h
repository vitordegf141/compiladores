

#ifndef HEADER_AST
#define HEADER_AST


#define program_ast 1
#define head_list_decl 2
#define tail_list_decl 3
#define var_decl  4
#define vector_decl 5
#define function_decl 6
#define literal 7
#define head_list_expression 9
#define tail_list_expression 10
#define head_list_ident 11
#define tail_list_ident 12
#define expression_var 100
#define expression_entrada 101
#define expression_func_call 102
#define expression_vector_pos 103
#define expression_parentesis 104
#define expression_add 105
#define expression_minus 106
#define expression_mult 107
#define expression_divison 108
#define expression_gt 110
#define expression_ge 111
#define expression_lt 112
#define expression_le 113
#define expression_dif 114
#define expression_eq 115
#define expression_and 116
#define expression_or 117
#define expression_not 118
#define var_assignment 200
#define vec_assignment 201
#define escreva_cmd 202
#define retorne_cmd 203
#define head_list_cmd 204
#define tail_list_cmd 205
#define block_dec 206
#define empty_cmd 207
#define enquanto_cmd 208
#define entaum_cmd 209
#define senaum_cmd 210

#include "hash.h"

typedef struct Astnode
{
    int ast_type;
    int type;
    Hash_node* symbol;
    struct Astnode *parent;
    struct Astnode *sons[4];
} Ast;


Ast* Create_ast(int ast_type, int type,Hash_node* symbol, Ast* son0, Ast* son1, Ast* son2, Ast* son3);
Ast* Add_to_tail(Ast* head, Ast* new_son);
void print_program_ast(Ast* program);
void write_ast_to_program(Ast* program,FILE* out);
#endif