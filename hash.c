
#ifndef C_HASH
#define C_HASH
#include "hash.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
char const defaultlit[] = "%literal_";
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
    }
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

void print_hashtable(void)
{
    int i;
    printf("\nbegin\n");
    for(i=0;i<TABLE_SIZE;i++)
    {
        if(hashtable[i]!=NULL)
        {
            printf("\n\t%d\t%s\t%d",i,hashtable[i]->name,hashtable[i]->type);
            if(hashtable[i]->value!=NULL)
                printf("\tvalue=%s",hashtable[i]->value);
        }
    }
    printf("\nend\n");
    return;
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

#endif