#ifndef _LISTA_H
#define _LISTA_H

#include "dataTypes.h"
#include <stdbool.h>

/**
Uma list é uma colecao ordenada de itens (ou seja, um elemento possui um 
antecessor e um sucessor)  em que seus elementos podem
ser acessados atraves de sua posicao (tipo Posic). 
Uma list sem nenhum elemento (comprimento 0) é denominada list vazia.

Uma instancia do tipo Posic indica a posicao de um item dentro da list. 
Este tipo possui um valor invalido que indica nao se referir a nenhum item. 
Tal valor invalido e' denotado por NIL.

Este modulo prove diversos iteradores: 1 deles genérico e 3 comuns a linguagens
de programacao funcionais (high-order functions).
*/

typedef void * List;
typedef void * Posic;

typedef void * Iterador;
typedef void * Clausura;

#define NIL NULL;
#define CAPAC_ILIMITADA -1

/** Retorna uma list vazia. A list pode definir um limite maximo de 
elementos armazenados (capacidade). Caso capacidade < 0, o tamanho da list � 
ilimitado */
List createLst(int capacidade);

void setIteratorPosition(List L, Iterador it, Posic p);

/** Retorna o numero de elementos da list. */
int lengthLst(List L);

/** Retorna a capacidade da list. Retorna -1, se a capacidade � ilimitada */
int maxLengthLst(List L);

/** Retorna verdadeiro se a list L estiver vazia */
bool isEmptyLst(List L);

/** Retorna verdadeiro se a list L estiver cheia. Ou seja, se a list
   tiver sido criada com uma capacidade m�xima e lenght(L) == maxLength(L). */
bool isFullLst(List L);

/**  Insere o item info no final da list L. O comprimento da
list e' acrescido de 1 elemento. 
Retorna um indicador para o elemento acrescentado; ou NIL, se a list estiver
cheia */
Posic insertLst(List L, Item info);

/** Remove e retorna o primeiro elemento da list L. 
    A list nao pode  estar vazia */
Item popLst(List L);

/** Remove o elemento da list L indicado por p.  p deve indicar um elemento existente em L. O comprimento da list e' diminuido de 1 elemento. */
void removeLst(List L, Posic p);

/** Retorna o valor do item da list indicado por p.
    p deve indicar um elemento existente em L. */
Item getLst(List L, Posic p);

/** Insere o item info na posicao imediatamente anterior ao
item indicado por p. O comprimento da list e' acrescido de 1 elemento.
Retorna um indicador para o elemento acrescentado. p deve indicar um 
elemento existente em L.*/
Posic insertBeforeLst(List L,Posic p, Item info);
 

/** Insere o item info na posicao imediatamente posterior ao
item indicado por p. O comprimento da list e' acrescido de 1 elemento.
Retorna um indicador para o elemento acrescentado. p deve indicar um 
elemento existente em L.*/
Posic insertAfterLst(List L,Posic p, Item info); 

/** Retorna o indicador do primeiro elemento de L. Se
length(L)=0, retorna NIL. */
Posic getFirstLst(List L);

/** Retorna o indicador do elemento de L seguinte ao elemento
indicado por p. Se p for o ultimo elemento da list, retorna NIL.
p deve indicar um elemento existente em L.*/
Posic getNextLst(List L,Posic p);

/** Retorna o indicador do ultimo elemento de L. Se
length(L)=0, retorna NIL.*/
Posic getLastLst(List L);

/** Retorna o indicador do elemento de L anterior ao elemento
indicado por p. Se p for o primeiro elemento da list, retorna NIL.
p deve indicar um elemento existente em L. */
Posic getPreviousLst(List L,Posic p);

/** Libera toda memoria alocada pela list. */
void killLst(List L);

/**
 ** Iteradores
 **
 ** (nota: existe uma certa redundancia com getFirst, getLast, 
 **  getNext e getPrevious).
 **/

/**
   Retorna um iterador sobre a list L. 
   O iterador "anda" do inicio ate' o fim, caso reverso for falso;
   do fim para o inicio, se reverso for verdadeiro.
 */
Iterador createIterador(List L, bool reverso);

/**
   Retorna verdadeiro caso o iterador esteja esgotado,
   i.e., todos os item ja' tenham sido retornados; falso,
   caso contrario.
 */
bool isIteratorEmpty(List L, Iterador it);

/**
   Retorna o proximo item. O iterador nao deve estar esgotado.
   Caso o item retornado seja o ultima, subsequentes invocacoes
   a isIteratorEmpty retornam verdadeiro.
 */
Iterador getIteratorNext(List L, Iterador it);

Item getIteratorItem(List L, Iterador it);
Posic getIteratorPosic(List L, Iterador it);

/**
   Libera os recursos usados pelo iterador.
 */
void killIterator(List L, Iterador it);

/**
 ** High-order functions
 **/


typedef Item (*Apply)(Item item);
typedef bool (*Check)(Item item);
typedef bool (*CheckClausure)(Item item, Clausura c);
typedef void (*ApplyClosure)(Item item, Clausura c);

/** Cria uma nova list. Aplica a funcao f a cada item de L
    e insere o resultado na nova list.
 */
List map(List L, Apply f);

/**
   Cria uma nova list contendo os itens de L para os quais a
   invocacao da funcao f retornar verdeira.
 */
List filter(List L, Check f);

/**
   Aplica a funcao f a cada elemento de L, possivelmente, atualizando
   o conteudo de c.
 */
void fold(List L, ApplyClosure f, Clausura c);

/**
   Cria uma nova list contendo os itens de L para os quais a
   invocacao da funcao f retornar verdeira.
 */
List filterClausure(List L, CheckClausure f, Clausura c);

#endif
