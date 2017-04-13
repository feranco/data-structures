#ifndef BST_ST_H
#define BST_ST_H

#include <iostream>
#include "symbol_table.h"
#include <stack>  //for iterative root insert

template <class Item, class Key>
class BstSt : public ST<Item, Key> {
  struct Node {
    Item item;
    Node* left, *right;
    int size;
    Node (Item x):item(x), left(0), right(0), size(1){}
  };
  typedef Node* Link;
  Link head;
  bool recursive;
  Item null_item;
  
  //recursive 
  void insertR (Link& v, Item item);
  void insertRootR (Link& v, Item item);
  Item searchR (Link v, Key k);
  void visitR (Link v);
  bool removeR (Link& v, Key k);
  Item selectR (Link v, int k);
  void rotLeft (Link& v);
  void rotRight (Link& v);
  int  size (Link v);
  void partitionR (Link& v, int k);
  void joinLRChild (Link& v);
  void joinR (Link& headL, Link headR);
  void balanceR (Link& v);
  void fixSize (Link v);

  //iterative
  void insertI (Item item);
  void insertRootI (Item item);
  Item searchI (Key k);
  Item selectI (int k);

  //for debug
  void dumpIntNode(std::ostream& os, Item v, int h) const;
  void dumpExtNode(std::ostream& os, int h) const; 
  void dump(std::ostream& os, Link t, int h) const;
public:
  BstSt (bool rec = true):head(0), recursive(rec){}
  int count (void) {return head->size;}
  void insert (Item item);
  void insertRoot (Item item);
  Item search (Key k);
  void remove (Item item);
  Item select (int k);
  void visit (void);
  void partition (int k) { partitionR(head,k);}
  void balance (void) {balanceR(head);}
  void join(BstSt<Item, Key>& rhs);

  Item lowestAncestor (Key a, Key  b);
  Item lowestAncestorR (Link v, Key a, Key  b);
  Item lowestAncestorI (Key a, Key  b);

  friend std::ostream& operator<< (std::ostream& os, const BstSt& rhs) {
    rhs.dump(os, rhs.head, 0);
    return os;
    }
};

template <class Item, class Key>
Item BstSt<Item, Key>::lowestAncestor (Key a, Key  b) {
  if (recursive) return lowestAncestorR (head, a, b);
  else return lowestAncestorI(a,b);
}

template <class Item, class Key>
Item BstSt<Item, Key>::lowestAncestorR (Link v, Key a, Key  b) {
  if (a == b) return null_item;
  Key k = v->item.key();
  if (a < k && b < k) return lowestAncestorR(v->left, a, b);
  if (a > k && b > k) return lowestAncestorR(v->right, a, b);
  return v->item;
}

template <class Item, class Key>
Item BstSt<Item, Key>::lowestAncestorI (Key a, Key  b) {
  Link v = head;
  while (v) {
     Key k = v->item.key();
     if (a < k && b < k) { v = v->left; continue;}
     if (a > k && b > k) {v = v->right; continue;}
     return v->item;
  }
  return null_item;
}

template <class Item, class Key>
void BstSt<Item, Key>::join(BstSt<Item, Key>& rhs) {
  joinR(head, rhs.head);
}

template <class Item, class Key>
  void BstSt<Item, Key>::joinR(Link& headL, Link headR) {
  if (!headR) return;
  if (!headL) { headL = headR; return;}
  insertRootR(headL, headR->item);
  joinR(headL->left, headR->left);
  joinR(headL->right, headR->right);
  delete(headR);
}

#if 0
//with references
template <class Item, class Key>
  Link BstSt<Item, Key>::joinR(Link headL, Link headR) {
  if (!headR) return headL;//return
  if (!headL) return headR;//headL = headR;
  insertRootR(headL, headR->item);
  headL->left = joinR(headL->left, headR->left);
  headL->right = joinR(headL->right, headR->right);
  delete(headR);
  return headL;
}
#endif

//public interfaces

template <class Item, class Key>
void BstSt<Item, Key>::insert (Item item) {
  if (recursive) return insertR(head, item);
  else return insertI(item);
}

template <class Item, class Key>
Item BstSt<Item, Key>::search (Key k) {
  if (recursive) return searchR(head, k);
  else  return searchI(k);
}

template <class Item, class Key>
void BstSt<Item, Key>::remove (Item item) {
  removeR(head, item.key());
}

template <class Item, class Key>
Item BstSt<Item, Key>::select (int k) {
  if (recursive) return selectR(head, k);
  else return selectI(k);
}

template <class Item, class Key>
void BstSt<Item, Key>::visit (void) {
  //first sort the list and then print nodes
  std::cout << *this;
  //visitR(head);
}

template <class Item, class Key>
void BstSt<Item, Key>::insertRoot (Item item) {
  if (recursive) insertRootR(head, item);
  else insertRootI(item);
}

//recursive

template <class Item, class Key>
Item BstSt<Item, Key>::searchR (Link v, Key k) {
  if (v == 0) return null_item;
  Key v_key = v->item.key();
  if (v_key == k) return v->item;
  if (v_key >  k) return searchR(v->left, k);
  else return searchR(v->right, k); 
}

template <class Item, class Key>
void BstSt<Item, Key>::insertR (Link& v, Item item) {
  if (!v) {
    v = new Node(item);
    return;
  }
  if (item.key() < v->item.key()) insertR(v->left, item);
  else insertR(v->right, item);
  v->size++;
}

template <class Item, class Key>
  bool BstSt<Item, Key>::removeR (Link& v, Key k) {
  if (v == 0) return false;//item is not in the ST
  Key v_key = (v->item.key());
  if (k == v_key) {
    Link tmp = v;
    std::cout << "remove " << v_key << std::endl;
    partitionR(v->right, 0);
    if (v->right) this->dump(std::cout, v->right, 0);
    joinLRChild(v);
    delete tmp;
    return true;//no need of this return putting the if at the end
  }
  if (v_key > k) {
    if(removeR(v->left, k)) { v->size--; return true;}
  }
  else {
    if(removeR(v->right, k)) {v->size--; return true;}
  }  
  return false;
}

template <class Item, class Key>
void BstSt<Item, Key>::joinLRChild (Link& v) {
  if (!v->right) {
    v = v->left;
    return;
  }
  v->right->left = v->left;
  v = v->right;
}

#if 0
template <class Item, class Key>
void BstSt<Item, Key>::joinLRChild (Link& v) {
  if (!v->right) {
    v = v->left;
    return;
  }
  partitionR(v->right, 1);
  v->right->left = v->left;
  v = v->right;
}
#endif

template <class Item, class Key>
void BstSt<Item, Key>::partitionR (Link& v, int k) {
  //if (!v || k == 0) return;
  int l_size = size(v->left);
  if (l_size+1 == k) return;
  if (k <= l_size) {
    partitionR(v->left, k);
    rotRight(v);
  }
  else {
    partitionR(v->right, k-l_size-1);
    rotLeft(v);
  }
}

template <class Item, class Key>
void BstSt<Item, Key>::balanceR (Link& v) {
  if (size(v) <= 1) return;
  partitionR(v, size(v)/2 + 1);
  balanceR(v->left);
  balanceR(v->right);
}

template <class Item, class Key>
void BstSt<Item, Key>::insertRootR (Link& v, Item item) {
  if (v == 0) {
    v = new Node(item);
    return;
  }
  if (item.key() < v->item.key()) {
    insertRootR(v->left, item);
    rotRight(v);
  }
  else {
    insertRootR(v->right, item);
    rotLeft(v);
  }
}

//traverse recursively the tree checking the left subtree size:
//1) if left subtree size + 1 is equal to k, then the current node is the k-th
//2) if left subtree size is >= k, then the k-th node is in the left subtree
//3) if left subtree size is < k, then the k-th node is in the right subtree
template <class Item, class Key>
Item BstSt<Item, Key>::selectR (Link v, int k) {
  if (!v) return null_item; //not necessary if k is checked against the tree size in the wrapper function
  int l_size = size(v->left);
  if (l_size + 1 == k) return v->item;
  if (k <= l_size) return selectR(v->left, k);
  else  return selectR(v->right, k-sz-1);
}

template <class Item, class Key>
void BstSt<Item, Key>::visitR (Link v) {
  if(!v) return;
  visitR(v->left);
  std::cout << v->item;
  visitR(v->right);
}

//left rotation: swap v with its right child r
//v become the left child of r
//the left child of r become the right child of v
//IMPORTANT: not swap instruction 2 with 3
template <class Item, class Key>
void BstSt<Item, Key>::rotLeft  (Link& v) {
  Link tmp = v->right;//save r
  v->right = tmp->left;//left child of r become the right child of v
  tmp->left = v;//v become left child of r
  v = tmp;//swap
  fixSize(v->left);
  fixSize(v);
}

//right rotation: swap v with its left child l
//v become the right child of l
//the right child of l become the left child of v
template <class Item, class Key>
void BstSt<Item, Key>::rotRight  (Link& v) {
  Link tmp = v->left;
  v->left = tmp->right;
  tmp->right = v;
  v = tmp;
  fixSize(v->right);
  fixSize(v);
}

//iterative

template <class Item, class Key>
Item BstSt<Item, Key>::searchI (Key k) {
  Link v = head;
  while (v) {
     Key v_key = v->item.key();
     if (v_key == k) return v->item;
     if (k < v_key) v = v->left;
     else v = v->right; 
  }
  return null_item;
}

template <class Item, class Key>
void BstSt<Item, Key>::insertI (Item item) {

  if (!head) {head =  new Node(item); return;}
  
  Link v = head;
  Link p = 0;
  Key k = item.key();
  
  while (v) {
     v->size++;
     p = v;
     if (k < v->item.key()) v = v->left;
     else v = v->right;
  }
  if (k < p->item.key()) p->left = new Node(item);
  else  p->right = new Node(item);
}

template <class Item, class Key>
Item BstSt<Item, Key>::selectI (int k) {
  Link v = head;
  int l_size = size(v->left);

  while (l_size+1 != k) {
    if (l_size >= k) {
      v = v->left;
    }
    else {
      v = v->right;
      k = k - l_size -1;
    }
    l_size = size(v->left);
  }
  return v->item;
}

template <class Item, class Key>
void BstSt<Item, Key>::insertRootI (Item item) {

  if (!head) {head =  new Node(item); return;}

  std::stack<Link> s;
  Link v = head;
  Link p = 0;
  Key k = item.key();
  
  while (v) {
     v->size++;
     p = v;
     if (k < v->item.key()) v = v->left;
     else v = v->right;
  }
  if (k < p->item.key()) p->left = new Node(item);
  else  p->right = new Node(item);

  while (!s.empty()) {
    v = s.top();
    s.pop();
    if (k < v->item.key()) rotRight(v);
    else rotLeft(v);
  }
}

//utility

template <class Item, class Key>
void BstSt<Item, Key>::fixSize (Link v) {
  v->size = size(v->left) + size(v->right) + 1;
}

template <class Item, class Key>
int BstSt<Item, Key>::size (Link v) {
  if (!v) return 0;
  else return v->size;
}

//print internal node
template <class Item, class Key>
void BstSt<Item, Key>::dumpIntNode(std::ostream& os, Item v, int h) const {
  for (int i = 0; i < h; ++i) os << "  ";
  os << v.key() << std::endl;
}

//print external node
template <class Item, class Key>
void BstSt<Item, Key>::dumpExtNode(std::ostream& os, int h) const {
  for (int i = 0; i < h; ++i) os << "  ";
  os << '*' << std::endl;
}

//print (sub)tree
template <class Item, class Key>
void BstSt<Item, Key>::dump(std::ostream& os, Link t, int h) const {
  if (t == 0) { dumpExtNode(os, h); return; }

  dump(os, t->right, h + 3);
  dumpIntNode(os, t->item, h);
  dump(os, t->left, h + 3);
}

#endif
