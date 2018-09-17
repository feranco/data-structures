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

template <typename Key, typename T, typename Hash = std::hash<Key>, typename EqualTo = std::equal_to<Key>>
class HashTable {
 
  using valueType =  pair<const Key, T>;
  using HashTableType = HashTable<Key, T, Hash>;
  
  vector<list<valueType>> hashTable;
  
  size_t bucketSize = 0;
  size_t size = 0;
  
  Hash hashFunct;
  EqualTo equalToFunction;

 public:

  //Custom iterator for the HashTable
  class iterator {
  public:
    //Define iterator traits
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = size_t;
    using value_type        = valueType;
    using pointer           = value_type*;
    using reference         = value_type&;

    template <typename TT>
    using listIterator =  typename std::list<TT>::iterator;

    
    //Constructor
    iterator() { };
    iterator (HashTableType* ht, listIterator<valueType> it) : hashTableIt(ht), lIt(it) {};
    
    iterator& operator++()
    {
      this->goToNextElement();
      return *this;
    }
    
    iterator operator++(int)
    {
      this->goto_next_element();
      return iterator(hashTableIt, lIt);
    }
   
    reference operator*()
    {
      return *lIt;
    }
     
    pointer operator->()
    {
      return &(*lIt);
    }
    
    bool operator==(const iterator& rhs) const
    {
      return lIt == rhs.lIt;
    }

    bool operator!=(const iterator& rhs) const
    {
      return lIt != rhs.lIt;
    }
    
  private:
    void goToNextElement()
    {
      Key k = lIt->first;
      size_t h = this->hashFunct(k);
      h = h % this->bucketSize();
      lIt++;
      if (lIt != this->hashTable[h].end()) {
	return lIt;
      }

      for (size_t i = h; i < this->bucketSize(); ++i) {
	auto it = this->hashTable[h].begin();
	if (it != this->hashTable[h].end()) {
	  return it;
	}	  
      }
      return iterator(hashTableIt, hashTableIt->hashTable[hashTableIt->bucketSize-1].end());
    }
    
  public:
    HashTableType* hashTableIt;
    listIterator<valueType> lIt;
    
  };

  iterator begin()
  {
    for (auto bucket : hashTable) {
      auto it = bucket.begin();
      if (it != bucket.end()) {
	return it;
      }
    }
    return iterator(this, hashTable[bucketSize-1].end());
  }

  iterator end()
  {
    return iterator(this, hashTable[bucketSize-1].end());
  }

  //constructors
  HashTable () {}
  HashTable (unsigned int n);
  HashTable(const HashTable& other) = default;
  HashTable(HashTable&& other) = default;

  iterator search (const Key& k);
  iterator insert (Key k, T value);
  T& operator[] (const Key& key);
  void remove (iterator it);
  bool remove(const Key& key);
};

template <typename Key, typename T, typename Hash, typename EqualTo>
  HashTable<Key,T, Hash, EqualTo>::HashTable(unsigned int size) {
  hashTable.resize(size);
  bucketSize = size;
}


template <typename Key, typename T, typename Hash, typename EqualTo>
  typename HashTable<Key,T, Hash, EqualTo>::iterator  HashTable<Key,T, Hash, EqualTo>::search(const Key& k)  {
  auto h =  hashFunct(k);//Hash<T>(k);
  h = h%bucketSize;
  auto lambda = [&](valueType x){return equalToFunction(x.first,k);}; 
  auto it =  find_if(hashTable[h].begin(), hashTable[h].end(),lambda);
  std::cout << "search: " << it->first << std::endl;
  return iterator(this, hashTable[h].begin());
}

template <typename Key, typename T, typename Hash, typename EqualTo>
  typename HashTable<Key,T, Hash, EqualTo>::iterator HashTable<Key,T, Hash, EqualTo>::insert(Key k, T value) {
  auto h = hashFunct(k);
  h = h%bucketSize;
  std::cout << h << std::endl;
  hashTable[h].push_front(std::make_pair(k,value));
  size++;
  return iterator(this, hashTable[h].begin());
}

/// Remove an element using an iterator.
/// return false if element was not found.
/// O(1) operation
template <typename Key, typename T, typename Hash, typename EqualTo>
  void HashTable<Key,T, Hash, EqualTo>::remove (typename HashTable<Key,T, Hash, EqualTo>::iterator it) {
   auto h = hashFunct(it->first);
   h = h%bucketSize;
   hashTable[h].erase(it);
   size--;
}

/// Remove an element from the hash table.
/// return false if element was not found
template <typename Key, typename T, typename Hash, typename EqualTo>
bool HashTable<Key,T, Hash, EqualTo>::remove(const Key& k)
{
  auto it = search(k);
  if (it == this->end()) return false;
  remove(it);
  return true;
}

/// Like std::unordered_map operator[].
template <typename Key, typename T, typename Hash, typename EqualTo>
T& HashTable<Key,T, Hash, EqualTo>::operator[] (const Key& key)
{
  auto it = search(key);

  if (it != this->end()) return it->second;

  it = insert(key, T());

  return it->second;
}

