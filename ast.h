

#ifndef HEADER_AST
#define HEADER_AST

typedef struct Astnode
{
    int type;
    struct Astnode *parent;
    struct Astnode *sons;
} Ast;
#endif