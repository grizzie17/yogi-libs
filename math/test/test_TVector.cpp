#include "gtest/gtest.h"

#include "math.hpp"

using namespace Yogi::math;


TEST( TVector, declareVecN )
{
    TVector<double, 5> v;
}

TEST( TVector, declareVec4d )
{
    vec4d v;

    for ( int i = 0; i < 4; ++i )
        ASSERT_DOUBLE_EQ( 0.0, v[i] );

    vec4d w { 1.0, 2.0, 3.0, 4.0 };
}

TEST( TVector, declareCtorValue )
{
    vec3d v( 1.0 );

    for ( int i = 0; i < 3; ++i )
        ASSERT_DOUBLE_EQ( 1.0, v[i] );
}

TEST( TVector, equals )
{
    vec3d v( { 1, 2, 3 } );
    vec3d t( v );

    ASSERT_TRUE( v == t );

    v[1] = 0;

    ASSERT_TRUE( v != t );
}

TEST( TVector, declareCtorXYZ )
{
    vec4d v( { 1.0, 2.0, 3.0 } );
}

TEST( TVector, assignArray )
{
    vec4i v;
    v.x = 5;
    v.y = 20;
    v[2] = 1;

    ASSERT_EQ( 5, v[0] );
    ASSERT_EQ( 20, v[1] );
    ASSERT_EQ( 1, v[2] );
}

TEST( TVector, negate )
{
    vec3d v = { 1, 2, 3 };

    vec3d result = -v;

    ASSERT_DOUBLE_EQ( -1.0, result.x );
    ASSERT_DOUBLE_EQ( -2.0, result.y );
    ASSERT_DOUBLE_EQ( -3.0, result.z );
}

TEST( TVector, length )
{
    vec3d v = { 1, 0, 0 };

    double n = v.length();

    ASSERT_DOUBLE_EQ( 1.0, n );
}