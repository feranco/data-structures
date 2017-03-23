#include <iostream>
#include <fstream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include "symbol_table_data.h"
#include "symbol_table_test.h"
#include "bst_st.h"

int main(int argc, char* argv[])
{

  BstSt<StData,Key> st;

  testST(st);
  //testStaticST();
  return 0;
}

 
