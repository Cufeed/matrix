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
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size too large");
    pMem = new T[sz]{};// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept : pMem(v.pMem), sz(v.sz)
  {
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) { 
          delete[] pMem; 

          sz = v.sz; 
          pMem = new T[sz]; 

          for (int i = 0; i < sz; i++) { 
              pMem[i] = v.pMem[i];
          }
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          pMem = v.pMem;
          v.sz = 0;
          v.pMem = nullptr;
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind >= sz) throw out_of_range("wrong index");
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind >= sz) throw out_of_range("wrong index");
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz) throw out_of_range("wrong index");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz) throw out_of_range("wrong index");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (size_t i = 0; i < sz; i++) 
          if (pMem[i] != v[i]) 
              return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(*this);
      for (size_t i = 0; i < sz; i++) 
          tmp.pMem[i] += val;
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector tmp(*this);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] -= val;
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector tmp(*this);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] *= val;
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) 
          throw out_of_range("wrong index's");
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) 
          tmp[i] = pMem[i] + v.pMem[i];
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw out_of_range("wrong index's");
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp[i] = pMem[i] - v.pMem[i];
      return tmp;
  }
  //T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  TDynamicVector operator*(const TDynamicVector& v)
  {
      TDynamicVector tmp(sz);
      if (sz != v.sz)
          throw out_of_range("wrong index's");
      //T tmp{};
      for (size_t i = 0; i < sz; i++)
          tmp[i] = pMem[i] * v.pMem[i];
      return tmp;
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
  //friend istream& operator>>(istream& istr, TDynamicVector<T>& v)
  //{
  //    for (size_t i = 0; i < v.sz; i++)
  //        istr >> v.pMem[i]; 
  //    return istr;
  //}
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
  //friend ostream& operator<<(ostream& ostr, const TDynamicVector<T>& v)
  //{
  //    for (size_t i = 0; i < v.sz; i++)
  //        ostr << v.pMem[i] << ' '; 
  //    return ostr;
  //}
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s > MAX_MATRIX_SIZE)
          throw out_of_range("Too large matrix");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }
  TDynamicMatrix(const TDynamicMatrix& other)
      : TDynamicVector<TDynamicVector<T>>(other.sz)
  {
      if (other.sz > MAX_MATRIX_SIZE)
          throw std::out_of_range("Too large matrix");

      // Deep copy each element
      for (size_t i = 0; i < sz; i++)
          pMem[i] = TDynamicVector<T>(other.pMem[i]);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz)
          return false;
      for (size_t i = 0; i < sz; i++)
          if (pMem[i] != m.pMem[i])
              return false;
      return true;
  }
  int GetSize() {
      return sz;
  }
  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              tmp[i][j] = pMem[i][j] * val;
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicVector<T> tmp(sz);
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              tmp[i] += pMem[i][j] * v[j];
      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw out_of_range("Different size's");
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              tmp[i][j] = pMem[i][j] + m.pMem[i][j];
      return tmp;

  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw out_of_range("Different size's");
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              tmp[i][j] = pMem[i][j] - m.pMem[i][j];
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              for (size_t k = 0; k < sz; k++)
                  tmp[i][j] += pMem[i][k] * m.pMem[k][j];
      return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          for (size_t j = 0; j < v.sz; j++)
              istr >> v[i][j];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
      {
          for (size_t j = 0; j < v.sz; j++)
              ostr << v[i][j] << ' ';
          ostr << '\n';
      }
      return ostr;
  }
};

#endif
