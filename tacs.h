#ifndef HEADER_TAC
#define HEADER_TAC


#include "hash.h"
#include "ast.h"

#define TAC_PROGRAM 0
#define TAC_SYMBOL 1
#define TAC_ADD 101
#define TAC_SUB 102
#define TAC_MULT 103
#define TAC_DIV 104
#define TAC_GT 105
#define TAC_GE 106
#define TAC_LT 107
#define TAC_LE 108
#define TAC_DIF 109
#define TAC_EQ 110
#define TAC_AND 111
#define TAC_OR 112
#define TAC_NOT 113
#define TAC_COPY 4
#define TAC_IFT 5
#define TAC_LABEL 6
#define TAC_JF 7
#define TAC_JUMP 8
#define TAC_VEC_POS 9
#define TAC_VEC_ASS 10
#define TAC_ARG 11
#define TAC_READ 12
#define TAC_PRINT 13
#define TAC_LIST_EXP 14
#define TAC_VEC_DECL 15
#define TAC_FUNC_BEGIN 16
#define TAC_FUNC_END 17
#define TAC_FUNC_CALL 18
#define TAC_VALUE 19
#define TAC_RET 20
typedef struct tac_node
{
    int type;
    Hash_node * res;
    Hash_node * op1;
    Hash_node * op2;
    struct tac_node* prev;
    struct tac_node* next;
} Tac;

Tac* tacCreate(int type,Hash_node* res,Hash_node* op1,Hash_node* op2);
void tacPrint(Tac* tac);
void tacPrintBackwards(Tac* tac);
Tac* generateCode(Ast *Node);
Tac* tacJoin(Tac* l1,Tac* l2);
#endif