#ifndef HEADER_HASH
#define HEADER_HASH

#define TABLE_SIZE 997
#define EH_IDENTIFICADOR 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define var_simbol 1
#define vector_simbol 2
#define function_simbol 3
#define parameter_simbol 4
#define temp_simbol 5
#define label_simbol 6
struct Astnode;

typedef struct Hnode
{
    char *name;
    int appearences;
    int type;
    char *value;
    int symbol_type;
    struct Hnode *next;
    struct Astnode* declaration;
} Hash_node;

typedef struct function_data
{
    int* parameters_types;
    int lenght_parameters;
} Func_data;

Hash_node * hashtable[TABLE_SIZE];
Hash_node* makeTemp(int type);
Hash_node* makeLabel();
Hash_node* insert_simbol_tk(char *name);
unsigned long hash(char *name);
Hash_node* insert_simbol(char *name, int type, int isLiteral);
int next_has_simbol(Hash_node *simbol_root,char *name, int type);
Hash_node *create_simbol(char *simbol_name, int type, int isLiteral);
Hash_node* insert_in_next( Hash_node *simbol_root,char *new_simbol, int type, int isLiteral);
void print_hashtable(void);
void print_lit_temp_to_ASM(FILE* out);
void print_string_to_ASM(FILE* out);

#endif