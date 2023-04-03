
%{
#include "hash.h"
#include "ast.h"
int yyerror(const char *); 
#define YYERROR_VERBOSE

%}

%union 
{
    Hash_node *symbol;
    Ast *ast;
    int type;
} 

%token KW_CARA 
%token KW_INTE
%token KW_REAL

%token KW_SE 
%token KW_ENTAUM 
%token KW_SENAUM
%token KW_ENQUANTO
%token KW_ENTRADA 
%token KW_ESCREVA
%token KW_RETORNE 

%token OPERATOR_LE 
%token OPERATOR_GE 
%token OPERATOR_EQ   
%token OPERATOR_DIF 

%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INTEIRO
%token<symbol> LIT_FLOAT
%token<symbol> LIT_CHAR 
%token<symbol> LIT_STRING 
%token TOKEN_ERROR 


%type<ast> var_decl;
%type<ast> function_decl;
%type<ast> list_decl;
%type<ast> program;
%type<type> type_key_word
%type<symbol> type_literal
%type<ast> expression
%type<ast> list_expression
%type<ast> ident_list
%left '+' '-'
%left '*' '/'
%left '&' '|' '~'
%left OPERATOR_GE OPERATOR_LE OPERATOR_EQ OPERATOR_DIF '<' '>' 
%left KW_CARA KW_INTE KW_REAL

%%
program: list_decl {fflush(stdout);$$ = Create_ast(program_ast,-1,NULL,NULL,NULL,NULL,$1);print_program_ast($$);write_ast_to_program($$,yyout);}
    ; 
list_decl: list_decl var_decl   {$$ = Add_to_tail($1,Create_ast(tail_list_decl,-1,NULL,$2,NULL,NULL,NULL));}
    | list_decl function_decl   {$$ = Add_to_tail($1,Create_ast(tail_list_decl,-1,NULL,$2,NULL,NULL,NULL));}
    |   {$$ = Create_ast(head_list_decl,-1,NULL,NULL,NULL,NULL,NULL);}
    ;

list_commands: list_commands ';' command  
    | command 
    ;
command: assingment 
    |   command_escreva 
    |   block_decl  
    |   command_senaum  
    |   command_enquanto    
    |   command_return    
    |      
    ;

assingment: TK_IDENTIFIER '=' expression
    |   TK_IDENTIFIER '[' expression ']' '=' expression
    ;

command_escreva: KW_ESCREVA list_expression 
    ;
command_senaum: KW_ENTAUM command KW_SE '(' expression ')'
    |   KW_ENTAUM command KW_SENAUM command  KW_SE'(' expression ')'
    ;
command_enquanto: command KW_ENQUANTO '(' expression ')'
    ;
command_return: KW_RETORNE expression
    ;
var_decl: type_key_word TK_IDENTIFIER '=' expression ';'  {$$ = Create_ast(var_decl,$1,$2,$4,NULL,NULL,NULL);}
    | type_key_word TK_IDENTIFIER '[' expression ']' list_expression  ';' {$$ = Create_ast(vector_decl,$1,$2,$4,$6,NULL,NULL);}
    ;

function_decl: type_key_word TK_IDENTIFIER '(' ident_list ')' block_decl {$$ = Create_ast(function_decl,$1,$2,$4,NULL,NULL,NULL);}
    ;
block_decl: '{' list_commands '}' 
    ;

list_expression: list_expression expression {$$ = Add_to_tail($1,Create_ast(tail_list_expression,-1,NULL,$2,NULL,NULL,NULL));}
    |   {$$ = Create_ast(head_list_expression,-1,NULL,NULL,NULL,NULL,NULL);}
    ;

expression: type_literal {$$ = Create_ast(expression_var,$1->type,$1,NULL,NULL,NULL,NULL);}
    |   TK_IDENTIFIER {$$ = Create_ast(expression_var,-1,$1,NULL,NULL,NULL,NULL);}
    |   KW_ENTRADA  {$$ = Create_ast(expression_escreva,-1,NULL,NULL,NULL,NULL,NULL);}
    |   TK_IDENTIFIER '(' list_expression ')' {$$ = Create_ast(expression_func_call,-1,$1,NULL,NULL,NULL,NULL);}
    |   TK_IDENTIFIER '[' expression ']'    {$$ = Create_ast(expression_vector_pos,-1,$1,NULL,NULL,NULL,NULL);}
    |   '(' expression ')'  {$$ = Create_ast(expression_parentesis,-1,NULL,$2,NULL,NULL,NULL);}
    |   expression '+' expression   {$$ = Create_ast(expression_add,-1,NULL,$1,$3,NULL,NULL);}
    |   expression '-' expression   {$$ = Create_ast(expression_minus,-1,NULL,$1,$3,NULL,NULL);}
    |   expression '*' expression   {$$ = Create_ast(expression_mult,-1,NULL,$1,$3,NULL,NULL);}
    |   expression '/' expression   {$$ = Create_ast(expression_divison,-1,NULL,$1,$3,NULL,NULL);}
    |   expression '>' expression   {$$ = Create_ast(expression_gt,-1,NULL,$1,$3,NULL,NULL);}
    |   expression OPERATOR_GE expression   {$$ = Create_ast(expression_ge,-1,NULL,$1,$3,NULL,NULL);}
    |   expression '<' expression   {$$ = Create_ast(expression_lt,-1,NULL,$1,$3,NULL,NULL);}
    |   expression OPERATOR_LE expression   {$$ = Create_ast(expression_le,-1,NULL,$1,$3,NULL,NULL);}
    |   expression OPERATOR_DIF expression  {$$ = Create_ast(expression_dif,-1,NULL,$1,$3,NULL,NULL);}
    |   expression OPERATOR_EQ expression   {$$ = Create_ast(expression_eq,-1,NULL,$1,$3,NULL,NULL);}
    |   expression '&' expression   {$$ = Create_ast(expression_and,-1,NULL,$1,$3,NULL,NULL);}
    |   expression '|' expression   {$$ = Create_ast(expression_or,-1,NULL,$1,$3,NULL,NULL);}
    |   '~' expression  {$$ = Create_ast(expression_not,-1,NULL,$2,NULL,NULL,NULL);}
    ;
type_key_word: KW_CARA {$$ = KW_CARA;}
    | KW_INTE {$$ = KW_INTE;}
    | KW_REAL {$$ = KW_REAL;}
    ;

type_literal: LIT_CHAR {$$ = $1;}
    | LIT_FLOAT {$$ = $1;}
    | LIT_INTEIRO {$$ = $1;}
    | LIT_STRING {$$ = $1;}
    ;

ident_list: ident_list type_key_word TK_IDENTIFIER  {$$ = Add_to_tail($1,Create_ast(tail_list_ident,$2,$3,NULL,NULL,NULL,NULL));}
    |   {$$ = Create_ast(head_list_ident,-1,NULL,NULL,NULL,NULL,NULL);}
    ;


%%

#include "y.tab.h"
#include "hash.h"
#include "ast.h"

int yywrap(void) {
    running =0;
    return 1;
} 
int yyerror(const char *s) {
    printf("\nahh nao %s linha  = %d\n", s,line_number);
 fprintf(stderr, "\nahh nao %s linha = %d\n", s,line_number);
 return 3;
} 