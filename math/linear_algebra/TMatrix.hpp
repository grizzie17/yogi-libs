//=====================================
//! @file: TMatrix.hpp
//!
//! define generalized matrix class
//=====================================
/*
	Definition

    00  01  02  03
    10  11  12  13
    20  21  22  23
    30  31  32  33

    XYZW

	x0  x1  x2  x3
	y0  y1  y2  y3
	z0  z1  z2  z3
	w0  w1  w2  w3

	Scale

	x0  0   0   0
	0   y1  0   0
	0   0   z2  0
	0   0   0   1

	Rotation

	r00 r01 r02 0
	r10 r11 r12 0
	r20 r21 r22 0
	0   0   0   1

	Translation

	1   0   0   tx
	0   1   0   ty
	0   0   1   tz
	0   0   0   1
*/

#ifndef HPP_TMATRIX_YOGI
#define HPP_TMATRIX_YOGI
#pragma once

// Headers ============================
#include <initializer_list>

#include "../trigonometry/calculations.hpp"
#include "TVector.hpp"

// namespaces =========================
namespace Yogi { namespace math {

// type definitions ===================


//=====================================
//! @class: TMatrix
template <typename T, size_t N>
class TMatrix
{
    // class lifecycle ----------------
public:
    TMatrix();
    TMatrix( const TMatrix<T, N>& r );
    TMatrix( const std::initializer_list<T> args );

public:
    // public types -------------------
    typedef TMatrix<T, N> TTMatrix;

    template <typename U>
    class Row
    {
    public:
        Row( TTMatrix& tm, size_t row );

        U&
        operator[]( size_t col );
        U
        operator[]( size_t col ) const;

    protected:
        TTMatrix& m_mat;
        size_t    m_row;
    };

    template <typename U>
    class ConstRow
    {
    public:
        ConstRow( const TTMatrix& tm, size_t row );

        U
        operator[]( size_t col ) const;

    protected:
        const TTMatrix& m_mat;
        size_t          m_row;
    };

    // public functions ---------------
    Row<T>
    operator[]( size_t row );
    ConstRow<T>
    operator[]( size_t row ) const;

    T
    getValue( size_t row, size_t col ) const;
    T&
    getRef( size_t row, size_t col );

    // equality
    bool
    equals( const TMatrix<T, N>& r ) const;
    bool
    operator==( const TMatrix<T, N>& r ) const;
    bool
    operator!=( const TMatrix<T, N>& r ) const;

    // set
    const TMatrix<T, N>&
    set( const TMatrix<T, N>& r );
    const TMatrix<T, N>&
    operator=( const TMatrix<T, N>& r );

    // add
    const TMatrix<T, N>&
    add( const TMatrix<T, N>& r );
    const TMatrix<T, N>&
    operator+=( const TMatrix<T, N>& r );

    // subtract
    const TMatrix<T, N>&
    subtract( const TMatrix<T, N>& r );
    const TMatrix<T, N>&
    operator-=( const TMatrix<T, N>& r );

    // transpose
    void
    transpose();

    void
    translate( const TVector<T, N>& v );

    // multiply
    const TMatrix<T, N>&
    multiply( const TMatrix<T, N>& r );
    const TMatrix<T, N>&
    operator*=( const TMatrix<T, N>& r );

    TVector<T, N>
    multiply( const TVector<T, N>& r );
    TVector<T, N>
    operator*( const TVector<T, N>& r );

    // public data --------------------
protected:
    // protected types ----------------
    // protected functions ------------
    // protected data -----------------
    T m_a[N][N];  // always square matrix
};


typedef TMatrix<float, 2> mat2f;
typedef TMatrix<float, 3> mat3f;
typedef TMatrix<float, 4> mat4f;

typedef TMatrix<double, 2> mat2d;
typedef TMatrix<double, 3> mat3d;
typedef TMatrix<double, 4> mat4d;


//=====================================
// class lifecycle
//=====================================

template <typename T, size_t N>
TMatrix<T, N>::TMatrix()
{
    // zero out the array
    for ( size_t i = 0; i < N; ++i )
    {
        for ( size_t j = 0; j < N; ++j )
            m_a[i][j] = static_cast<T>( 0 );
    }
    // load the identity diagonal
    for ( size_t i = 0; i < N; ++i )
        m_a[i][i] = static_cast<T>( 1 );
}


template <typename T, size_t N>
TMatrix<T, N>::TMatrix( const TMatrix<T, N>& r )
{
    set( r );
}

template <typename T, size_t N>
TMatrix<T, N>::TMatrix( const std::initializer_list<T> args )
{
    size_t nRows = 0;
    size_t nCols = 0;

    for ( auto& it : args )
    {
        m_a[nRows][nCols++] = it;
        if ( N <= nCols )
        {
            ++nRows;
            if ( N <= nRows )
                break;
            nCols = 0;
        }
    }
}


//=====================================
// array notation
//=====================================
// Row
template <typename T, size_t N>
template <typename U>
TMatrix<T, N>::Row<U>::Row( TMatrix<T, N>& tm, size_t row )
        : m_mat( tm )
        , m_row( row )
{}

template <typename T, size_t N>
template <typename U>
inline U&
TMatrix<T, N>::Row<U>::operator[]( size_t col )
{
    return m_mat.getRef( m_row, col );
}

template <typename T, size_t N>
template <typename U>
inline U
TMatrix<T, N>::Row<U>::operator[]( size_t col ) const
{
    return m_mat.getValue( m_row, col );
}

template <typename T, size_t N>
inline TMatrix<T, N>::Row<T>
TMatrix<T, N>::operator[]( size_t row )
{
    return Row<T>( *this, row );
}

// ConstRow
template <typename T, size_t N>
template <typename U>
TMatrix<T, N>::ConstRow<U>::ConstRow( const TMatrix<T, N>& tm, size_t row )
        : m_mat( tm )
        , m_row( row )
{}

template <typename T, size_t N>
template <typename U>
inline U
TMatrix<T, N>::ConstRow<U>::operator[]( size_t col ) const
{
    return m_mat.getValue( m_row, col );
}

template <typename T, size_t N>
inline TMatrix<T, N>::ConstRow<T>
TMatrix<T, N>::operator[]( size_t row ) const
{
    return ConstRow<T>( *this, row );
}


//=====================================
// public functions
//=====================================
template <typename T, size_t N>
inline T
TMatrix<T, N>::getValue( size_t row, size_t col ) const
{
    return m_a[row][col];
}

template <typename T, size_t N>
inline T&
TMatrix<T, N>::getRef( size_t row, size_t col )
{
    return m_a[row][col];
}


template <typename T, size_t N>
bool
TMatrix<T, N>::equals( const TMatrix<T, N>& r ) const
{
    for ( size_t row = 0; row < N; ++row )
    {
        for ( size_t col = 0; col < N; ++col )
        {
            if ( m_a[row][col] != r.m_a[row][col] )
                return false;
        }
    }

    return true;
}

template <typename T, size_t N>
inline bool
TMatrix<T, N>::operator==( const TMatrix<T, N>& r ) const
{
    return equals( r );
}


template <typename T, size_t N>
inline bool
TMatrix<T, N>::operator!=( const TMatrix<T, N>& r ) const
{
    return ! equals( r );
}


template <typename T, size_t N>
const TMatrix<T, N>&
TMatrix<T, N>::set( const TMatrix<T, N>& r )
{
    for ( size_t row = 0; row < N; ++row )
    {
        for ( size_t col = 0; col < N; ++col )
            m_a[row][col] = r.m_a[row][col];
    }
    return *this;
}


template <typename T, size_t N>
inline const TMatrix<T, N>&
TMatrix<T, N>::operator=( const TMatrix<T, N>& r )
{
    return set( r );
}


// add
template <typename T, size_t N>
const TMatrix<T, N>&
TMatrix<T, N>::add( const TMatrix<T, N>& r )
{
    for ( size_t row = 0; row < N; ++row )
    {
        for ( size_t col = 0; col < N; ++col )
            m_a[row][col] += r.m_a[row][col];
    }
    return *this;
}

template <typename T, size_t N>
inline const TMatrix<T, N>&
TMatrix<T, N>::operator+=( const TMatrix<T, N>& r )
{
    return add( r );
}


// subtract
template <typename T, size_t N>
const TMatrix<T, N>&
TMatrix<T, N>::subtract( const TMatrix<T, N>& r )
{
    for ( size_t row = 0; row < N; ++row )
    {
        for ( size_t col = 0; col < N; ++col )
            m_a[row][col] -= r.m_a[row][col];
    }
    return *this;
}

template <typename T, size_t N>
inline const TMatrix<T, N>&
TMatrix<T, N>::operator-=( const TMatrix<T, N>& r )
{
    return subtract( r );
}


template <typename T, size_t N>
void
TMatrix<T, N>::transpose()
{
    TMatrix<T, N> result;
    for ( size_t i = 0; i < N; ++i )
    {
        for ( size_t j = 0; j < N; ++j )
        {
            result.m_a[j][i] = this->m_a[i][j];
        }
    }
    *this = result;
}


template <typename T, size_t N>
void
TMatrix<T, N>::translate( const TVector<T, N>& v )
{
    size_t n = N - 1;
    for ( size_t i = 0; i < N; ++i )
    {
        this->m_a[i][n] = v[i];
    }
}


// multiply
template <typename T, size_t N>
const TMatrix<T, N>&
TMatrix<T, N>::multiply( const TMatrix<T, N>& rhs )
{
    TMatrix<T, N> result( *this );
    for ( size_t row = 0; row < N; ++row )
    {
        for ( size_t col = 0; col < N; ++col )
        {
            T value = {};
            for ( size_t j = 0; j < N; ++j )
            {
                value += m_a[row][j] * rhs[j][col];
            }
            result[row][col] = value;
        }
    }
    *this = result;
    return *this;
}


template <typename T, size_t N>
TVector<T, N>
TMatrix<T, N>::multiply( const TVector<T, N>& v )
{
    TVector<T, N> result;

    for ( size_t row = 0; row < N; ++row )
    {
        T value = {};
        for ( size_t j = 0; j < N; ++j )
            value += m_a[row][j] * v[j];
        result[row] = value;
    }
    return result;
}

template <typename T, size_t N>
inline TVector<T, N>
TMatrix<T, N>::operator*( const TVector<T, N>& r )
{
    return multiply( r );
}


//=====================================
//=====================================


//=====================================
// protected functions
//=====================================


//=====================================
// Operations
//=====================================

// addition
template <typename T, size_t N>
TMatrix<T, N>
operator+( const TMatrix<T, N>& lhs, const TMatrix<T, N>& rhs )
{
    TMatrix<T, N> result( lhs );
    result.add( rhs );
    return result;
}

// subtraction
template <typename T, size_t N>
TMatrix<T, N>
operator-( const TMatrix<T, N>& lhs, const TMatrix<T, N>& rhs )
{
    TMatrix<T, N> result( lhs );
    result.subtract( rhs );
    return result;
}

// multiplication
template <typename T, size_t N>
TMatrix<T, N>
operator*( const TMatrix<T, N>& lhs, const TMatrix<T, N>& rhs )
{
    TMatrix<T, N> result( lhs );
    result.multiply( rhs );
    return result;
}

}}  // namespace Yogi::math


#endif  // HPP_TMATRIX_YOGI
