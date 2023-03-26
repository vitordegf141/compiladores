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
program: list_decl {printf("\nidentificou program");}
    ; 
list_decl: list_decl var_decl   {printf("\nidentificou list_decl var_decl");}
    | list_decl function_decl   {printf("\nidentificou list_decl function_decl");}
    |   {printf("\nidentificou list_decl empty");}
    ;

list_commands: list_commands ';' command  {printf("\nidentificou list_commands command");}
    | command {printf("\nidentificou single command in list_commands");}
    ;
command: assingment {printf("\nidentificou assingment command");}
    |   command_escreva {printf("\nidentificou command_escreva command");}
    |   block_decl  {printf("\nidentificou block_decl command");}
    |   command_senaum  {printf("\nidentificou command_senaum command");}
    |   command_enquanto    {printf("\nidentificou command_enquanto command");}
    |   command_return    {printf("\nidentificou command_return command");}
    |      {printf("\nidentificou vazio command");}
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
var_decl: type_key_word TK_IDENTIFIER '=' expression ';'  {printf("\nidentificou init variavel");}
    | vetor_decl ';' {printf("\nidentificou decl vetor");}
    ;

function_decl: type_key_word TK_IDENTIFIER '(' ident_list ')' block_decl {printf("\nidentificou function_decl");}
    ;
block_decl: '{' list_commands '}' 
    ;

vetor_decl: type_key_word TK_IDENTIFIER '[' expression ']' {printf("\nidentificou just decl vetor");}
    | type_key_word TK_IDENTIFIER '[' expression ']' list_expression {printf("\nidentificou decl init vetor");}
    ;

list_expression: list_expression expression {printf("\nidentificou list_expression expression ");}
    | expression {printf("\nidentificou expression");}
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
type_key_word: KW_CARA  {printf("\nidentificou KW_CARA");}
    | KW_INTE   {printf("\nidentificou KW_INTE");}
    | KW_REAL   {printf("\nidentificou KW_REAL");}
    ;

type_literal: LIT_CHAR {printf("\nidentificou LIT_CHAR");}
    | LIT_FLOAT {printf("\nidentificou LIT_FLOAT");}
    | LIT_INTEIRO {printf("\nidentificou LIT_INTEIRO");}
    | LIT_STRING {printf("\nidentificou LIT_STRING");}
    ;

ident_list: ident_list ident_list {printf("\nidentificou ident_list ident_list");}
    | type_key_word TK_IDENTIFIER {printf("\nidentificou type_key_word TK_IDENTIFIER TK_IDENTIFIER");}
    | {printf("\nidentificou ident_list empty");}
    ;


%%
#include "y.tab.h"
int yywrap(void) {
    running =0;
    return 1;
    //assingment: KW_CARA '=' {printf("identificou assingment, %d",$1);}
} 
int yyerror(const char *s) {
    printf("ahh pqp %s\n", s);
 fprintf(stderr, "ahh pqp %s\n", s);
 return 3;
} 