#include "adj_list_graph.h"
#include <fstream>
using namespace std;
int main(int argc, char *argv[])
{
  ifstream ifs("/home/emh2/Desktop/code/projectG/graphs/source/tiny_graph.txt");
  Graph g(ifs, false);
  cout << g;
  g.bfs(0);
}
