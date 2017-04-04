#ifndef ADJ_LIST_GRAPH_H
#define ADJ_LIST_GRAPH_H

class Graph {
  struct Node {
    int v;
    Node* next;
    Node (int x):v(x), next(0) {};
  };
  typedef Node* Link;
  int  v, e; //number of vertex and edges
  Link* adj;
  bool* visited;

 public:
  Graph (int n): v(n), e(0) {adj = new Link[n]; visited = new bool[n];}
  void addEdge (int v1, int v2);
  
};


#endif
