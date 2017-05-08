//Open addressing with sequencial probing
template <class Item, class Key>
class HashTable {
  Item* ht;
  Item null_item;
  int max_sz;
  int sz;

 public:
  HashTable (int n);
  Item search(Key k);
  void insert(Item item);
  void delete(Key k);
};

template <class Item, Key>
HashTable<Item>::HashTable(int n) {
  ht = new Item[n];
  max_sz = n;
  sz = 0;
  for (int i = 0; i < n; ++i) ht[i] = null_item;
}

template <class Item, Key>
Item HashTable<Item, Key>::search(Key k) {
  int h = hash(k, max_sz);
  while (ht[h] != null_item) {
    if (ht[h].key() == k) return ht[h];
    h = ++h % max_sz;
  }
  return null_item;
}

template <class Item, Key>
void HashTable<Item, Key>::insert(Item item) {
  int h = hash(k, max_sz);
  while (ht[h] != null_item) h = ++h % max_sz;
  ht[h] = item;
  ++sz;
}

template <class Item, Key>
void HashTable<Item, Key>::delete(Key k) {
  int h = hash(k, max_sz);
  while (ht[h].key() != k) {
    if (ht[h] == null_item) return;
    h = ++h % max_sz;
  }
  ht[h++] = null_item;
  sz--;
  while (ht[h] != null_item) {
    //first set the old position to null and then
    //insert in the new position
    Item tmp = ht[h];
    ht[h] = null_item;
    sz--; //decrement the size because in insert in again increased
    insert(tmp);
  }
}
