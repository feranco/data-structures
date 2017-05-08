template <class Item, class Key>
class HashTable {
  struct Node {
    Item item;
    Node *next;
    Node (Item x): item(x), next(0){};
  };

  typedef Node* Link;
  Link* ht;
  int size;

 public:
  HashTable (int n);
  Item search(Key k);
  void insert(Item item);
};

template <class Item, Key>
HashTable<Item>::HashTable(int n) {
  size = n;
  ht = new Link[n];
  for (int i = 0; i < n; ++i) ht[i] = 0;
}

template <class Item, Key>
Item HashTable<Item, Key>::search(Key k) {
  int h = hash(k, size);
  Link t = ht[h];
  while (!t) {
    if (t->item.key() == k) return t->item;
    t = t->next;
  }
  return null_item;
}

template <class Item, Key>
void HashTable<Item, Key>::insert(Item item) {
  int h = hash(item.key(), size);
  Link t = new Node(item);
  t->next = ht[h];
  ht[h] = t;
}

