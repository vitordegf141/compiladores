

%{
#include "hash.h"
#include "ast.h"
#include <string.h>
#include "y.tab.h"


int line_count =0;
int line_number =1;
int running = 1;
int charlenght=0;
char chartemp ='a';
char *temp_string;
char temp_string_lenght;
char temp_max_string_lenght;
#define TABLE_SIZE 997


Hash_node* tester;
void initMe(void)
{
    //*hashtable = ( simbol *) malloc(sizeof( simbol)*TABLE_SIZE);
    int i;
    for(i=0;i<TABLE_SIZE;i++)
    {
        hashtable[i]=NULL;
    }
}   

int isRunning()
{
    return running;
}

#define incrimental_string_lenght 10

void append_temp_string(char new_text){
    temp_string[temp_string_lenght-1]=new_text;
    temp_string[temp_string_lenght]='\0';
}

void reset_temp_string()
    {
        temp_string = malloc(sizeof(char)*incrimental_string_lenght);
        temp_max_string_lenght =incrimental_string_lenght;
        temp_string[0]='\0';
        temp_string_lenght =1;
    }

void insert_char_into_temp_string(char text)
{
    if(temp_max_string_lenght==0)
    {
        temp_string = malloc(sizeof(char)*incrimental_string_lenght);
        temp_max_string_lenght =incrimental_string_lenght;
        append_temp_string(text);
        temp_string_lenght =2;

    }
    else if(temp_string_lenght + 1 >temp_max_string_lenght)
    {
        temp_max_string_lenght+=incrimental_string_lenght;
        temp_string = realloc(temp_string, sizeof(char)*temp_max_string_lenght);
        append_temp_string(text);
        temp_string_lenght++;
    }
    else
    {
        append_temp_string(text);
        temp_string_lenght++;
    }

}

int getLineNumber()
{
    return line_number;
}

void stringnewline(char *literal1){
    if(strstr(literal1,"\n") !=NULL)
    {
        line_count++;
        line_number++;
    }
        
}
%}
%x COMMENT_MULTIPLE
%x COMMENT_SIMPLE
%x READ_CHAR
%x READ_STRING
%x READ_ESCAPE
%%

;|\(|\)|\[|\]|\{|\}|\=|\+|\-|\*|\/|\<|\>|\&|\||\~           {return (int)yytext[0];}
cara                                                        {return KW_CARA;}
inte                                                        {return KW_INTE;}
real                                                        {return KW_REAL;}
se                                                          {return KW_SE;}
entaum                                                      {return KW_ENTAUM;}
senaum                                                      {return KW_SENAUM;}
enquanto                                                    {return KW_ENQUANTO;}
entrada                                                     {return KW_ENTRADA;}
escreva                                                     {return KW_ESCREVA;}
retorne                                                     {return KW_RETORNE;}
\=\=                                                      {return OPERATOR_EQ;}
\>\=                                                      {return OPERATOR_GE;}
\<\=                                                      {return OPERATOR_LE;}
\!\=                                                      {return OPERATOR_DIF;}
"\n"                                                    {line_count++;line_number++;}
"\""                                              {reset_temp_string();BEGIN READ_STRING;}
"'"                                             {charlenght = 0;BEGIN READ_CHAR;}
[0-9]+                                                  {yylval.symbol = insert_simbol(yytext,KW_INTE,1);return LIT_INTEIRO;}
[0-9]+\.[0-9]+                                                {yylval.symbol = insert_simbol(yytext,KW_REAL,1);return LIT_FLOAT;}
\/\/                                                    {BEGIN COMMENT_SIMPLE;}
\/\/\/                                                       {BEGIN COMMENT_MULTIPLE;}
[a-z]+[a-z\.\_\-1-9]*                                          {yylval.symbol =insert_simbol_tk(yytext);return  TK_IDENTIFIER;}
[ \t\r,]+                                                   {}
.                                                    {return TOKEN_ERROR;}
<COMMENT_MULTIPLE>. {}
<COMMENT_MULTIPLE>[\n]  {line_count++;line_number++;}
<COMMENT_MULTIPLE>"\\"{3} {BEGIN 0;}

<COMMENT_SIMPLE>.* {}
<COMMENT_SIMPLE>"\n" {line_count++;line_number++;BEGIN 0;}




<READ_CHAR>"'" {if (charlenght == 1) {yylval.symbol = insert_simbol(&chartemp,KW_CARA,1); yytext = &chartemp; BEGIN 0;return LIT_CHAR;} else{ return TOKEN_ERROR;} }
<READ_CHAR>. {chartemp = yytext[0];charlenght++;}

<READ_STRING>"\"" {yylval.symbol = insert_simbol(temp_string,LIT_STRING,1);BEGIN 0;return LIT_STRING;}
<READ_STRING>. {insert_char_into_temp_string(yytext[0]);}

<READ_ESCAPE>"a" {insert_char_into_temp_string('\a');BEGIN READ_STRING;}
<READ_ESCAPE>"b" {insert_char_into_temp_string('\b');BEGIN READ_STRING;}
<READ_ESCAPE>"e" {insert_char_into_temp_string('\e');BEGIN READ_STRING;}
<READ_ESCAPE>"f" {insert_char_into_temp_string('\f');BEGIN READ_STRING;}
<READ_ESCAPE>"n" {insert_char_into_temp_string('\n');BEGIN READ_STRING;}
<READ_ESCAPE>"r" {insert_char_into_temp_string('\r');BEGIN READ_STRING;}
<READ_ESCAPE>"t" {insert_char_into_temp_string('\t');BEGIN READ_STRING;}
<READ_ESCAPE>"v" {insert_char_into_temp_string('\v');BEGIN READ_STRING;}
<READ_ESCAPE>"\\" {insert_char_into_temp_string('\\');BEGIN READ_STRING;}
<READ_ESCAPE>"\'" {insert_char_into_temp_string('\'');BEGIN READ_STRING;}
<READ_ESCAPE>"\"" {insert_char_into_temp_string('\"');BEGIN READ_STRING;}
<READ_ESCAPE>"?" {insert_char_into_temp_string('\?');BEGIN READ_STRING;}
<READ_ESCAPE>. {return TOKEN_ERROR;}
%%


#include "main.c"
#include "y.tab.c"

