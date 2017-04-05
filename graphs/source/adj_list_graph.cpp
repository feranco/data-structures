#include "adj_list_graph.h"
#include <fstream>
#include <stdexcept>

Graph::Graph (int n, bool r = true): v(n), e(0), rec(r) {
  adj = new Link[n]; 
  for (int i = 0; i < v; ++i) adj[i] = 0;
}

Graph::Graph(std::ifstream& ifs, bool r = true): v(0), e(0), rec(r) {
  ifs >> v;
  if (v <= 0) throw std::invalid_argument("number of vertices in a Graph must be nonnegative");
  adj = new Link[v];

  for (int i = 0; i < v; ++i) adj[i] = 0;

  int v1, v2;
  while (ifs >> v1 >> v2) addEdge(v1,v2);
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
  adj[v2] = new Node(v1);
  adj[v2]->next = tmp;

  ++e;
}

void Graph::bfs (int v) {
  if (!validateVertex(v)) return;
  bool* visited = new bool[this->v];
  std::cout << "bfs:  ";
  if (rec) bfsR(v, visited); 
}

void bfsR (int v, bool visited[]) {
  if (!visited[v]) {
    std::cout << v << " ";
    visited[v] = true;
  }

  for (auto t = adj[v]; t != 0; t = t->next) {
    bfsR(t->v, visited);
  }
}

std::ostream& operator<<(std::ostream& os, const Graph& rhs) {
  os << rhs.v << " vertices " << rhs.e << " edges" << "\n";
  for (int i = 0; i < rhs.v; ++i) {
    os << i << ": ";
    for (auto t = rhs.adj[i]; t != 0; t = t->next) os << t->v << " ";
    os << "\n"; 
  }
  return os;
}
