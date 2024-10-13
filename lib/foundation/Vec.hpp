#ifndef _H_VEC
#define _H_VEC
#include <Option.hpp>
namespace foundation {
template<typename T>
class Vec {
public:
  Vec(int initCap);
  ~Vec();

  T& operator[](int index);
  const T& operator[](int index) const;

  Option<T> pop();
  int push(const T value);
  int length() const;
  int capacity() const;
  
private:
  T* elems;
  int cap;
  int len;

  void grow(int n);
};

template<typename T>
Vec<T>::Vec(int initCap) : cap(initCap > 0 ? initCap : 1), len(0) {
  elems = new T[initCap];
}

template<typename T>
Vec<T>::~Vec() {
  delete[] elems;
}

template<typename T>
int Vec<T>::length() const {
  return len;
}

template<typename T>
int Vec<T>::capacity() const {
  return cap;
}

template<typename T>
Option<T> Vec<T>::pop() {
  if (len == 0) {
    return Option<T>::none();
  }

  Option<T> result = Option<T>::some(elems[len - 1]);
  len--;
  return result;
}

template<typename T>
void Vec<T>::grow(int n) {
  int newCap = cap + n;
  T* newElems = new T[newCap];

  for (int i = 0; i < cap; i++) {
    newElems[i] = elems[i];
  }

  delete[] elems;
  elems = newElems;
  cap = newCap;
}

template<typename T>
int Vec<T>::push(const T value) {
  if (len == cap) {
    // cap = len + 2
    grow(2);
  }

  int i = len;
  elems[i] = value;
  len++;
  return i;
}

template<typename T>
T& Vec<T>::operator[](int index) {
  return elems[index];
}

template<typename T>
const T& Vec<T>::operator[](int index) const {
  return elems[index];
}


};
#endif
