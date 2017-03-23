#ifndef STATIC_ST_H
#define STATIC_ST_H

#include <iostream>
#include "symbol_table.h"

template <class Item, class Key>
class StaticSt : public ST<Item, Key> {
  Item* arr;
  Item null_item;
  int n;
  bool recursion;
  Item bsearchR (int l, int r, Key k);
  Item bsearchI (int l, int r, Key k);
  void sort (void);

 public:
  StaticSt (Item a[], int sz, bool rec = true):arr(a), n(sz), recursion(rec) {sort();}
  ~StaticSt () {}
  int count (void) {return n;}
  void insert (Item item);
  Item search (Key k);
  void remove (Item item);
  Item select (int k);
  void visit (void);
};

template <class Item, class Key>
void StaticSt<Item, Key>::sort (void) {
  for (int i = 1; i < n; ++i) {
    Item tmp = arr[i];
    int j = i;
    while (j >= 1 && arr[j-1].key() > tmp.key()) {
      arr[j] = arr[j-1];
      j--;
    }
    arr[j] = tmp;
  }
}

template <class Item, class Key>
Item StaticSt<Item, Key>::bsearchR (int l, int r, Key k) {
  if (r < l) return null_item; 
  int m = (l + r) / 2;
  if (arr[m].key() == k) return arr[m];
  if (arr[m].key() > k) return bsearchR(l, m-1, k);
  else return bsearchR(m+1, r, k);
}

template <class Item, class Key>
Item StaticSt<Item, Key>::bsearchI (int l, int r, Key k) {
  while (l <= r) {
    int m = (l + r) / 2;
    if (arr[m].key() == k) return arr[m];
    if (arr[m].key() > k) r = m-1;
    else l = m+1;
  }
  return null_item;
}

template <class Item, class Key>
Item StaticSt<Item, Key>::search (Key k) {
  if (recursion) return bsearchR(0, n-1, k);
  else return bsearchI(0, n-1, k);
}

template <class Item, class Key>
void StaticSt<Item, Key>::insert (Item item) {
  //static st : no insert
}

template <class Item, class Key>
void StaticSt<Item, Key>::remove (Item item) {
  //static st : no remove
}

template <class Item, class Key>
Item StaticSt<Item, Key>::select (int k) {
  if (k>=n) return null_item;
  else return arr[k];
}

template <class Item, class Key>
void StaticSt<Item, Key>::visit (void) {
  for (int i = 0; i < n; ++i) {
    std::cout << arr[i];
  }
}

#endif
