#ifndef ADJ_LIST_GRAPH_H
#define ADJ_LIST_GRAPH_H

#include <iostream>

class Graph {
  struct Node {
    int v;
    Node* next;
    Node (int x):v(x), next(0) {};
  };
  typedef Node* Link;
  int  v, e; //number of vertex and edges
  Link* adj;
  bool rec;

  bool validateVertex (int v) const;
  void bfsR (int v, bool visited[]);

 public:
  Graph (int n, bool r = true);
  Graph(std::ifstream& ifs, bool r = true);
  void addEdge (int v1, int v2);
  void bfs (int v);
  friend std::ostream& operator<<(std::ostream& os, const Graph& rhs);
};


#endif
