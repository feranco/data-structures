#include <algorithm>
#include <functional>
#include <list>
#include <utility>
#include <vector>
#include <iostream>
using std::find;
using std::list;
using std::pair;
using std::vector;

template <typename Key, typename T, typename Hash = std::hash<Key>>
class HashTable {
  //typedef pair<const Key, T> valueType;
  using valueType =  pair<const Key, T>;
  vector<list<valueType>> hashTable;
  size_t size = 0;
  Hash hashFunct;

 public:
  //typedef typename std::list<valueType> array_type;
  //typedef typename x std::list<valueType>::iterator iterator;
  //using hashFunction = std::function<unsigned int(Key, unsigned int)>;
  //hashFunction hash;
  using iterator =  typename std::list<valueType>::iterator;
  iterator begin() noexcept { return hashTable[0].begin(); }
  inline iterator end() noexcept { return hashTable[0].end(); }
  
  HashTable () {}
  //HashTable (hashFunction hf) : hash(hf){}
  
  HashTable (unsigned int n);
  iterator search(const Key& k) ;
  iterator insert(Key k, T value);
  //void delete (iterator it);

};

template <typename Key, typename T, typename Hash>
  HashTable<Key,T, Hash>::HashTable(unsigned int size) {
  hashTable.resize(size);
  this->size = size;
}


template <typename Key, typename T, typename Hash>
  typename HashTable<Key, T, Hash>::iterator  HashTable<Key,T, Hash>::search(const Key& k)  {
  auto h =  hashFunct(k);//Hash<T>(k);
  h = h%size;
  auto lambda = [&](valueType x){return x.first == k;}; 
  auto it =  find_if(hashTable[h].begin(), hashTable[h].end(),lambda);
  std::cout << "search: " << it->first << std::endl;
  return (hashTable[h].begin());
}

template <typename Key, typename T, typename Hash>
  typename HashTable<Key,T, Hash>::iterator HashTable<Key,T, Hash>::insert(Key k, T value) {
  auto h = hashFunct(k);
  h = h%size;
  std::cout << h << std::endl;
  hashTable[h].push_front(std::make_pair(k,value));
  //size++;
  return hashTable[h].begin();
}

