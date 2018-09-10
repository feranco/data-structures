#include "hash.h"

/*
unsigned int hash (char* s, unsigned int n) {
  int h = 0;
  const int m = 127;
  for (; *s != 0; s++) {
    h = (h*m + *s) % n; 
  }
  return h;
}
*/

unsigned int hash (string s, unsigned int n) {
  int h = 0;
  const int m = 127;
  for (char c : s) {
    h = (h*m + c) % n; 
  }
  return h;
}


