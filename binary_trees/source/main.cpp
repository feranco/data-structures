#include <iostream>
#include "binary_tree.h"
using namespace std;

int main(int argc, char* argv[])
{

  const char*s = "1100100";
  const char*l = "dbacfeg";
  BT<char> bt(s, l, false);
  std::cout << bt;
  std::cout << "height: " << bt.height() << endl;
  std::cout << "preorder: ";
  bt.preorder();
  std::cout << endl << "inorder: ";
  bt.inorder();
  std::cout << endl << "postorder: ";
  bt.postorder();
  return 0;
}

 

