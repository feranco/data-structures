#ifndef SYMBOL_TABLE_TEST
#define SYMBOL_TABLE_TEST


#include <iostream>
#include "symbol_table_data.h"
#include "symbol_table.h"

const int sz = 11;

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

//test insert, search and remove
template <class Item, class Key>
void testSTA (BstSt<Item,Key>& st) {
  StData item, a, b;
  for (int i = 0; i <= sz; ++i) {
    item.rand();
    if (st.search(item.key()).null()) st.insert(item);   
    if (i == 2) a = item;
    //if (i == 7) b = item;
  }
  st.visit();
  
  std::cout << "Test selection: " << "\n";
  for (int i = 1; i <= 10; ++i) {
    b = st.select(i);
    std::cout << b;
  }
  
  std::cout << "Test partition: " << "\n";
  for (int i = 1; i <= sz; ++i) {
    st.partition(i);
  }
  st.visit();

  std::cout << "Test balance: " << "\n";
  st.balance();
  std::cout << "--------" << std::endl;
  st.visit();
  
  
  st.remove(a);
  std::cout << "--------" << std::endl;
  //st.visit();
  //Item anc =  st.lowestAncestor(a.key(),b.key());
  //std::cout << "low anc: "<< a << " " << b << " " << anc;
}

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
