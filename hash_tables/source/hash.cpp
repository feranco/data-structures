#include "hash.h"


int hash (char* s, int n) {
  int h = 0;
  const int m = 127;
  for (; *s != 0; s++) {
    h = (h*m + *s) % n; 
  }
  return h;
}

int hash (string s, int n) {
  int h = 0;
  const int m = 127;
  for (char c : s) {
    h = (h*m + c) % n; 
  }
  return h;
}


