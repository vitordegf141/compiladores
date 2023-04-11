
#ifndef C_HASH
#define C_HASH
#include "hash.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
char const defaultlit[] = "_lit_literal_";
char const suffixTk[]= "_tk_";
int appendixlit =0;
char appendixlit_str[20];


unsigned long hash(char *name)
{
    unsigned long sum =0;
    for (int j=0;name[j]!='\0';j++)
    {
        sum += name[j];
    }
    return sum % TABLE_SIZE;
}

int next_has_simbol(Hash_node *simbol_root,char *name, int type)
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

 Hash_node *create_simbol(char *simbol_name, int type, int isLiteral)
{
    if(simbol_name == NULL)
        return NULL;
     Hash_node *new = malloc(sizeof( Hash_node));
    int i,namesize;
    namesize = strlen(simbol_name);
    if(isLiteral)
    {
        //printf("\nliteral strlen(simbol_name) = %d name  = %s",namesize,simbol_name);
        new->value = malloc(sizeof(char)*(namesize+1));
        strcpy(new->value,simbol_name);
        sprintf(appendixlit_str, "%d", appendixlit);
        new->name = malloc(sizeof(char)*(strlen(defaultlit) + strlen(appendixlit_str) +1));
        strcpy(new->name,defaultlit);
        strcat(new->name,appendixlit_str);
        new->appearences=1;
        new->next=NULL;
        new->type=type;
        appendixlit++;
        new->symbol_type=0;
    }
    else
    {
        //printf("\nidentifier strlen(simbol_name) = %d value  = %s",namesize,simbol_name);
        new->name = malloc(sizeof(char)*(namesize+1));
        strcpy(new->name,simbol_name);
        new->appearences=1;
        new->next=NULL;
        new->type=type;
        new->value=NULL;
        new->symbol_type=-1;
    }
    new->declaration=NULL;
    
    return new;
}

Hash_node* insert_in_next( Hash_node *simbol_root,char *new_simbol, int type, int isLiteral){
    if(simbol_root == NULL || new_simbol == NULL){
         fprintf(stderr, "\ninsert_in_next with root simbol null or null new_simbol\n");
        return NULL;
    }
    else{
        if(strcmp(simbol_root->name,new_simbol) == 0)
        {
            simbol_root->appearences++;
            return simbol_root;
        }
        else
        {
            if(simbol_root->next == NULL)
            {
                simbol_root->next = create_simbol(new_simbol,type,isLiteral);
                return simbol_root->next;
            }
            else
            {
                return insert_in_next(simbol_root->next,new_simbol,type,isLiteral);
            }
        }
    }
}
void print_next(Hash_node* next,int i)
{
    if(next == NULL)
        return;
    printf("\n\t%d\t%s\t%d\tsymbol_type=%d",i,next->name,next->type,next->symbol_type);
            if(next->value!=NULL)
                printf("\tvalue=%s",next->value);
            if(next->declaration!=NULL)
                printf("\tdeclaration= notNull");
            if(next->declaration==NULL)
                printf("\tdeclaration= Null");
    print_next(next->next,i);
}

void print_hash_to_ASM(Hash_node* next,FILE* out)
{
    if(next!=NULL)
        {
            if(next->symbol_type == 0 || next->symbol_type == 5)
            {
                fprintf(out,"%s:\n",next->name);
                switch ( next->type)
                {
                case 258:
                    if( next->value !=NULL)
                        fprintf(out,"\t.byte\t\'%s\'\n",next->value);
                    else
                        fprintf(out,"\t.byte\t0\n");
                    break;
                case 259:
                    if( next->value !=NULL)
                        fprintf(out,"\t.long\t%s\n",next->value);
                    else
                        fprintf(out,"\t.long\t0\n");
                    break;
                case 260:
                    if( next->value !=NULL)
                        fprintf(out,"\t.long\t%s\n",next->value);
                    else
                        fprintf(out,"\t.long\t0\n");
                    break;
                case 276:
                    if( next->value !=NULL)
                        fprintf(out,"\t.string\t\"%s\"\n",next->value);
                    else
                        fprintf(out,"\t.string\t\"\"\n");
                    break;
                default:
                    break;
                }
            }
        }
}

void print_hash_next_ASM(Hash_node* next,FILE* out)
{
    if(next == NULL)
        return;
    print_hash_to_ASM(next,out);
    print_hash_next_ASM(next->next,out);
}

void print_lit_temp_to_ASM(FILE* out)
{
    int i;
    for(i=0;i<TABLE_SIZE;i++)
    {
        if(hashtable[i]!=NULL)
        {
            print_hash_to_ASM(hashtable[i],out);
            print_hash_next_ASM(hashtable[i]->next,out);
        }
    }
    return;
}

void print_hashtable(void)
{
    int i;
    printf("\nbegin\n");
    for(i=0;i<TABLE_SIZE;i++)
    {
        if(hashtable[i]!=NULL)
        {
            printf("\n\t%d\t%s\t%d\tsymbol_type=%d",i,hashtable[i]->name,hashtable[i]->type,hashtable[i]->symbol_type);
            if(hashtable[i]->value!=NULL)
                printf("\tvalue=%s",hashtable[i]->value);
            if(hashtable[i]->declaration!=NULL)
                printf("\tdeclaration= notNull");
            if(hashtable[i]->declaration==NULL)
                printf("\tdeclaration= Null");
            print_next(hashtable[i]->next,i);
        }
    }
    printf("\nend\n");
    return;
}
Hash_node* insert_simbol_tk(char *name)
{
    
    int namesize = strlen(name) + strlen(suffixTk);
    char *TkName = malloc(sizeof(char)*(namesize+1));
    strcpy(TkName,suffixTk);
    strcat(TkName,name);
    return insert_simbol(TkName,-1,0);
}
Hash_node* insert_simbol(char *name, int type,int isLiteral){
    if(name == NULL)
        return 0;
    unsigned long computed_hash = hash(name);
    if(hashtable[computed_hash] != NULL){
        if(strcmp(hashtable[computed_hash]->name,name) == 0)
        {
            hashtable[computed_hash]->appearences++;
            return hashtable[computed_hash];
        }
        else{
            return insert_in_next(hashtable[computed_hash],name,type,isLiteral);
        }
    }
    else
    {
        Hash_node *new_simbol=create_simbol(name,type,isLiteral);
        hashtable[computed_hash]=new_simbol;
        return new_simbol;
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

Hash_node* makeTemp(int type)
{
    static int serial=0;
    char buffer[50] ="";
    sprintf(buffer,"_tmp_temp%d",serial++);
    Hash_node* tmp =  insert_simbol(buffer,type,0);
    tmp->symbol_type =temp_simbol;
    return tmp;
}

Hash_node* makeLabel()
{
    static int seriallabel=0;
    char buffer[50] ="";
    sprintf(buffer,"_label_temp%d",seriallabel++);
    Hash_node* label =  insert_simbol(buffer,-1,0);
    label->symbol_type =label_simbol;
    return label;
}
#endif