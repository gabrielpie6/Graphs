#include "graph.h"

#include <stdlib.h>

typedef struct StGraph {
    // numero de vertices
    int vertexCount;
    // numero de arestas
    int edgeCount;
    // lista de ponteiros para vertices do grafo
    List vertexList;
} graph;

typedef struct StVertex {
    // idenficador do vertice (deve ser único)
    int id;
    // ponteiro para o item do vertice
    Item item;
    // lista de ponteiros para arestas do vertice
    List connections;
    int degree;
    // ponteiro para o grafo ao qual o vertice pertence
    Graph origin;
} vertex;

Graph createGraph()
{
    graph * g = (graph *) malloc(sizeof(graph));
    g->vertexCount = 0;
    g->edgeCount = 0;
    g->vertexList = createLst(CAPAC_ILIMITADA);
    return (Graph) g;
}

int      getVtxCount       (Graph gph)
{
    graph * g = (graph *) gph;
    return g->vertexCount;
}

List     getGraphVtxList   (Graph gph)
{
    graph * g = (graph *) gph;
    return g->vertexList;
}

void     removeGraph       (Graph gph)
{
    graph * g = (graph *) gph;
    free(g);
}






Vertex createVertex(int id, Item item)
{
    vertex * v = (vertex *) malloc(sizeof(vertex));
    v->id = id;
    v->item = item;
    v->connections = createLst(CAPAC_ILIMITADA);
    v->degree = 0;
    v->origin = NULL;
    return (Vertex) v;
}

void connectVtx(Vertex vtx1, Vertex vtx2)
{
    vertex * v1 = (vertex *) vtx1;
    vertex * v2 = (vertex *) vtx2;
    // adiciona v2 na lista de arestas de v1
    insertLst(v1->connections, (Item) vtx2);
    v1->degree++;
    // adiciona v1 na lista de arestas de v2
    insertLst(v2->connections, (Item) vtx1);
    v2->degree++;

    // Faltam realizar mais operações de casos especiais, mas por enquanto está satisfatório
}

Posic getVtxPosicByIDInLst (List lst, int id)
{
    vertex * aux;
    Posic p;

    for (p = getFirstLst(lst); p != NIL p = getNextLst(lst, p))
    {
        aux = (vertex *) getLst(lst, p);
        if (aux->id == id)
            break;
    };
    return p;
}

void     disconnectVtx     (Vertex vtx1, Vertex vtx2)
{
    vertex * v1 = (vertex *) vtx1;
    vertex * v2 = (vertex *) vtx2;

    
    // remove v2 da lista de arestas de v1
    removeLst(v1->connections, getVtxPosicByIDInLst(v1->connections, getVtxID(vtx2)));
    v1->degree--;

    // remove v1 da lista de arestas de v2
    removeLst(v2->connections, getVtxPosicByIDInLst(v2->connections, getVtxID(vtx1)));
    v2->degree--;
}


void     setVtxOrigin      (Vertex vtx, Graph gph)
{
    vertex * v = (vertex *) vtx;
    graph * g;
    if (v->origin != NULL)
    {
        g = (graph *) v->origin;
        removeLst(g->vertexList, getVtxPosicByIDInLst(g->vertexList, getVtxID(vtx)));
        g->vertexCount--;
    }
    v->origin = gph;
    g = (graph *) gph;
    insertLst(g->vertexList, (Item) v);
    g->vertexCount++;
}
void     setVtxID          (Vertex vtx, int id)
{
    vertex * v = (vertex *) vtx;
    v->id = id;
}
void     setVtxItem        (Vertex vtx, Item item)
{
    vertex * v = (vertex *) vtx;
    v->item = item;
}
void     setVtxDegree      (Vertex vtx, int degree)
{
    vertex * v = (vertex *) vtx;
    v->degree = degree;
}
void     setVtxConnections (Vertex vtx, List lst)
{
    vertex * v = (vertex *) vtx;
    v->connections = lst;
}

Graph    getVtxOrigin      (Vertex vtx)
{
    vertex * v = (vertex *) vtx;
    return v->origin;
}
int      getVtxID          (Vertex vtx)
{
    vertex * v = (vertex *) vtx;
    return v->id;
}
Item     getVtxItem        (Vertex vtx)
{
    if (vtx == NULL)
        return NULL;
    else
    {
        vertex * v = (vertex *) vtx;
        return v->item;
    }
}
int      getVtxDegree      (Vertex vtx)
{
    vertex * v = (vertex *) vtx;
    return v->degree;
}
List     getVtxConnections (Vertex vtx)
{
    vertex * v = (vertex *) vtx;
    return v->connections;
}

/*
    Deve buscar dentro da lista de vertices pertencentes ao grafo gph o vertice
    que possui o id passado como parâmetro. Considere que o id é único. Se não
    encontrar, deve retornar NULL.
*/
Vertex   findVtxByIDinGraph(Graph gph, int id)
{
    graph * g = (graph *) gph;
    vertex * vtx;
    for (Posic p = getFirstLst(g->vertexList); p != NULL; p = getNextLst(g->vertexList, p))
    {
        vtx = (vertex *) getLst(g->vertexList, p);
        if (vtx->id == id)
            return (Vertex) vtx;
    }
    return NULL;
}