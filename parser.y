%{
int yyerror(const char *); 
#define YYERROR_VERBOSE
%}


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

%token TK_IDENTIFIER

%token LIT_INTEIRO
%token LIT_FLOAT  
%token LIT_CHAR 
%token LIT_STRING 

%token TOKEN_ERROR 

%left '+' '-'
%left '*' '/'
%%
program: list_decl 
    ; 
list_decl: list_decl var_decl   
    | list_decl function_decl   
    |   
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
var_decl: type_key_word TK_IDENTIFIER '=' expression ';'  
    | vetor_decl ';' 
    ;

function_decl: type_key_word TK_IDENTIFIER '(' ident_list ')' block_decl 
    ;
block_decl: '{' list_commands '}' 
    ;

vetor_decl: type_key_word TK_IDENTIFIER '[' expression ']' 
    | type_key_word TK_IDENTIFIER '[' expression ']' list_expression 
    ;

list_expression: list_expression expression 
    | expression 
    ;

expression: type_literal
    |   TK_IDENTIFIER
    |   KW_ENTRADA
    |   TK_IDENTIFIER '(' list_expression ')'
    |   TK_IDENTIFIER '[' expression ']'
    |   '(' expression ')'
    |   expression '+' expression
    |   expression '-' expression
    |   expression '*' expression
    |   expression '/' expression
    |   expression '>' expression
    |   expression OPERATOR_GE expression
    |   expression '<' expression
    |   expression OPERATOR_LE expression
    |   expression OPERATOR_DIF expression
    |   expression OPERATOR_EQ expression
    |   expression '&' expression
    |   expression '|' expression
    |   expression '~' expression
    ;
type_key_word: KW_CARA  
    | KW_INTE   
    | KW_REAL   
    ;

type_literal: LIT_CHAR 
    | LIT_FLOAT 
    | LIT_INTEIRO 
    | LIT_STRING 
    ;

ident_list: ident_list ident_list 
    | type_key_word TK_IDENTIFIER 
    | 
    ;


%%
#include "y.tab.h"
int yywrap(void) {
    running =0;
    return 1;
} 
int yyerror(const char *s) {
    printf("ahh pqp %s\n", s);
 fprintf(stderr, "ahh pqp %s\n", s);
 return 3;
} 