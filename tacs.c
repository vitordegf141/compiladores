

#include "tacs.h"

#include "hash.h"
#include "ast.h"

Tac* makeBinOpe(int tac_type,Tac* code0,Tac* code1);
Tac* makeIfThen(Tac* code0,Tac* code3);
Tac* makeIfThenElse(Tac* code0,Tac* code1,Tac* code2);
Tac* makeWhile(Tac* code0,Tac* code2);
Tac* makePrint(Tac* code0);
Tac* makeVecDecl(Hash_node* vecSymbol,Tac* code0,Tac* code1);
Tac* makeFuncDecl(Hash_node* FuncSymbol,Tac* code0,Tac* code1);
Tac* makeFuncCall(Hash_node* FuncSymbol,Tac* code0);
Tac* makeVarDecl(Hash_node* VarSymbol,Tac* code0);

Tac* tacCreate(int type,Hash_node* res,Hash_node* op1,Hash_node* op2)
{
    Tac* new = (Tac*) malloc(sizeof(Tac));
    new->type=type;
    new->res=res;
    new->op1=op1;
    new->op2=op2;
    new->prev=NULL;
    new->next=NULL;
    return new;
}

void tacPrint(Tac* tac)
{
    if(tac==NULL)
        return;
    if(tac->type==TAC_SYMBOL)
        return;
    fprintf(stderr,"TAC(");
    switch (tac->type)
    {
    case TAC_PROGRAM:
        fprintf(stderr,"TAC_PROGRAM");
        break;
    case TAC_SYMBOL:
        fprintf(stderr,"TAC SYMBOL");
        break;
    case TAC_ADD:
        fprintf(stderr,"TAC_ADD");
        break;
    case TAC_SUB:
        fprintf(stderr,"TAC_SUB");
        break;
    case TAC_COPY:
        fprintf(stderr,"TAC_COPY");
        break;
    case TAC_IFT:
        fprintf(stderr,"TAC_IFT");
        break;
    case TAC_MULT:
        fprintf(stderr,"TAC_MULT");
        break;
    case TAC_DIV:
        fprintf(stderr,"TAC_DIV");
        break;
    case TAC_GT:
        fprintf(stderr,"TAC_GT");
        break;
    case TAC_GE:
        fprintf(stderr,"TAC_GE");
        break;
    case TAC_LT:
        fprintf(stderr,"TAC_LT");
        break;
    case TAC_LE:
        fprintf(stderr,"TAC_LE");
        break;
    case TAC_DIF:
        fprintf(stderr,"TAC_DIF");
        break;
    case TAC_EQ:
        fprintf(stderr,"TAC_EQ");
        break;
    case TAC_AND:
        fprintf(stderr,"TAC_AND");
        break;
    case TAC_OR:
        fprintf(stderr,"TAC_OR");
        break;
    case TAC_JF:
        fprintf(stderr,"TAC_JF");
        break;
    case TAC_JUMP:
        fprintf(stderr,"TAC_JUMP");
        break;
    case TAC_LABEL:
        fprintf(stderr,"TAC_LABEL");
        break;
    case TAC_ARG:
        fprintf(stderr,"TAC_ARG");
        break;
    case TAC_VEC_POS:
        fprintf(stderr,"TAC_VEC_POS");
        break;
    case TAC_VEC_ASS:
        fprintf(stderr,"TAC_VEC_ASS");
        break;
    case TAC_READ:
        fprintf(stderr,"TAC_READ");
        break;
    case TAC_PRINT:
        fprintf(stderr,"TAC_PRINT");
        break;
    case TAC_LIST_EXP:
        fprintf(stderr,"TAC_LIST_EXP");
        break;
    case TAC_VEC_DECL:
        fprintf(stderr,"TAC_VEC_DECL");
        break;
    case TAC_FUNC_BEGIN:
        fprintf(stderr,"TAC_FUNC_BEGIN");
        break;    
    case TAC_FUNC_END:
        fprintf(stderr,"TAC_FUNC_END");
        break;
    case TAC_FUNC_CALL:
        fprintf(stderr,"TAC_FUNC_CALL");
        break;
    case TAC_VALUE:
        fprintf(stderr,"TAC_VALUE");
        break;
    case TAC_RET:
        fprintf(stderr,"TAC_RET");
        break;
    case TAC_NOT:
        fprintf(stderr,"TAC_NOT");
        break;
    default:
        fprintf(stderr,"TAC_UNKNOWN");
        break;
    }
    fprintf(stderr,",%s",tac->res == NULL? "" : tac->res->name);
    fprintf(stderr,",%s",tac->op1 == NULL? "" : tac->op1->name);
    fprintf(stderr,",%s",tac->op2 == NULL? "" : tac->op2->name);
    fprintf(stderr,");\n");
    fflush(stderr);
}
void tacPrintBackwards(Tac* tac)
{
    if(tac==NULL)
        return;
    tacPrintBackwards(tac->prev);
    tacPrint(tac);
    return;
}


int gencode_count =0;
Tac* generateCode(Ast *Node)
{
   
    int i;
    Tac* result = NULL;
    Tac* code[4];
    if(Node == NULL)
        return NULL;

    fflush(stdout);
    for(i=0;i<4;i++)
        code[i]=generateCode(Node->sons[i]);
    fflush(stdout);
    switch (Node->ast_type)
    {
    case program_ast:
        if(code[3]==NULL) fprintf(stderr,"\n\expression_add code0 eh NULL");
        result = tacJoin(tacCreate(TAC_PROGRAM,NULL,NULL,NULL),code[3]);
        break;
    case expression_func_call:
        result = makeFuncCall(Node->symbol,code[0]);
        break;
    case expression_var:
        result = tacCreate(TAC_SYMBOL,Node->symbol,NULL,NULL);
        if(result == NULL) fprintf(stderr,"\n\expression_var result eh NULL");
        break;
    case expression_add:
        if(code[0]==NULL) fprintf(stderr,"\n\expression_add code0 eh NULL");
        if(code[1]==NULL) fprintf(stderr,"\n\expression_add code1 eh NULL");
        result = makeBinOpe(TAC_ADD,code[0],code[1]);
        if(result == NULL) fprintf(stderr,"\n\expression_add result eh NULL");
        break;
    case expression_minus:
        result = makeBinOpe(TAC_SUB,code[0],code[1]);
        break;
    case expression_mult:
        result = makeBinOpe(TAC_MULT,code[0],code[1]);
        break;
    case expression_divison:
        result = makeBinOpe(TAC_DIV,code[0],code[1]);
        break;
    case expression_gt:
        result = makeBinOpe(TAC_GT,code[0],code[1]);
        break;
    case expression_ge:
        result = makeBinOpe(TAC_GE,code[0],code[1]);
        break;
    case expression_lt:
        result = makeBinOpe(TAC_LT,code[0],code[1]);
        break;
    case expression_le:
        result = makeBinOpe(TAC_LE,code[0],code[1]);
        break;
    case expression_dif:
        result = makeBinOpe(TAC_DIF,code[0],code[1]);
        break;
    case expression_eq:
        fflush(stdout);
        result = makeBinOpe(TAC_EQ,code[0],code[1]);
        break;
    case expression_and:
        result = makeBinOpe(TAC_AND,code[0],code[1]);
        break;
    case expression_or:
        result = makeBinOpe(TAC_OR,code[0],code[1]);
        break;
    case expression_not:
        if(code[0]==NULL) fprintf(stderr,"\nexpression_not code0 eh NULL");
        result = tacJoin(code[0],tacCreate(TAC_NOT,makeTemp(277),code[0]==NULL? NULL: code[0]->res,NULL));
        break;
    case expression_vector_pos:
        if(code[0]==NULL) fprintf(stderr,"\nexpression_vector_pos code0 eh NULL");
        result = tacJoin(code[0],tacCreate(TAC_VEC_POS,makeTemp(259),Node->symbol,code[0]==NULL? NULL: code[0]->res));
        break;
    case vec_assignment:
        if(code[0]==NULL) fprintf(stderr,"\nvec_assignment code0 eh NULL");
        if(code[1]==NULL) fprintf(stderr,"\nvec_assignment code1 eh NULL\n");
        result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_VEC_ASS,Node->symbol,code[0]==NULL? NULL: code[0]->res,code[1]==NULL? NULL: code[1]->res)));
        break;
    case var_assignment:
        if(code[0]==NULL) fprintf(stderr,"\nvar_assignment code0 eh NULL");
        result = tacJoin(code[0],tacCreate(TAC_COPY,Node->symbol,code[0]==NULL? NULL: code[0]->res,NULL));
        fflush(stderr);
        break;
    case entaum_cmd:
        if(code[0]==NULL) fprintf(stderr,"\tentaum_cmd code0 eh NULL");
        if(code[2]==NULL) fprintf(stderr,"\tentaum_cmd code2 eh NULL");
        result = makeIfThen(code[0],code[2]);
        break;
    case senaum_cmd:
        if(code[0]==NULL) fprintf(stderr,"\tsenaum_cmd code0 eh NULL");
        if(code[1]==NULL) fprintf(stderr,"\tsenaum_cmd code1 eh NULL");
        if(code[2]==NULL) fprintf(stderr,"\tsenaum_cmd code2 eh NULL\n");
        result = makeIfThenElse(code[0],code[1],code[2]);
        break;
    case enquanto_cmd:
        if(code[0]==NULL) fprintf(stderr,"\nenquanto_cmd code0 eh NULL");
        if(code[1]!=NULL) fprintf(stderr,"\tenquanto_cmd code1 eh NULL");
        if(code[2]==NULL) fprintf(stderr,"\tenquanto_cmd code2 eh NULL");
        if(code[3]!=NULL) fprintf(stderr,"\tenquanto_cmd code3 eh NULL\n");
        result = makeWhile(code[0],code[2]);
        break;
    case escreva_cmd:
        result = makePrint(code[0]);
        break;
    case tail_list_ident:
        result = tacJoin(code[3],tacJoin(tacCreate(TAC_LABEL,Node->symbol,NULL,NULL),tacCreate(TAC_VALUE,Node->symbol,NULL,NULL)));
        break;
    case tail_list_expression:
        if(code[0]==NULL) fprintf(stderr,"\ntail_list_expression code0 eh NULL");
        fflush(stderr);
        result = tacJoin(tacJoin(code[0],tacCreate(TAC_LIST_EXP,NULL,code[0]==NULL? NULL: code[0]->res,NULL)),code[3]);
        break;
    case expression_entrada:
        result = tacCreate(TAC_READ,makeTemp(259),NULL,NULL);
        break;
    case var_decl:
        result = makeVarDecl(Node->symbol,code[0]);
        break;
    case vector_decl:
        result = makeVecDecl(Node->symbol,code[0],code[1]);
        break;
    case function_decl:
        result = makeFuncDecl(Node->symbol,code[0],code[1]);
        break;
    case retorne_cmd:
        if(code[0]==NULL) fprintf(stderr,"\nretorne_cmd code0 eh NULL");
        result = tacJoin(code[0],tacCreate(TAC_RET,code[0]==NULL? NULL: code[0]->res,NULL,NULL));
        break;
        
    default:
        result = tacJoin(code[0],tacJoin(code[1],tacJoin(code[2],code[3])));
        break;
    }
    if(Node->ast_type==var_assignment && result == NULL) fprintf(stderr,"\nvar_assignment result eh NULL");
    return result;
}
int joincount =0;
Tac* tacJoin(Tac* l1,Tac* l2)
{
    Tac* point;
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;
    for(point = l2;point->prev != NULL; point = point->prev)
    ;
    point->prev = l1;
    return l2;
}


Tac* makeBinOpe(int tac_type,Tac* code0,Tac* code1)
{
    if(code0==NULL) fprintf(stderr,"\t%d code0 eh NULL\n",tac_type);
    if(code1==NULL) fprintf(stderr,"\t%d code1 eh NULL\n",tac_type);
    return tacJoin(tacJoin(code0,code1),tacCreate(tac_type,makeTemp(code0==NULL? -1: code0->res->type),code0==NULL? NULL: code0->res,code1==NULL? NULL: code1->res));
}

Tac* makeIfThen(Tac* code0,Tac* code2)
{
    Tac* jumpTac;
    Tac* labelTac;
    Hash_node* newLabel;
    newLabel = makeLabel();

    jumpTac = tacCreate(TAC_JF,newLabel,code2==NULL? NULL: code2->res,NULL);
    fflush(stdout);
    jumpTac->prev = code2;
    labelTac = tacCreate(TAC_LABEL,newLabel,NULL,NULL);
    labelTac->prev = code0;
    return tacJoin(jumpTac,labelTac);
}

Tac* makeIfThenElse(Tac* code0,Tac* code1,Tac* code2)
{
    Tac* ifjumpTac;
    Tac* jumpTac;
    Tac* label1Tac;
    Tac* label2Tac;
    Hash_node* Label1;
    Hash_node* Label2;
    Label1 = makeLabel();
    Label2 = makeLabel();

    ifjumpTac = tacCreate(TAC_JF,Label1,code2==NULL? NULL: code2->res,NULL);
    ifjumpTac->prev = code2;
    
    label1Tac = tacCreate(TAC_LABEL,Label1,NULL,NULL);
    label2Tac = tacCreate(TAC_LABEL,Label2,NULL,NULL);
    jumpTac = tacCreate(TAC_JUMP,Label2,NULL,NULL);
    if(code0 != NULL)
        code0->prev = ifjumpTac;
    jumpTac->prev = code0;
    label1Tac->prev =jumpTac;
    if(code1!=NULL)
        code1->prev=label1Tac;
    label2Tac->prev = code1;
    return label2Tac;
}
Tac* makeWhile(Tac* code0,Tac* code2)
{
/// while
/// label1
/// code2 ->temp0
/// JF label2 temp0
/// code 0
/// JUMP label1
/// label2
    Tac* ifjumpTac;
    Tac* jumpTac;
    Tac* label1Tac;
    Tac* label2Tac;
    Hash_node* Label1;
    Hash_node* Label2;
    Label1 = makeLabel();
    Label2 = makeLabel();
    label1Tac = tacCreate(TAC_LABEL,Label1,NULL,NULL);
    label2Tac = tacCreate(TAC_LABEL,Label2,NULL,NULL);

    ifjumpTac = tacCreate(TAC_JF,Label2,code2==NULL? NULL: code2->res,NULL);
    ifjumpTac->prev=code2;

    jumpTac = tacCreate(TAC_JUMP,Label1,NULL,NULL);
    jumpTac->prev = code0;
    label2Tac->prev=jumpTac;

    return tacJoin(label1Tac,tacJoin(ifjumpTac,label2Tac));
}

Tac* tacInverter(Tac* filho,Tac* pai)
{
    if(filho==NULL)
    {
        return pai;
    }

    Tac* temp =tacInverter(filho->prev,filho);
    filho->prev=pai;
    return temp;
}

Tac* makePrint(Tac* code0)
{
    if (code0 ==NULL)
        return NULL;
    
    for(Tac* temp=code0;temp!=NULL;temp=temp->prev)
    {
        if(temp == NULL)
            {
                fprintf(stderr,"\n temp eh NULL wtf");
            }
        if(temp->type==TAC_LIST_EXP)
            temp->type= TAC_PRINT;
        
    }
    //code0 = tacInverter(code0,NULL);
    return code0;
}



Tac* makeVecDecl(Hash_node* vecSymbol,Tac* code0,Tac* code1)
{
    Tac* vec = tacCreate(TAC_LABEL,vecSymbol,NULL,NULL);
    int pos_vec=0;
    for(Tac* temp=code1;temp!=NULL;temp=temp->prev)
    {
        if(temp->type==TAC_LIST_EXP)
        {
            pos_vec++;
            temp->type= TAC_VALUE;
            temp->res=vecSymbol;
        }
    }
    //code1 = tacInverter(code1,NULL);
    int vec_len=0;
    if(code0 != NULL && code0->res != NULL && code0->res->value != NULL)
        vec_len = atoi(code0->res->value);
    Tac* fill_rest =NULL;
    Tac* temp=NULL;
    for(;pos_vec<vec_len;pos_vec++)
    {
        temp = tacCreate(TAC_VALUE,vecSymbol,NULL,NULL);
        temp->prev = fill_rest;
        fill_rest =temp;
    }
    
    return tacJoin(vec,tacJoin(code1,fill_rest));;
}
Tac* makeFuncDecl(Hash_node* FuncSymbol,Tac* code0,Tac* code1)
{

    Tac* funBegin = tacCreate(TAC_FUNC_BEGIN,FuncSymbol,NULL,NULL);
    Tac* funEnd = tacCreate(TAC_FUNC_END,FuncSymbol,NULL,NULL);
    return tacJoin(code0,tacJoin(funBegin,tacJoin(code1,funEnd)));
} 

Tac* makeVarDecl(Hash_node* VarSymbol,Tac* code0)
{
    if(VarSymbol == NULL)
        return NULL;
    Tac* varLabel = tacCreate(TAC_LABEL,VarSymbol,NULL,NULL);
    Tac* var = tacCreate(TAC_VALUE,VarSymbol,code0==NULL? NULL:code0->res,NULL);
    return tacJoin(varLabel,var);
}

Tac* makeFuncCall(Hash_node* FuncSymbol,Tac* code0)
{

    if(FuncSymbol == NULL)
        return NULL;
    Ast* fun_decl = FuncSymbol->declaration;
    if(fun_decl == NULL || fun_decl->sons[0] ==NULL)
    {
        fprintf(stderr,"\t fun_decl eh NULL ou fun_decl->sons[0] eh NULL\n");
        return NULL;
    }
    
    //remove head
    Ast* fun_iden_list = fun_decl->sons[0]->sons[3];

    for(Tac* temp=code0;temp!=NULL&&fun_iden_list!=NULL;temp=temp->prev)
    {
        if(temp->type==TAC_LIST_EXP)
        {
            temp->type= TAC_COPY;
            temp->res= fun_iden_list->symbol==NULL? NULL : fun_iden_list->symbol;
            fun_iden_list=fun_iden_list->sons[3];
        }
    }
    Tac* fun_call = tacCreate(TAC_FUNC_CALL,makeTemp(FuncSymbol->type),FuncSymbol,NULL);
    Tac* tesTemp =  tacJoin(code0,fun_call);
    if(tesTemp == NULL)
        fprintf(stderr,"\t fun_decl tacJoin(code0,fun_call); eh NULL\n");
    return tesTemp;

}