#ifndef ADJ_LIST_GRAPH_H
#define ADJ_LIST_GRAPH_H

class Graph {
  struct Node {
    int item;
    Node* next;
    Node (int x):item(x), next(0) {};
  };
  typedef Node* Link;
  int  n_vertex;
  Link vertex;
  bool* visited;

 public:
  Graph (int n): n_vertex(n) {vertex = new Node[n]; visited = new bool[n];}
  addEdge (int v1, int v2);
  
};

Graph::addEdge (int v1, int v2){
  Link tmp = vertex[v1];
  vertex[v1] = new Node(v2);
  vertex[v1]->next = tmp;

  Link tmp = vertex[v2];
  vertex[v2] = new Node(v2);
  vertex[v2]->next = tmp;
}

#endif
