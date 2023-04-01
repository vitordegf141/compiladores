

typedef struct astnode
{
    int type;
    struct astnode *parent;
    struct astnode *sons;
} ast;