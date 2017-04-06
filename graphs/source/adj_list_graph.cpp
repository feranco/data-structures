#include "adj_list_graph.h"
#include <fstream>
#include <stdexcept>
#include <stack>
#include <queue>

Graph::Graph (int n, bool r): v(n), e(0), rec(r) {
  adj = new Link[n]; 
  for (int i = 0; i < v; ++i) adj[i] = 0;
}

Graph::Graph(std::ifstream& ifs, bool r): v(0), e(0), rec(r) {
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

/**
 * Depth first search interface
 * @param v the source vertex
 */
void Graph::dfs (int v) {
  if (!validateVertex(v)) return;
  bool* visited = new bool[this->v];
  for (int i = 0; i < v; ++i) visited[i] = false;
  std::cout << "dfs:  ";
  if (rec) dfsR(v, visited);
  else dfsI(v, visited);
}

/**
 * Depth first search recursive implementation
 * @param v: the current vertex
 * @param visited: already visited vertices
 */
void Graph::dfsR (int v, bool visited[]) {
  if (visited[v]) return;
    
  std::cout << v << " ";
  visited[v] = true;

  for (auto t = adj[v]; t != 0; t = t->next) {
    dfsR(t->v, visited);
  }
}

/**
 * Depth first search iterative implementation
 * @param v: the current vertex
 * @param visited: already visited vertices
 */
void Graph::dfsI (int v, bool visited[]) { 
  std::stack<int> s;
  s.push(v);
  
  while (!s.empty()) {

    int curr = s.top();

    if (!visited[curr]) {
      std::cout << curr << " ";
      visited[curr] = true;
    }

    auto t = adj[curr];
    for (; t != 0; t = t->next) {
      if (!visited[t->v]) {
	s.push(t->v);
	break;
      }
    } 
    //pop a vertex only if its adj list has been visited
    if (!t) s.pop();   
  }
}

/**
 * Breadth first search interface
 * @param v the source vertex
 */
void Graph::bfs (int v) {
  if (!validateVertex(v)) return;
  bool* visited = new bool[this->v];
  for (int i = 0; i < v; ++i) visited[i] = false;
  std::cout << "bfs:  ";
 
  std::queue<int> s;
  s.push(v);
  
  while (!s.empty()) {
     
    int curr = s.front();
    s.pop();
    if (!visited[curr]) {
      std::cout << curr << " ";
      visited[curr] = true;
    }

    for (auto t = adj[curr]; t != 0; t = t->next) {
      if (!visited[t->v]) s.push(t->v);
    } 
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
