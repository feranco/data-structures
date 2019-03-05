#include "circular_buffer.h"
#include <gtest/gtest.h>

TEST(RingBufferTest, testEmpty) {
  RingBuffer<int> rb (5);
  ASSERT_EQ(true, rb.empty());
}

TEST(RingBufferTest, testFull) {
  RingBuffer<int> rb (5);
  ASSERT_EQ(false, rb.full());
}

TEST(RingBufferTest, testPut) {
  RingBuffer<double> rb (5);
  ASSERT_EQ(true, rb.empty());
  rb.put(12);
  ASSERT_EQ(false, rb.empty());
}

TEST(RingBufferTest, testGet) {
  const int val = 12;
  RingBuffer<double> rb (5);
  ASSERT_EQ(true, rb.empty());
  rb.put(val);
  ASSERT_EQ(false, rb.empty());
  ASSERT_EQ(val, rb.get());
}

TEST(RingBufferTest, testPutAndGet) {
  const int val = 12;
  const size_t capacity = 5;
  RingBuffer<double> rb (capacity);
  ASSERT_EQ(true, rb.empty());
  for (size_t i = 0; i < capacity; ++i) {
      rb.put(val);
      ASSERT_EQ(false, rb.empty());
  }

    for (size_t i = 0; i < capacity; ++i) {
    //   ASSERT_EQ(rb.get(),val+i);
    std::cout << rb.get() << " ";
  }


  ASSERT_EQ(true, rb.full());
}
#if 0
TEST(RingBufferTest, testCopyConstructor) {
  const int val = 12;
  const size_t capacity = 5;
  RingBuffer<int> rb (capacity);

  for (size_t i = 0; i < capacity; ++i) {
    rb.put(val+i);
  }

  RingBuffer<int> rbCopy = rb;

  for (size_t i = 0; i < capacity; ++i) {
    //   ASSERT_EQ(rb.get(),val+i);
    std::cout << rbCopy.get() << " ";
  }

}
#endif



int main (int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}
