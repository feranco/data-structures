#ifndef BST_ST_H
#define BST_ST_H

#include <iostream>
#include "symbol_table.h"

template <class Item, class Key>
class BstSt : public ST<Item, Key> {
  struct Node {
    Item item;
    Node* left, *right;
    Node (Item x):item(x), left(0), right(0){}
  };
  typedef Node* Link;
  bool recursive;
  Item null_item;
  Link head;
  int n;
  
  void insertI (Item item);
  void insertR (Link& v, Item item);
  Item searchI (Key k) ;
  Item searchR (Link v, Key k) ;

  //for debug
  void dumpIntNode(std::ostream& os, Item v, int h) const;
  void dumpExtNode(std::ostream& os, int h) const; 
  void dump(std::ostream& os, Link t, int h) const;
public:
  BstSt (bool rec = true):head(0), recursive(rec){}
  int count (void) {return n;}
  void insert (Item item);
  Item search (Key k);
  void remove (Item item);
  Item select (int k);
  void visit (void);
};

template <class Item, class Key>
void BstSt<Item, Key>::dumpIntNode(std::ostream& os, Item v, int h) const {
  for (int i = 0; i < h; ++i) os << "  ";
  os << v.key() << std::endl;
}

template <class Item, class Key>
void BstSt<Item, Key>::dumpExtNode(std::ostream& os, int h) const {
  for (int i = 0; i < h; ++i) os << "  ";
  os << '*' << std::endl;
}

template <class Item, class Key>
void BstSt<Item, Key>::dump(std::ostream& os, Link t, int h) const {
  if (t == 0) { dumpExtNode(os, h); return; }

  dump(os, t->right, h + 3);
  dumpIntNode(os, t->item, h);
  dump(os, t->left, h + 3);
}

template <class Item, class Key>
Item BstSt<Item, Key>::search (Key k) {
  if (recursive) return searchR(head, k);
  else  return searchI(k);
}

template <class Item, class Key>
Item BstSt<Item, Key>::searchR (Link v, Key k) {
  if (v == 0) return null_item;
  Key v_key = v->item.key();
  if (v_key == k) return v->item;
  if (v_key >  k) return searchR(v->left, k);
  else return searchR(v->right, k); 
}

template <class Item, class Key>
Item BstSt<Item, Key>::searchI (Key k) {
  Link tmp = head;
  while (tmp) {
     Key v_key = tmp->item.key();
     if (v_key == k) return tmp->item;
     if (v_key >  k) tmp = tmp->left;
     else tmp = tmp->right; 
  }
  return null_item;
}

template <class Item, class Key>
void BstSt<Item, Key>::insert (Item item) {
  if (recursive) return insertR(head, item);
  else return insertI(item);
}

template <class Item, class Key>
void BstSt<Item, Key>::insertR (Link& v, Item item) {
  if (v == 0) v = new Node(item);
  Key v_key = v->item.key();
  if (v_key >  item.key()) insertR(v->left, item);
  else insertR(v->right, item); 
}

template <class Item, class Key>
void BstSt<Item, Key>::insertI (Item item) {
  Link tmp = head;
  Key k = item.key();
  while (tmp) {
     Key v_key = tmp->item.key();
     if (v_key >  k) {
       if (!tmp->left) {
	 tmp->left = new Node(item);
	 break;
       }
       tmp = tmp->left;
     }
     else {
        if (!tmp->right) {
	 tmp->right = new Node(item);
	 break;
       }
       tmp = tmp->right;
     } 
  }
}

template <class Item, class Key>
void BstSt<Item, Key>::remove (Item item) {
 
}

template <class Item, class Key>
Item BstSt<Item, Key>::select (int k) {
  //first sort the list and than return the k-th node
  return null_item;
}

template <class Item, class Key>
void BstSt<Item, Key>::visit (void) {
  //first sort the list and then print nodes
}

#endif
