#ifndef GRAPH_H
#define GRAPH_H

#include "dataTypes.h"
#include "list.h"

typedef void * Graph;
typedef void * Vertex;
typedef void * Edge;

Graph    createGraph       ();
int      getVtxCount       (Graph gph);
List     getGraphVtxList   (Graph gph);
void     removeGraph       (Graph gph);
void     removeAllGraph    (Graph gph);


Vertex   createVertex      (int id, Item item);
void     connectVtx        (Vertex vtx1, Vertex vtx2);
void     disconnectVtx     (Vertex vtx1, Vertex vtx2);
Vertex   copyVertex        (Vertex vtx);
void     removeVertex      (Vertex vtx);

void     setVtxOrigin      (Vertex vtx, Graph gph);
void     setVtxID          (Vertex vtx, int id);
void     setVtxItem        (Vertex vtx, Item item);
//void     setVtxDegree      (Vertex vtx, int degree);
//void     setVtxConnections (Vertex vtx, List lst);

Graph    getVtxOrigin      (Vertex vtx);
int      getVtxID          (Vertex vtx);
Item     getVtxItem        (Vertex vtx);
int      getVtxDegree      (Vertex vtx);
List     getVtxConnections (Vertex vtx);


Vertex   findVtxByIDinGraph(Graph gph, int id);

#endif