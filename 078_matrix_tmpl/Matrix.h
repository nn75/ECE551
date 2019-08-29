#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(0){};
  Matrix(int r, int c);
  Matrix(const Matrix<T> & rhs);
  //~IntMatrix();
  Matrix & operator=(const Matrix<T> & rhs);
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix<T> & rhs) const;
  Matrix<T> operator+(const Matrix<T> & rhs) const;
  template<typename X>
  friend std::ostream & operator<<(std::ostream& s, const Matrix<X> & rhs);
};

template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c) {
  rows = std::vector<std::vector<T> >(r);
  for (typename std::vector<std::vector<T> >::iterator it = rows.begin(); it != rows.end(); ++it) {
    *it = std::vector<T>(numColumns);
  }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  //rows = rhs.rows;
  rows = std::vector<std::vector<T> >(numRows);
  typename std::vector<std::vector<T> >::const_iterator it = rhs.rows.begin();
  for (typename std::vector<std::vector<T> >::iterator it1 = rows.begin(); it1 != rows.end(); ++it1) {
    *it1 = std::vector<T>(numColumns);
    typename std::vector<T>::const_iterator itt = it->begin();//itt = *it.begin()
    for (typename std::vector<T>::iterator itt1 = it1->begin(); itt1 != it1->end(); ++itt1){
      *itt1 = *itt;
      ++itt;
    }
    ++it;
  }
}

/*
template<typename T>
Matrix<T>::~IntMatrix() {
for (typename std::vector<T>::iterator it = rhs.numRows.begin(); it != rhs.numRows.end(); ++it) {
  delete *it;
}
delete[] rows;
}
*/


template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  if (this != &rhs) {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = std::vector<std::vector<T> >(numRows);
    typename std::vector<std::vector<T> >::const_iterator it = rhs.rows.begin();
    for (typename std::vector<std::vector<T> >::iterator it1 = rows.begin(); it1 != rows.end(); ++it1) {
      *it1 = std::vector<T>(rhs.numColumns);
      typename std::vector<T>::const_iterator itt = it->begin();
      for (typename std::vector<T>::iterator itt1 = it1->begin(); itt1 != it1->end(); ++itt1) {
        *itt1 = *itt;
        ++itt;
      }
      ++it;
    }
  }
  return *this;
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert(index >= 0 && (size_t)index < rows.size());
  return rows[index];
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert(index >= 0 && (size_t)index < rows.size());
  return rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if (numRows != rhs.numRows) {
    return false;
  }
  if (numColumns != rhs.numColumns) {
    return false;
  }
  typename std::vector<std::vector<T> >::const_iterator it1 = rows.begin();
  for (typename std::vector<std::vector<T> >::const_iterator it = rhs.rows.begin(); it != rhs.rows.end(); ++it) {
    if (*it!= *it1) {
      return false;
    }
    ++it1;
  }
  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  Matrix<T> sum(numRows,numColumns);
  typename std::vector<std::vector<T> >::const_iterator it = rhs.rows.begin();
  typename std::vector<std::vector<T> >::const_iterator it1 = rows.begin();
  typename std::vector<std::vector<T> >::iterator it0;
  for ( it0 = sum.rows.begin(); it0 != sum.rows.end(); ++it0,++it1,++it) {
    typename std::vector<T>::const_iterator itt = it->begin();
    typename std::vector<T>::const_iterator itt1 = it1->begin();
    typename std::vector<T>::iterator itt0;
    for (itt0 = it0->begin(); itt0 != it0->end(); ++itt0) {
        *itt0= *itt1 + *itt;
        ++itt1;
        ++itt;
    }
    
    //while(itt0 != it0->end()){
    //  *itt0++=*itt1++ + *itt++ ;
    //}
    
  }

  return sum;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[";
  for (typename std::vector<std::vector<T> >::const_iterator it = rhs.rows.begin();
       it != rhs.rows.end();
       ++it) {
    if (it != rhs.rows.begin()) {
      s << ",\n{";
    }
    else {
      s << "{";
    }
    for (typename std::vector<T>::const_iterator itt = it->begin(); itt != it->end(); ++itt) {
      if (itt != it->begin()) {
        s << ",";
      }
      s << *itt;
    }
    s << "}";
  }
  s << "]";
  return s;
}

#endif
