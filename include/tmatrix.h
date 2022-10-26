// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    else if (sz > MAX_VECTOR_SIZE)
        throw std::exception("It's very big size for vector");
    else if (sz < 0)
        throw std::exception("Can't be vector with negative size");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s){
      if (sz == 0)
          throw out_of_range("Vector size should be greater than zero");
      else if (sz > MAX_VECTOR_SIZE)
          throw std::exception("It's very big size for vector");
      else if (sz < 0)
          throw std::exception("Can't be vector with negative size");
      assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
      pMem = new T[sz];
      std::copy(arr, arr + sz, pMem);
      
  }
  TDynamicVector(const TDynamicVector& v){
      sz = v.sz;
      T* pMemcopy = new T[sz];
      for (int i = 0; i < sz; i++) {
          pMemcopy[i] = v.pMem[i];
      }
      pMem = pMemcopy;
  }
  TDynamicVector(TDynamicVector&& v) noexcept{
      sz = v.sz;
      T* pMemcopy = new T[sz];
      for (int i = 0; i < sz; i++) {
          pMemcopy[i] = v.pMem[i];
      }
      pMem = pMemcopy;
      v.sz = 0;
      v.pMem = nullptr;
  }
  ~TDynamicVector(){
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v){
      if (this == &v)
          return *this;
      sz = v.sz;
      delete[] pMem;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept{
      if (this == &v)
          return *this;
      sz = v.sz;
      delete[] pMem;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
      v.sz = 0;
      v.pMem = nullptr;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind){
      return pMem[ind];
  }
  const T& operator[](size_t ind) const{
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind){
      if (ind < 0)
          throw std::exception("Can't be negative index");
      else if (ind > sz)
          throw std::exception("Very big index");
      return pMem[ind];
  }
  const T& at(size_t ind) const{
      if (ind < 0)
          throw std::exception("Can't be negative index");
      else if (ind > sz)
          throw std::exception("Very big index");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept{
      if (sz != v.sz) {
          return false;
      }
      else {
          for (int i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) {
                  return false;
              }
          }
          return true;
      }
  }
  bool operator!=(const TDynamicVector& v) const noexcept{
      return !(*this == v)
  }

  // скалярные операции
  TDynamicVector operator+(T val){
      TDynamicVector copy(sz);
      for (int i = 0; i < sz; i++) {
          copy.pMem[i] = pMem[i] + val;
      }
      return copy;

  }
  TDynamicVector operator-(T val){
      TDynamicVector copy(sz);
      for (int i = 0; i < sz; i++) {
          copy.pMem[i] = pMem[i] - val;
      }
      return copy;

  }
  TDynamicVector operator*(T val){
      TDynamicVector copy(sz);
      for (int i = 0; i < sz; i++) {
          copy.pMem[i] = pMem[i] * val;
      }
      return copy;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v){
      if (sz != v.sz)
          throw std::exception("Can't sum vectors with different size");
      else {
          TDynamicVector copy(sz);
          for (int i = 0; i < sz; i++) {
              copy.pMem[i] = pMem[i] + v.pMem[i];
          }
          return copy;
      }

  }
  TDynamicVector operator-(const TDynamicVector& v){
      if (sz != v.sz)
          throw std::exception("Can't substract vectors with different size");
      else {
          TDynamicVector copy(sz);
          for (int i = 0; i < sz; i++) {
              copy.pMem[i] = pMem[i] - v.pMem[i];
          }
          return copy;
      }
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T())){
      if (sz != v.sz)
          throw std::exception("Can't multiply vectors with different size");
      else {
          T res = 0;
          for (int i = 0; i < sz; i++) {
              res += pMem[i] * v.pMem[i];
          }
          return res;
      }
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s){
      if (s > MAX_MATRIX_SIZE)
          throw std::exception("Very big size of matrix");
      for (size_t i = 0; i < sz; i++)
          pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
  }
};

#endif
