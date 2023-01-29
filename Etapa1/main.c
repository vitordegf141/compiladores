
#include <stdio.h>
#include "tokens.h"




int decode(int token)
{
    switch (token)
    {
    case KW_CARA:
        printf("#encontrou KW_CARA %d",KW_CARA);
        break;
    case KW_INTE:
        printf("#encontrou KW_INTE %d",KW_INTE);
        break;
    case KW_REAL:
        printf("#encontrou KW_REAL %d",KW_REAL);
        break;
    case KW_SE:
        printf("#encontrou KW_SE %d",KW_SE);
        break;
    case KW_ENTAUM:
        printf("#encontrou KW_ENTAUM %d",KW_ENTAUM);
        break;
    case KW_SENAUM:
        printf("#encontrou KW_SENAUM %d",KW_CARA);
        break;
    case KW_ENQUANTO:
        printf("#encontrou KW_ENQUANTO %d", KW_ENQUANTO);
        break;
    case KW_ENTRADA:
        printf("#encontrou KW_ENTRADA %d",KW_ENTRADA);
        break;
    case KW_ESCREVA:
        printf("#encontrou KW_ESCREVA %d",KW_ESCREVA);
        break;
    case KW_RETORNE:
        printf("#encontrou KW_RETORNE %d",KW_RETORNE);
        break;
    case OPERATOR_LE:
        printf("#encontrou OPERATOR_LE %d",OPERATOR_LE);
        break;
    case OPERATOR_GE:
        printf("#encontrou OPERATOR_GE %d",OPERATOR_GE);
        break;
    case OPERATOR_EQ:
        printf("#encontrou OPERATOR_EQ %d",OPERATOR_EQ);
        break;
    case OPERATOR_DIF:
        printf("#encontrou OPERATOR_DIF %d",OPERATOR_DIF);
        break;
    case TK_IDENTIFIER:
    printf("#encontrou SIMBOLO %d simbolo : %s",TK_IDENTIFIER,yytext);
        break;
    case LIT_STRING:
    printf("#encontrou LIT_STRING %d literal : %s",LIT_STRING,yytext);
        break;
    case LIT_CHAR:
    printf("#encontrou LIT_CHAR %d literal : %s",LIT_CHAR,yytext);
        break;
    case LIT_INTEIRO:
    printf("#encontrou LIT_INTEIRO %d literal : %s",LIT_CHAR,yytext);
        break;
    case LIT_FLOAT:
    printf("#encontrou LIT_FLOAT %d literal : %s",LIT_FLOAT,yytext);
        break;
    case '\n':
        printf("\nachou nova linha, contagem de linhas = %d numero da linha = %d\n", line_count, line_number);
        break;
    case ';' :
    case '(':
    case ')': 
    case '[': 
    case ']': 
    case '{': 
    case '}': 
    case '=': 
    case '+':  
    case '-':  
    case '*': 
    case '/':
    case '<':
    case '>':
    case '&':
    case '|':
    case '~':
        printf("#encontrou caracter especial %d caracter : %c \n",token,(char) token);
        break;
    case TOKEN_ERROR:
        printf("#encontrou TOKEN_ERROR %d INESPERADO : %s \n",token,yytext);
        break;
    default:
        printf("#encontrou algo diferente %s", yytext);
        break;
    printf("\n");
    }
}

int main()
{   
    printf("COMECOU");
    int token;
    print_hashtable();
    initMe();
    while(isRunning())
    {   
        printf("Caraljho");
        token = yylex();
        if(!isRunning())
            break;
        decode(token);
    }
    print_hashtable();
    printf("line counting : %d\n", line_count);
}