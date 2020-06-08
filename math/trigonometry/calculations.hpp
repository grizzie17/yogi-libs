#ifndef HPP_CALCULATIONS_MATH
#define HPP_CALCULATIONS_MATH
#pragma once


#include <math.h>

namespace Yogi { namespace math {

// sqrt ===============================
template <typename T>
inline T
sqrt( T v )
{
    return ::sqrt( v );
}

template <>
inline double
sqrt<double>( double v )
{
    return ::sqrt( v );
}

template <>
inline long double
sqrt<long double>( long double v )
{
    return ::sqrtl( v );
}

template <>
inline float
sqrt<float>( float v )
{
    return ::sqrtf( v );
}


// abs ================================

template <typename T>
inline T
abs( T v )
{
    return ::fabs( v );
}

template <>
inline int
abs<int>( int v )
{
    return ::abs( v );
}

template <>
inline long
abs<long>( long v )
{
    return ::labs( v );
}

template <>
inline float
abs<float>( float v )
{
    return ::fabsf( v );
}

template <>
inline double
abs<double>( double v )
{
    return ::fabs( v );
}

template <>
inline long double
abs<long double>( long double v )
{
    return ::fabsl( v );
}


// equals =============================

#if false
template <typename T>
inline bool
operator==( T lhs, T rhs )
{
    return abs<T>( lhs - rhs ) <= std::numeric_limits<T>::epsilon();
}


template <>
inline bool
operator==( double lhs, double rhs )
{
    return abs<double>( lhs - rhs ) <= std::numeric_limits<double>::epsilon();
}


template <typename T>
inline bool
operator!=( T lhs, T rhs )
{
    return std::numeric_limits<T>::epsilon() < abs<T>( lhs - rhs );
}


template <>
inline bool
operator!=( double lhs, double rhs )
{
    return std::numeric_limits<double>::epsilon() < abs<double>( lhs - rhs );
}
#endif


}}  // namespace Yogi::math


#endif  // HPP_CALCULATIONS_MATH
