#include <cstdio>
#include <memory>
#include <mutex>
#include <iostream>
template <class T>
class RingBuffer {
 public:
  RingBuffer(size_t size) :
      mCapacity(size),
      mData(std::unique_ptr<T[]>(static_cast<T*>(operator new (((size+1)*sizeof(T))))))
  {

  }

  RingBuffer(const RingBuffer& src) : mHead(src.mHead), mTail(src.mTail), mCapacity(src.mCapacity),
                                      mData(std::unique_ptr<T[]>(static_cast<T*>(operator new (((src.mCapacity)*sizeof(T))))))
  {
    std::cout << "CC called\n";
    //call move assignment operator try after it is defined
    //mData = std::make_unique<T[]>(static_cast<T*>(operator new (((mCapacity)*sizeof(T)))));
    for (std::size_t i = mHead; i != mTail; i = (i+1) % mCapacity)
    {
      new (mData.get()+i) T(src.mData[i]);
    }
  }

  bool empty() const
  {
    //if head and tail are equal the container is empty
    return (mHead == mTail);
  }

  bool full() const
  {
    //If tail is ahead the head by 1 the container is full
    return (mHead == ((mTail+1)%mCapacity));
  }

  void put(const T& item)
  {
    std::lock_guard<std::mutex> lock(mMutex);

    if (full()) {
      new(mData.get() + mHead) T(item);
      mTail = mHead;
      mHead = (mHead+1) % mCapacity;
    }
    else {
      new(mData.get() + mTail) T(item);
      mTail = (mTail+1) % mCapacity;
    }

  }

  T get()
  {
    std::lock_guard<std::mutex> lock(mMutex);

    if(empty())
    {
      return T();
    }

    //Read mData and advance the tail (we now have a free space)
    auto ret = mData[mHead];
    mData[mHead].~T();
    mHead = (mHead+1) % mCapacity;
    return ret;
  }
#if 0
  void reset()
  {
    std::lock_guard<std::mutex> lock(mMutex);
    mHead = mTail;
    mFull = false;
  }

  size_t capacity() const
  {
    return mCapacity;
  }

  size_t size() const
  {
    size_t size = mCapacity;

    if(!mFull)
    {
      if(mHead >= mTail)
      {
        size = mHead - mTail;
      }
      else
      {
        size = mCapacity + mHead - mTail;
      }
    }

    return size;
  }
#endif
 private:
  std::mutex mMutex;
  size_t mHead = 0;
  size_t mTail = 0;
  const size_t mCapacity;
  std::unique_ptr<T[]> mData;
};
