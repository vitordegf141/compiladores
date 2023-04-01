#ifndef HEADER_HASH
#define HEADER_HASH

#define TABLE_SIZE 997
#define EH_IDENTIFICADOR 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hnode
{
    char *name;
    int appearences;
    int type;
    struct Hnode *next;
} Hash_node;

Hash_node * hashtable[TABLE_SIZE];

unsigned long hash(char *name);
int next_has_simbol(Hash_node *simbol_root,char *name, int type);
Hash_node *create_simbol(char *simbol_name, int type);
Hash_node* insert_in_next( Hash_node *simbol_root,char *new_simbol, int type);
void print_hashtable();
Hash_node* insert_simbol(char *name, int type);

#endif