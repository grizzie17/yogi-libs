//! @file: TVector.hpp
//!
//!
#ifndef HPP_TVECTOR_MATH
#define HPP_TVECTOR_MATH
#pragma once


#include <array>
#include <initializer_list>

#include "math.hpp"


namespace Yogi { namespace math {

//=====================================
// Vector[fields]
//=====================================
template <typename T, size_t N>
struct TVectorFields
{
    T m_data[N];

    TVectorFields()
            : m_data {}
    {}

    // ~TVectorFields()
    // {}
};

//=====================================
template <typename T>
struct TVectorFields<T, 2>
{
    static constexpr size_t N = 2;
    union
    {
        T m_data[N];
        // Coordinates
        struct
        {
            T x;
            T y;
        };
    };

    TVectorFields()
            : m_data {}
    {}

    // TVectorFields( T x, T y )
    // {
    //     this->m_data = { x, y };
    // }

    T
    length()
    {
        return sqrt<T>( this->x * this->x + this->y * this->y );
    }
};


//=====================================

template <typename T>
struct TVectorFields<T, 3>
{
    static constexpr size_t N = 3;
    union
    {
        T m_data[N];
        // Coordinates
        struct
        {
            T x;
            T y;
            T z;
        };
    };

    TVectorFields()
            : m_data {}
    {}

    // TVectorFields( T x, T y, T z )
    // {
    //     this->m_data = { x, y, z };
    // }

    T
    length()
    {
        return sqrt<T>(
                this->x * this->x + this->y * this->y + this->z * this->z );
    }
};

// template <typename T>
// TVectorFields<T, 3>::TVectorFields( T x, T y, T z )
// {
//     this->m_data = { x, y, z };
// }

//=====================================
template <typename T>
struct TVectorFields<T, 4>
{
    static constexpr size_t N = 4;
    union
    {
        T m_data[N];
        // Coordinates
        struct
        {
            T x;
            T y;
            T z;
            T w;
        };
    };

    TVectorFields()
            : m_data {}
    {}

    // TVectorFields( T x, T y, T z, T w )
    // {
    //     this->m_data = { x, y, z, w };
    // }
};

//=====================================
// Vector[*]
//=====================================
// typename D = data fields
// typename T = field types
// typename N = number of indices
template <typename T, size_t N>
struct TVector : public TVectorFields<T, N>
{
    TVector();
    TVector( const TVector<T, N>& r );
    const TVector<T, N>&
    operator=( const TVector<T, N>& r );

    TVector( T v );
    TVector( const std::initializer_list<T> args );

    T
    operator[]( size_t index ) const noexcept;
    T&
    operator[]( size_t index ) noexcept;

    TVector<T, N>
    operator-();

    bool
    equals( const TVector<T, N>& r ) const;
    bool
    operator==( const TVector<T, N>& r ) const;
    bool
    operator!=( const TVector<T, N>& r ) const;
};


template <typename T, size_t N>
TVector<T, N>::TVector()
        : TVectorFields<T, N>()
{
    // for ( size_t j = 0; j < N; ++j )
    //     this->m_data[j] = {};
}

template <typename T, size_t N>
TVector<T, N>::TVector( T v )
{
    for ( size_t j = 0; j < N; ++j )
        this->m_data[j] = v;
}

template <typename T, size_t N>
TVector<T, N>::TVector( const TVector<T, N>& r )
{
    for ( size_t j = 0; j < N; ++j )
        this->m_data[j] = r.m_data[j];
}

template <typename T, size_t N>
const TVector<T, N>&
TVector<T, N>::operator=( const TVector<T, N>& r )
{
    for ( size_t j = 0; j < N; ++j )
        this->m_data[j] = r.m_data[j];
}

template <typename T, size_t N>
TVector<T, N>::TVector( const std::initializer_list<T> args )
{
    size_t j = 0;
    for ( auto& it : args )
    {
        if ( j < N )
            this->m_data[j++] = it;
        else
            break;
    }
    // fill remaining space with null
    while ( j < N )
    {
        this->m_data[j++] = {};
    }
}

template <typename T, size_t N>
T
TVector<T, N>::operator[]( size_t index ) const noexcept
{
    assert( 0 <= index && index < N );
    return this->m_data[index];
}

template <typename T, size_t N>
T&
TVector<T, N>::operator[]( size_t index ) noexcept
{
    assert( 0 <= index && index < N );
    return this->m_data[index];
}


// unary negate
template <typename T, size_t N>
TVector<T, N>
TVector<T, N>::operator-()
{
    TVector<T, N> result;
    for ( size_t i = 0; i < N; ++i )
        result[i] = -this->m_data[i];
    return result;
}


// equals
template <typename T, size_t N>
bool
TVector<T, N>::equals( const TVector<T, N>& r ) const
{
    for ( size_t j = 0; j < N; ++j )
    {
        if ( this->m_data[j] != r.m_data[j] )
            return false;
    }
    return true;
}
template <typename T, size_t N>
inline bool
TVector<T, N>::operator==( const TVector<T, N>& r ) const
{
    return equals( r );
}
template <typename T, size_t N>
inline bool
TVector<T, N>::operator!=( const TVector<T, N>& r ) const
{
    return ! equals( r );
}


//=====================================
// Vector[0]
//=====================================


//=====================================
// Vector[2]
//=====================================
typedef TVector<int, 2>    vec2i;
typedef TVector<float, 2>  vec2f;
typedef TVector<double, 2> vec2d;


//=====================================
// Vector[3]
//=====================================

typedef TVector<int, 3>    vec3i;
typedef TVector<float, 3>  vec3f;
typedef TVector<double, 3> vec3d;


// template <typename T, size_t N>
// TVector3<T, N>::TVector3()
//         : ThisType()
// {}

// template <typename T, size_t N>
// TVector3<T, N>::TVector3( const T& v )
//         : ThisType( v )
// {}

// template <typename T, size_t N>
// TVector3<T, N>::TVector3( T x, T y, T z )
// {
//     this->m_data = { x, y, z };
// }


//=====================================
// Vector[4]
//=====================================

typedef TVector<int, 4>    vec4i;
typedef TVector<float, 4>  vec4f;
typedef TVector<double, 4> vec4d;


}}  // namespace Yogi::math


#endif  // HPP_TVECTOR_MATH
