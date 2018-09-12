#include "list_hash_table.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>

using std::string;

std::vector<unsigned int> integerKeys()
{
    std::mt19937_64 rd(0);

    std::vector<unsigned int > numbers;
    for (size_t i = 0; i < 50; ++i) {
      numbers.push_back(rd());
    }

    return numbers;
}

std::vector<std::string> generateKeys(
    const std::string& prefix, const std::vector<unsigned int>& integer_keys, const std::string& suffix)
{
	std::vector<std::string> results;
	results.reserve(integer_keys.size());
	for (const auto& int_key : integer_keys) {
		results.emplace_back(prefix + std::to_string(int_key) + suffix);
		// results.emplace_back(prefix + std::string((const char*)&int_key, sizeof(int_key)) + suffix);
	}
	return results;
}


int main(int argc, char* argv[])
{
  const auto integer_keys  = integerKeys();
  const auto string_keys    = generateKeys("", integer_keys, "");
  HashTable<string,int> ht(100);
  for (int i = 0; i < integer_keys.size(); ++i) {
    auto it = ht.insert(string_keys[i], integer_keys[i]);
    std::cout << it->first << std::endl;
  }

 ht.search(string_keys[5]);
  // std::cout << it->first << std::endl;
}


