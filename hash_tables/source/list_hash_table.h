#include <list>
#include <vector>

using std::list;
using std::vector;

template <typename Key, typename T>
class HashTable {
  typedef pair<const Key, T> valueType;
  vector<list<valueType>> hashTable;
  size_t size = 0;
/*
  struct Node {
    Item item;
    Node *next;
    Node (Item x): item(x), next(0){};
  };

  typedef Node* Link;
  Link* ht;
  int size;
*/
 public:
  typedef HashTable::iterator iterator;
  iterator begin() noexcept { return hashTable.begin(); }
  inline iterator end() noexcept { return hashTable.end(); }
  
  HashTable () {}
  HashTable (size_t n);
  Item search(Key k);
  iterator insert(k, T value);
  //void insert(Key k, T value);
};

template <typename Item, typename Key>
HashTable<T,Key>::HashTable(unsigned int size) {
  hashTable.resize(size);
/*
  size = n;
  ht = new Link[n];
  for (int i = 0; i < n; ++i) ht[i] = 0;
  */
}

template <typename T, typename Key>
T HashTable<Item, Key>::search(Key k) {
  int h = hash(k, size);
  Link t = ht[h];
  while (!t) {
    if (t->item.key() == k) return t->item;
    t = t->next;
  }
  return null_item;
}

template <typename T, typename Key>
iterator HashTable<T, Key>::insert(T value) {
  int h = hash(item.key(), size);
  hashTable[h].push_front(value);
  return hashTable[h].begin();
  /*
  Link t = new Node(item);
  t->next = ht[h];
  ht[h] = t;
  */
}

template <class Item, Key>
void HashTable<Item, Key>::insert(Item item) {
  int h = hash(item.key(), size);
  Link t = new Node(item);
  t->next = ht[h];
  ht[h] = t;
}

