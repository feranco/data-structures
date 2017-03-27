#ifndef SYMBOL_TABLE_TEST
#define SYMBOL_TABLE_TEST


#include <iostream>
#include "symbol_table_data.h"
#include "symbol_table.h"

const int sz = 10;

//test insert, search and remove
template <class Item, class Key>
void testST (ST<Item,Key>& st) {
  StData item;
  for (int i = 0; i < sz; ++i) {
    item.rand();
    if (st.search(item.key()).null()) st.insert(item);   
  }
  st.visit();
  Item x = st.search(item.key());
  std::cout << "search hit: " << x;
  st.remove(x);
  x = st.search(x.key());
  std::cout << "search miss: " << x;
  st.visit();
}

#include "bst_st.h"
//test join
template <class Item, class Key>
  void testST2 (BstSt<Item,Key>& stA, BstSt<Item,Key>& stB) {
  StData item;
  for (int i = 0; i < sz; ++i) {
    item.rand();
    if (stA.search(item.key()).null()) stA.insert(item);   
  }
  stA.visit();
  std::cout << "--------" << std::endl;
  for (int i = 0; i < sz; ++i) {
    item.rand();
    if (stB.search(item.key()).null()) stB.insert(item);   
  }
  stB.visit();
  std::cout << "--------" << std::endl;
  stA.join(stB);
  stA.visit();
}

#include "static_st.h"

void testStaticST (void) {
  StData a[sz];
  for (int i = 0; i < sz; ++i) {
    a[i].rand();
  }
  StaticSt<StData,Key> st(a, sz);
  st.visit();
  StData x = st.search(a[8].key());
  std::cout << "search hit: " << x;
}

#endif
