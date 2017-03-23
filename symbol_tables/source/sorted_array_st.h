#ifndef SORTED_ARRAY_ST_H
#define SORTED_ARRAY_ST_H

#include <iostream>
#include "symbol_table.h"

template <class Item, class Key>
class SortedArraySt : public ST<Item, Key> {
  static const int size = 1000;
  Item* arr;
  Item null_item;
  int n;
  Item bsearchR (int l, int r, Key k);
  Item bsearchI (int l, int r, Key k);
 public:
  SortedArraySt ():n(0) {arr = new Item[size];}
  ~SortedArraySt () {delete[] arr;}
  int count (void) {return n;}
  void insert (Item item);
  Item search (Key k);
  void remove (Item item);
  Item select (int k);
  void visit (void);
};

template <class Item, class Key>
void SortedArraySt<Item, Key>::bsearchR (int l, int r, Key k) {
  if (r < l) return null_item; 
  int m = l + r / 2;
  if (arr[m].key() == k) return arr[k];
  if (arr[m].key() > k) bsearch(l, m-1, k);
  else bsearch(m+1, r, k);
}

template <class Item, class Key>
void SortedArraySt<Item, Key>::bsearchI (int l, int r, Key k) {
  while (l <= r) {
    int m = l + r / 2;
    if (arr[m].key() == k) return a[m];
    if (arr[m].key() > k) r = m-1;
    else l = m+1;
  }
  return null_item;
}

template <class Item, class Key>
void SortedArraySt<Item, Key>::insert (Item item) {
  if (n >= size) return;
  int i = n;
  Key k = item.key();//prevent many function call during while
  while (i > 0 && arr[i-1].key() > k) {
    arr[i] = arr[i-1];
    --i;
  }
  arr[i] = item;
  ++n;
}

template <class Item, class Key>
Item SortedArraySt<Item, Key>::search (Key k) {
  for (int i = 0; i < size; ++i) {
    if (arr[i].key() >= k) break;
  }
  if (i < size && arr[i].key() == k) return arr[i];
  return null_item;
}

template <class Item, class Key>
void SortedArraySt<Item, Key>::remove (Item item) {
  int i;
  for (i = 0; i < n; ++i) {
    if (arr[i].key() >= item.key()) break;
  }

  if (i < n && arr[i].key() ==  item.key()){
    for (i = i+1; i < size; ++i) arr[i-1] = arr[i];
    arr[--n] = null_item;
  }
}

template <class Item, class Key>
Item SortedArraySt<Item, Key>::select (int k) {
  if (k>=n) return null_item;
  else return arr[k];
}

template <class Item, class Key>
void SortedArraySt<Item, Key>::visit (void) {
  for (int i = 0; i < n; ++i) {
    std::cout << arr[i];
  }
}

#endif
