
#include <stdio.h>
#include "hash.h"
#include "y.tab.h"

extern FILE *yyin;
extern FILE *yyout;
void decode(int token)
{
    switch (token)
    {
    case KW_CARA:
        printf("\n#encontrou KW_CARA %d",KW_CARA);
        break;
    case KW_INTE:
        printf("\n#encontrou KW_INTE %d",KW_INTE);
        break;
    case KW_REAL:
        printf("\n#encontrou KW_REAL %d",KW_REAL);
        break;
    case KW_SE:
        printf("\n#encontrou KW_SE %d",KW_SE);
        break;
    case KW_ENTAUM:
        printf("\n#encontrou KW_ENTAUM %d",KW_ENTAUM);
        break;
    case KW_SENAUM:
        printf("\n#encontrou KW_SENAUM %d",KW_CARA);
        break;
    case KW_ENQUANTO:
        printf("\n#encontrou KW_ENQUANTO %d", KW_ENQUANTO);
        break;
    case KW_ENTRADA:
        printf("\n#encontrou KW_ENTRADA %d",KW_ENTRADA);
        break;
    case KW_ESCREVA:
        printf("\n#encontrou KW_ESCREVA %d",KW_ESCREVA);
        break;
    case KW_RETORNE:
        printf("\n#encontrou KW_RETORNE %d",KW_RETORNE);
        break;
    case OPERATOR_LE:
        printf("\n#encontrou OPERATOR_LE %d",OPERATOR_LE);
        break;
    case OPERATOR_GE:
        printf("\n#encontrou OPERATOR_GE %d",OPERATOR_GE);
        break;
    case OPERATOR_EQ:
        printf("\n#encontrou OPERATOR_EQ %d",OPERATOR_EQ);
        break;
    case OPERATOR_DIF:
        printf("\n#encontrou OPERATOR_DIF %d",OPERATOR_DIF);
        break;
    case TK_IDENTIFIER:
    printf("\n#encontrou SIMBOLO %d simbolo : %s",TK_IDENTIFIER,yytext);
        break;
    case LIT_STRING:
    printf("\n#encontrou LIT_STRING %d literal : %s",LIT_STRING,yytext);
        break;
    case LIT_CHAR:
    printf("\n#encontrou LIT_CHAR %d literal : %s",LIT_CHAR,yytext);
        break;
    case LIT_INTEIRO:
    printf("\n#encontrou LIT_INTEIRO %d literal : %s",LIT_CHAR,yytext);
        break;
    case LIT_FLOAT:
    printf("\n#encontrou LIT_FLOAT %d literal : %s",LIT_FLOAT,yytext);
        break;
    case '\n':
        printf("\n\nachou nova linha, contagem de linhas = %d numero da linha = %d", line_count, line_number);
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
        printf("\n#encontrou caracter especial %d caracter : %c",token,(char) token);
        break;
    case TOKEN_ERROR:
        printf("\n#encontrou TOKEN_ERROR %d INESPERADO : %s \n",token,yytext);
        break;
    default:
        printf("\n#encontrou algo diferente %s", yytext);
        break;
    printf("\n");
    }
}

int main(int argc, char *args[])
{   
    printf("Start compiling\n");
    char *filename;
    if(argc <= 1)
    {
        printf("need to specify file\n");
    }
    if(argc == 2)
    {
        filename = args[1];
        printf("yyin file : %s\n",filename);
        yyin = fopen(filename,"r");
        printf("yyout: NULL, NOT DECOMPILING");
        yyout = NULL;
    }
    if(argc == 3)
    {
        filename = args[1];
        printf("yyin file : %s\n",filename);
        yyin = fopen(filename,"r");
        filename = args[2];
        printf("yyout: file : %s\n",filename);
        yyout = fopen(filename,"w");
    }
    if(argc > 3)
    {
        printf("Too many arguments");
        return 0;
    }
    int result;
    printf("COMECOU\n");
    

    if(yyin == NULL)
    {
        printf("File not found, using sample.txt\n");
        yyin = fopen("sample.txt","r");
        if(yyin == NULL)
        {
            printf("sample.txt not found too, exiting\n");
            return 1;
        }
    }
    initMe();
    result = yyparse();
    
    printf("\nline counting : %d\n", line_number);
    printf("\n*********hash********\n");
    print_hashtable();
    printf("\n*******end hash******\n");
    if(result == 0)
    {
        printf("\nSUCCESSFUL it is a program !\n");
    }
    else if(result ==3)
    {
        printf("\n Error on %d\n",line_number);
    }
    else if(result ==4)
    {
        printf("\n semantic error\n");
    }
    exit(result);
    return result;
}