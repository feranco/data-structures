#include <algorithm>
#include <functional>
#include <list>
#include <utility>
#include <vector>

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
  iterator search(const Key& k) const;
  iterator insert(Key k, T value);
  //void delete (iterator it);

};

template <typename Key, typename T, typename Hash>
  HashTable<Key,T, Hash>::HashTable(unsigned int size) {
  hashTable.resize(size);
  this->size = size;
}


template <typename Key, typename T, typename Hash>
  typename HashTable<Key, T, Hash>::iterator  HashTable<Key,T, Hash>::search(const Key& k) const {
  int h = hash(k);
  return find(hashTable[h].begin(), hashTable[h].end());
}

template <typename Key, typename T, typename Hash>
  typename HashTable<Key,T, Hash>::iterator HashTable<Key,T, Hash>::insert(Key k, T value) {
  int h = hash(k);
  hashTable[h].push_front(value);
  size++;
  return hashTable[h].begin();
}

