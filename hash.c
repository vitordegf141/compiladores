#include "hash.h"

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

 Hash_node *create_simbol(char *simbol_name, int type)
{
    if(simbol_name == NULL)
        return NULL;
     Hash_node *new = malloc(sizeof( Hash_node));
    int i,namesize;
    namesize = strlen(simbol_name);
    new->name = malloc(sizeof(char)*(namesize+1));
    strcpy(new->name,simbol_name);
    new->appearences=1;
    new->next=NULL;
    new->type=type;
    return new;
}

void insert_in_next( Hash_node *simbol_root,char *new_simbol, int type){
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
        Hash_node *new_simbol=create_simbol(name,type);
        hashtable[computed_hash]=new_simbol;
        return 1;
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