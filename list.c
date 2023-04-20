#include "list.h"

#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////
// Implementação das Estruturas
//
struct StNode{
  struct StNode *prox, *ant;
  Item info;
};

struct StList{
  struct StNode *prim, *ult;
  int capac;
  int length;
};

typedef struct StList ListImpl;
typedef struct StNode Node;

struct StIterator{
  Node *curr;
  bool reverso;
};
//
typedef struct StIterator IteratorImpl;
/////////////////////////////////////////////

List createLst(int capacidade)
{
    ListImpl *lst = (ListImpl *) malloc(sizeof(ListImpl));
    lst->prim = NULL;
    lst->ult = NULL;
    lst->capac = capacidade;
    lst->length = 0;
    return lst;
}

int lengthLst(List L)
{
    ListImpl *lst = (ListImpl *) L;
    return lst->length;
}

int maxLengthLst(List L)
{
    ListImpl *lst = (ListImpl *) L;
    if (lst->capac < 0)
        return -1;
    else
        return lst->capac;
}

bool isEmptyLst(List L)
{
    ListImpl *lst = (ListImpl *) L;
    return lst->length == 0;
}

bool isFullLst(List L)
{
    ListImpl *lst = (ListImpl *) L;
    return lst->length == lst->capac;
}

Posic insertLst(List L, Item info)
{    
    ListImpl *lst = ( ListImpl *)L;
    Node *newNode = (Node *) malloc (sizeof(Node));
    newNode->info = info;
    newNode->prox = NULL;
    
    if (isEmptyLst(L))
        lst->prim = newNode;
    else
        lst->ult->prox = newNode;
        
    newNode->ant = lst->ult;
    lst->ult = newNode;
    lst->length++;
    return newNode;
}

Item popLst(List L)
{
    ListImpl *lst = (ListImpl *) L;

    if (isEmptyLst(L))
    {
        printf("ERRO: popLst em list vazia\n");
        return NULL;
    }
    else
    {
        Node *node = lst->prim;
        Item info = node->info;
        removeLst(L, node);

        return info;
    }
}

void removeLst(List L, Posic p)
{
    ListImpl *lst = (ListImpl *) L;
    Node *node = (Node *) p;
    if (node != NULL)
    {
        if (node->ant != NULL)
            node->ant->prox = node->prox;
        else
            lst->prim = node->prox;

        if (node->prox != NULL)
            node->prox->ant = node->ant;
        else
            lst->ult = node->ant;
        // Cuidado ao desalocar item do tipo Item (ainda desconhecido)
        //free(node->info);
        free(node);
        lst->length--;
    }
    else
        printf("ERRO: removeLst com posicao invalida\n");
}

Item getLst(List L, Posic p)
{
    Node *node = (Node *) p;
    if (node != NULL)
        return node->info;
    else
    {
        printf("ERRO: getLst com posicao invalida\n");
        return NULL;
    }
}

Posic insertBeforeLst(List L, Posic p, Item info)
{
    ListImpl *lst = (ListImpl *) L;
    Node *node = (Node *) p;

    Node *newNode = (Node *) malloc (sizeof(Node));
    newNode->info = info;
    newNode->prox = node;
    newNode->ant = node->ant;
    if (node->ant == NULL)
        lst->prim = newNode;
    else
        node->ant->prox = newNode;
    node->ant = newNode;
    lst->length++;
    return newNode;
}

Posic insertAfterLst(List L, Posic p, Item info)
{
    ListImpl *lst = (ListImpl *) L;
    Node *node = (Node *) p;

    Node *newNode = (Node *) malloc (sizeof(Node));
    newNode->info = info;
    newNode->ant = node;
    newNode->prox = node->prox;
    if (node->prox == NULL)
        lst->ult = newNode;
    else
        node->prox->ant = newNode;
    node->prox = newNode;
    lst->length++;
    return newNode;
}

Posic getFirstLst(List L)
{
    ListImpl *lst = (ListImpl *) L;
    return lst->prim;
}

Posic getNextLst(List L, Posic p)
{
    ListImpl *lst = (ListImpl *) L;
    Node *node = (Node *) p;
    if (lst->ult == node)
        return NIL
    else
        return node->prox;
}

Posic getLastLst(List L)
{
    ListImpl *lst = (ListImpl *) L;
    if (lengthLst(lst) == 0)
        return NIL
    else
        return lst->ult;
}

Posic getPrevLst(List L, Posic p)
{
    ListImpl *lst = (ListImpl *) L;
    Node *node = (Node *) p;
    if (lst->prim == node)
        return NIL
    else
        return node->ant;
}

void killLst(List L)
{
    ListImpl *lst = (ListImpl *) L;
    if (lst != NULL && !isEmptyLst(lst))
    {
        for (Node * node = lst->prim->prox; node != NULL; node = node->prox)
        {
            //free(node->ant->info);
            free(node->ant);
        }
        //free(lst->ult->info);
        free(lst->ult);
        free(lst);
    }
}


/**
 ** Iteradores
 **
 ** (nota: existe uma certa redundancia com getFirst, getLast, 
 **  getNext e getPrevious).
 **/
Iterador createIterador(List L, bool reverso)
{
    ListImpl *lst = (ListImpl *) L;
    IteratorImpl *iter = (IteratorImpl *) malloc (sizeof(IteratorImpl));
    //iter->curr = lst->prim;
    iter->reverso = reverso;
    return iter;
}

void setIteratorPosition(List L, Iterador it, Posic p)
{
    ListImpl *lst = (ListImpl *) L;
    IteratorImpl *iter = (IteratorImpl *) it;
    iter->curr = (Node *) p;
}

bool isIteratorEmpty(List L, Iterador it)
{
    ListImpl *lst = (ListImpl *) L;
    IteratorImpl *iter = (IteratorImpl *) it;
    // DEVERIA verificar se o iterador aponta para ALGUM elemento da list
    return iter->curr == NULL;
}

Iterador getIteratorNext(List L, Iterador it)
{
    ListImpl *lst = (ListImpl *) L;
    IteratorImpl *iter = (IteratorImpl *) it;

    if (isIteratorEmpty(L, it))
        return NULL;
    else
        if (iter->reverso == false)
            iter->curr = iter->curr->prox;
        else
            iter->curr = iter->curr->ant;
    return iter;
}

Item getIteratorItem(List L, Iterador it)
{
    ListImpl *lst = (ListImpl *) L;
    IteratorImpl *iter = (IteratorImpl *) it;
    return iter->curr->info;
}

Posic getIteratorPosic(List L, Iterador it)
{
    ListImpl *lst = (ListImpl *) L;
    IteratorImpl *iter = (IteratorImpl *) it;
    return iter->curr;
}

void killIterator(List L, Iterador it)
{
    IteratorImpl *iter = (IteratorImpl *) it;
    free(iter);
}





/**
 ** High-order functions
 **/
typedef Item (*Apply)(Item item);
typedef bool (*Check)(Item item);
typedef void (*ApplyClosure)(Item item, Clausura c);

List map(List L, Apply f)
{
    ListImpl *lst = (ListImpl *) L;
    ListImpl *newLst = (ListImpl *) createLst(lst->capac);

    for (Node * node = lst->prim; node != NULL; node = node->prox)
        insertLst(newLst, f(node->info));
    return newLst;
}

List filter(List L, Check f)
{
    ListImpl *lst = (ListImpl *) L;
    ListImpl *newLst = (ListImpl *) createLst(lst->capac);

    for (Node * node = lst->prim; node != NULL; node = node->prox)
        if (f(node->info))
            insertLst(newLst, node->info);
    return newLst;
}

void fold(List L, ApplyClosure f, Clausura c)
{
    ListImpl *lst = (ListImpl *) L;
    for (Node * node = lst->prim; node != NULL; node = node->prox)
        f(node->info, c);
}

List filterClausure(List L, CheckClausure f, Clausura c)
{
    ListImpl *lst = (ListImpl *) L;
    ListImpl *newLst = (ListImpl *) createLst(lst->capac);

    for (Node * node = lst->prim; node != NULL; node = node->prox)
        if (f(node->info, c))
            insertLst(newLst, node->info);
    return newLst;
}