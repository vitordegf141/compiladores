

%{
#include "tokens.h"
#include <string.h>

int line_count =0;
int line_number =1;
int running = 1;


#define TABLE_SIZE 997
#define EH_IDENTIFICADOR 1
#define EH_LITERAL 2
typedef struct simbol
{
    char *name;
    int appearences;
    int type;
    struct simbol *next;
}simbol;
simbol * hashtable[TABLE_SIZE];
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
unsigned long hash(char *name)
{
    unsigned long sum =0;
    for (int j=0;name[j]!='\0';j++)
    {
        sum += name[j];
    }
    return sum % TABLE_SIZE;
}

int next_has_simbol(simbol *simbol_root,char *name, int type)
{
    if(simbol_root == NULL)
        return 0;
    else{
         if(strcmp(simbol_root->name,name) == 0)
            return 1;
        else
        {
            return next_has_simbol(simbol_root->next,name,type);
        }
    }
}
int has_simbol(char *name,int type){
    unsigned long computed_hash = hash(name);
    if(hashtable[computed_hash] != NULL){
        if(strcmp(hashtable[computed_hash]->name,name) == 0)
            return 1;
        else 
            return next_has_simbol(hashtable[computed_hash],name,type);
    }
    else
    {
        return 0;
    }
}

 simbol *create_simbol(char *simbol_name, int type)
{
    if(simbol_name == NULL)
        return NULL;
     simbol *new = malloc(sizeof( simbol));
    int i,namesize;
    namesize = strlen(simbol_name);
    new->name = malloc(sizeof(char)*(namesize+1));
    strcpy(new->name,simbol_name);
    new->appearences=1;
    new->next=NULL;
    new->type=type;
    return new;
}

void insert_in_next( simbol *simbol_root,char *new_simbol, int type){
    if(simbol_root == NULL || new_simbol == NULL)
        return;
    else{
        if(strcmp(simbol_root->name,new_simbol) == 0)
        {
            simbol_root->appearences++;
        }
        else
        {
            if(simbol_root->next == NULL)
            {
                simbol_root->next = create_simbol(new_simbol,type);
            }
            else
            {
                insert_in_next(simbol_root->next,new_simbol,type);
            }
        }
    }
}

void print_hashtable()
{
    int i;
    printf("\nbegin\n");
    for(i=0;i<TABLE_SIZE;i++)
    {
        if(hashtable[i]!=NULL)
            printf("\n\t%d\t%s\t%d",i,hashtable[i]->name,hashtable[i]->type);
    }
    printf("\nend\n");
}

int insert_simbol(char *name, int type){
    if(name == NULL)
        return 0;
    unsigned long computed_hash = hash(name);
    if(hashtable[computed_hash] != NULL){
        if(strcmp(hashtable[computed_hash]->name,name) == 0)
        {
            hashtable[computed_hash]->appearences;
            return 1;
        }
        else{
            insert_in_next(hashtable[computed_hash],name,type);
            return 1;
        }
    }
    else
    {
        simbol *new_simbol=create_simbol(name,type);
        hashtable[computed_hash]=new_simbol;
        return 1;
    }
    
}
int getLineNumber()
{
    return line_number;
}

void stringnewline(char *literal){
    if(strstr(literal,"\n") !=NULL)
    {
        line_count++;
        line_number++;
    }
        
}
%}
%x COMMENT_MULTIPLE
%x COMMENT_SIMPLE
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
"\n"                                                     {line_count++;line_number++;}
"\"(\\\"|.)*\""                                              {insert_simbol(yytext,EH_LITERAL);return LIT_STRING;}
"\'(.)\'"                                                {insert_simbol(yytext,EH_LITERAL);return LIT_CHAR;}
[0-9]+                                                  {insert_simbol(yytext,EH_LITERAL);return LIT_INTEIRO;}
[0-9]+\.[0-9]+                                                {insert_simbol(yytext,EH_LITERAL);return LIT_FLOAT;}
\/\/                                                    {BEGIN COMMENT_SIMPLE;}
\/\/\/                                                       {BEGIN COMMENT_MULTIPLE;}
[a-z]+[a-z\.\_\-]*                                          {insert_simbol(yytext,EH_IDENTIFICADOR);return  TK_IDENTIFIER;}
[ \t\r]+                                                   {}
"[^A-z'0-9 ;\(\)\[\]\{\}\=\+\-\*\/\<\>\&\\~!\",.\n]"                                                    {return TOKEN_ERROR;}
<COMMENT_MULTIPLE>[^\(\\\\\\\\|[\n]\)]* {}
<COMMENT_MULTIPLE>[\n]  {line_count++;line_number++; return '\n';}
<COMMENT_MULTIPLE>\\\\\\\\ {BEGIN 0;}

<COMMENT_SIMPLE>.* {}
<COMMENT_SIMPLE>"\n" {BEGIN 0;}
%%


#include "main.c"



int yywrap()
{
    running = 0;
    return 1;
}