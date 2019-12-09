//
// Created by qnbhd on 02.12.2019.
//

#pragma once

#include <iostream>
#include <vector>

enum MatrixType
{
    ZEROS,
    ONES
};

template <typename T>
class Matrix {
private:

    T **   data_;

    size_t rows_;

    size_t columns_;

    T ** _create_array2d (size_t a , size_t b);

    void _free_array2d (T ** m , size_t a , size_t b );

    void _make_ones ();

    T* getRow (size_t index);

    T* getColumn (size_t index);

public:

    Matrix (std::size_t, std::size_t, int MatrixType = ZEROS);

    explicit Matrix (std::vector<std::vector<T>>);

    virtual ~Matrix();

    Matrix (const Matrix&);

    Matrix& operator=(const Matrix& right);

    T* operator [] (size_t index);

    T& at (size_t i, size_t j);

    [[nodiscard]] size_t rows () const;

    [[nodiscard]] size_t columns () const;

    void RowSum (size_t, size_t);

    void ColSum (size_t, size_t);

    template <class U>
    friend std::ostream& operator<<(std::ostream& out, Matrix<U> d1) ;


};

template<typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t columns, int MatrixType) : rows_(rows), columns_(columns)
{
    data_ = _create_array2d(rows, columns);

    for (size_t i = 1; i != rows ; ++i)
    {
        *data_[i] = 0.0;
    }

    if (rows == columns)
    {
        switch (MatrixType)
        {
            case ONES:
                _make_ones();
                break;

            case ZEROS:

            default:  ;
        }
    }


}

template<typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> source)
{
    //// ALL ROWS ARE IDENTICAL
    rows_ = source.size();
    columns_ = source.at(0).size();

    data_ = _create_array2d(rows_, columns_);

    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < columns_; ++j)
            data_[i][j] = source[i][j];

}

template<typename T>
Matrix<T>::~Matrix() {
    _free_array2d(data_, rows_, columns_);
}

template <typename T>
Matrix<T>::Matrix(const Matrix & mt) : rows_(mt.rows_), columns_(mt.columns_)
{
    data_ = _create_array2d(rows_, columns_);

    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < columns_; ++j)
            data_[i][j] = mt.data_[i][j];

}

template <typename T>
Matrix<T>&
Matrix<T>::operator=(const Matrix<T> &right)
{
    if (this == &right) {
        return *this;
    }

    rows_ = right.rows_;
    columns_ = right.columns_;

    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; i < columns_; ++j)
            data_[i][j] = right[i][j];


    return *this;
}

template <typename T>
std::ostream&
operator<<(std::ostream &out, Matrix<T> d1)
{
    for (size_t i = 0; i < d1.rows_ ; ++i)
    {
        for (size_t j = 0; j < d1.columns_ ; ++j)
        {
            out << d1.at(i, j) << " ";
        }

        out << std::endl;
    }

    return out;
}

template<typename T>
T**
Matrix<T>::_create_array2d(size_t a, size_t b)
{
    T ** m = new T *[a];
    m [0] = new T [a * b];
    for (size_t i = 1; i != a ; ++i)
        m[i] = m[i - 1] + b;
    return m;
}

template<typename T>
void
Matrix<T>::_free_array2d(T **m, size_t a, size_t b)
{
    delete [] m [0];
    delete [] m;
}

template<typename T>
void
Matrix<T>::_make_ones()
{
    if (columns_ != rows_)
        throw std::runtime_error("[ERROR] making zeros matrix, where cols <> rows");

    for (size_t i = 0; i < rows_; ++i)
        data_[i][i] = 1;
}

template<typename T>
T*
Matrix<T>::getRow(size_t index) {
    if (index >= 0 && index < rows_)
        return data_[index];
    return 0;
}

template<typename T>
T*
Matrix<T>::getColumn(size_t index) {
    if (index < 0 || index >= columns_)
        return 0;
    T * c = new T [rows_];
    for (int i = 0; i < rows_; ++ i)
        c[i] = data_[i][index];
    return c;
}

template<typename T>
T*
Matrix<T>::operator[](size_t index) {
    return getRow (index);
}

template<typename T>
size_t
Matrix<T>::rows() const {
    return rows_;
}

template<typename T>
size_t
Matrix<T>::columns() const {
    return columns_;
}

template<typename T>
T&
Matrix<T>::at(size_t i, size_t j) {
    if ((i < 0 || i >= rows_) || (j < 0 || j >= columns_))
        throw std::out_of_range("[ERROR] Matrix -> at() out of range");
    return data_[i][j];
}

template<typename T>
void
Matrix<T>::RowSum(size_t i, size_t j) {
    for (size_t z = 0; z < rows_; ++z)
        at(i, z) += at(j, z);
}

template<typename T>
void
Matrix<T>::ColSum(size_t i, size_t j) {
    for (size_t z = 0; z < rows_; ++z)
        at(z, i) += at(z, j);
}
