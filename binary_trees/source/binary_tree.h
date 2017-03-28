#ifndef BINARY_TREES_H
#define BINARY_TREES_H

#include <iostream>
#include <algorithm> //max
#include <stack>

template <class Item>
class BT {
  struct Node {
    Item item;
    Node* left, *right;
    Node (Item x):item(x), left(0), right(0){}
  };
  typedef Node* Link;
  Link root;
  bool recursive;

  //iterative
  void preorderI (void);
  void inorderI (void);

  //recursive
  int heightR (Link v);
  void preorderR (Link v);
  void inorderR (Link v);

  //for debug
  void dumpIntNode(std::ostream& os, Item v, int h) const;
  void dumpExtNode(std::ostream& os, int h) const; 
  void dump(std::ostream& os, Link t, int h) const;

 public:
  BT (bool rec = true):root(0), recursive(rec) {};
  BT (const char* s, const char* l, bool rec = true):recursive(rec) {charBT(root, s, l);};
  void charBT (Link& v, const char* s, const char* l);

  int height (void) {return heightR(root);}
  void preorder (void) {if (recursive) preorderR(root); else preorderI();}
  void inorder (void) {if (recursive) inorderR(root); else inorderI();}

  friend std::ostream& operator<< (std::ostream& os, const BT& rhs) {
    rhs.dump(os, rhs.root, 0);
    return os;
  }
};

//build a tree with char nodes
//l contains the nodes
//s specify if the corresponding node in l is internal (1) or external/leaf (0)
//external nodes are specified only if they have a leaf as brother
template <class Item>
void BT<Item>::charBT (Link& v, const char* s, const char* l) {
   static int i = 0;
   static int j = 0;
   if (s[i++] == '0') {
      v = new Node(l[j++]);
      if (v->item == '*') v = 0; //Set fake nodes to null
    }
    else {
      v = new Node(l[j++]);
      charBT(v->left, s, l);
      charBT(v->right, s, l);
    }
}

template <class Item>
int BT<Item>::heightR (Link v) {
  if (!v) return 0;
  else return std::max(heightR(v->left), heightR(v->right)) + 1;
}

template <class Item>
void BT<Item>::preorderR (Link v) {
  if (!v) return;
  std::cout << v->item << " ";
  preorderR(v->left);
  preorderR(v->right);
}

template <class Item>
void BT<Item>::inorderR (Link v) {
  if (!v) return;
  preorderR(v->left);
  std::cout << v->item << " ";
  preorderR(v->right);
}


//iterative

//preorder traversal without recursion
template <class Item>
void BT<Item>::preorderI (void) {
  std::stack<Link> s;
  s.push(root);
  while (!s.empty()) {
    Link v = s.top();
    std::cout << v->item << " "; // print current node
    s.pop(); //pop it from the stack
    if (v->right) s.push(v->right); //push right subtree
    if (v->left) s.push(v->left); //push left subtree
  }
}

template <class Item>
void BT<Item>::inorderI (void) {
  std::stack<Link> s;
  s.push(root);
  while (!s.empty()) {
    Link v = s.top();
    while (v->left) {
      s.push(v->left);
      v = v->left;
    }
    v = s.top();
    std::cout << v;
    //s.pop();
    if (v->right) {
      std::cout << s.top();
      s.pop();
      s.push(v->right);
    }
  }
}

//print internal node
template <class Item>
void BT<Item>::dumpIntNode(std::ostream& os, Item v, int h) const {
  for (int i = 0; i < h; ++i) os << "  ";
  os << v << std::endl;
}

//print external node
template <class Item>
void BT<Item>::dumpExtNode(std::ostream& os, int h) const {
  for (int i = 0; i < h; ++i) os << "  ";
  os << '*' << std::endl;
}

//print (sub)tree
template <class Item>
void BT<Item>::dump(std::ostream& os, Link t, int h) const {
  if (t == 0) { dumpExtNode(os, h); return; }

  dump(os, t->right, h + 3);
  dumpIntNode(os, t->item, h);
  dump(os, t->left, h + 3);
}

#endif

