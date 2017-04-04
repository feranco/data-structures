#include "adj_list_graph.h"
#include <ifstream>
#include <stdexcept>

Graph (int n): v(n), e(0) {
  adj = new Link[n]; 
  visited = new bool[n];
  for (int i = 0; < v; ++i) {
    adj[i] = 0;
    visited [i] = false;
  }
}

Graph(std::ifstream& ifs) {
  try {
    ifs >> v >> e;
    if (v <= 0) throw std::invalid_argument("number of vertices in a Graph must be nonnegative");
    if (e < 0) throw std::invalid_argument("number of edges in a Graph must be nonnegative");
    adj = new Link[v];
    int v1, v2;
    while (ifs >> v1 >> v2) {

    }
   
    int E = in.readInt();
    if (E < 0) throw new IllegalArgumentException("number of edges in a Graph must be nonnegative");
    for (int i = 0; i < E; i++) {
      int v = in.readInt();
      int w = in.readInt();
      validateVertex(v);
      validateVertex(w);
      addEdge(v, w); 
    }
  }
  catch (NoSuchElementException e) {
    throw new IllegalArgumentException("invalid input format in Graph constructor", e);
  }
}

bool Graph::validateVertex (int v) const{
  if (v >= 0 && v <= this->v) return true;
  else return false; 
}

void Graph::addEdge (int v1, int v2){
  if (!validateVertex(v1) || !validateVertex(v2)) return;

  //Add v1->v2
  Link tmp = adj[v1];
  adj[v1] = new Node(v2);
  adj[v1]->next = tmp;
  
  //Add v2->v1
  tmp = adj[v2];
  adj[v2] = new Node(v2);
  adj[v2]->next = tmp;
}
