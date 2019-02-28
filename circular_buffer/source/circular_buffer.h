#include <cstdio>
#include <memory>
#include <mutex>

template <class T>
class ringBuffer {
public:
  ringBuffer(size_t size) :
      mData(std::unique_ptr<T>(static_cast<T*>(new (size*sizeof(T))))),
      mSize(size)
  {

  }
#if 0
  void put(T item)
  {
    std::lock_guard<std::mutex> lock(mMutex);

    mData[mHead] = item;

    new(_data + _size) T(t);
++size;

    if(mFull)
    {
      mTail = (mTail + 1) % mSize;
    }

    mHead = (mHead + 1) % mSize;

    mFull = mHead == mTail;
  }

  T get()
  {
    std::lock_guard<std::mutex> lock(mMutex);

    if(empty())
    {
      return T();
    }

    //Read mData and advance the tail (we now have a free space)
    auto val = mData[mTail];
    mFull = false;
    mTail = (mTail + 1) % mSize;

    return val;
  }

  void reset()
  {
    std::lock_guard<std::mutex> lock(mMutex);
    mHead = mTail;
    mFull = false;
  }

  bool empty() const
  {
    //if head and tail are equal, we are empty
    return (!mFull && (mHead == mTail));
  }

  bool full() const
  {
    //If tail is ahead the head by 1, we are full
    return mFull;
  }

  size_t capacity() const
  {
    return mSize;
  }

  size_t size() const
  {
    size_t size = mSize;

    if(!mFull)
    {
      if(mHead >= mTail)
      {
        size = mHead - mTail;
      }
      else
      {
        size = mSize + mHead - mTail;
      }
    }

    return size;
  }
#endif
private:
  std::mutex mMutex;
  //std::unique_ptr<T> mData;
  T* mData;
  size_t mHead = 0;
  size_t mTail = 0;
  const size_t mSize;
  bool mFull = 0;
};
