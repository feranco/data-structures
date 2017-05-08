#include "hash.h"
#include <iostream>
#include <string>

using std::string;

int main(int argc, char* argv[])
{
  /*char s1[] = "pippo";
  char s2[] = "fernando";
  char s3[] = "opppi";
  char s4[] = "opppo";
  */

  string s1 = "pippo";
  string s2 = "fernando";
  string s3 = "opppi";
  string s4 = "opppo";
  /*
  char s1[] = "p";
  char s2[] = "i";
  char s3[] = "r";
  char s4[] = "o";

  std::cout <<  hash(s1,200) +  hash(s2,200) +  hash(s3,200) +  hash(s4,200) << "\n";

  char s5[] = "o";
  char s6[] = "i";
  char s7[] = "p";
  char s8[] = "r";

  std::cout <<  hash(s5,200) +  hash(s6,200) +  hash(s7,200) +  hash(s8,200) << "\n";
  */
  std::cout << hash(s1,200) << "\n";
  std::cout << hash(s2,200) << "\n";
  std::cout << hash(s3,200) << "\n";
  std::cout << hash(s4,200) << "\n";
}


