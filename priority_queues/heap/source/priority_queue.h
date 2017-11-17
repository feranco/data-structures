
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityQueue {
  vector<T> pq;

  size_t parent (size_t idx) {return idx >> 1;};
  size_t left (size_t idx) {return idx << 1;};
  size_t right (size_t idx) {return (idx << 1) + 1;};
  void heapifyDown (size_t idx);
  void heapifyUp (size_t idx);

public:
  PriorityQueue () {pq.emplace_back(T{});};
  ~PriorityQueue () {pq.clear();};
  void insert (const T& value);
  const T& peak ();
  void remove ();
  size_t size () {return pq.size()-1;};
  bool empty () {return pq.size() == 1;};
};

template <typename T>
void PriorityQueue<T>::heapifyUp (size_t idx) {
  while (idx > 1) {
    size_t p = parent(idx);
    if (pq[p] > pq[idx]) break;
    swap(pq[p], pq[idx]);
    idx = p;
  }
}

template <typename T>
void PriorityQueue<T>::heapifyDown (size_t idx) {

  while (idx < pq.size()) {
    size_t left_child = left(idx), right_child = right(idx), max = idx;
    if (left_child < pq.size() && pq[left_child] > pq[max]) max = left_child;
    if (right_child < pq.size() && pq[right_child] > pq[max]) max = right_child;
    if (max == idx) break;
    swap(pq[idx], pq[max]);
    idx = max;
  }
}

template <typename T>
const T& PriorityQueue<T>::peak () {
  if (pq.size <= 1) throw std::runtime_error("Priority queue underflow!");
  return pq[1];
}

template <typename T>
void PriorityQueue<T>::remove () {
  if (pq.size() <= 1) throw std::runtime_error("Priority queue underflow!");
  swap(pq[1], pq[pq.size()-1]);
  heapifyDown(1);
  pq.pop_back();
}

template <typename T>
void PriorityQueue<T>::insert (const T& value) {
  pq.emplace(value);
  heapifyUp(pq.size()-1);
}
