#include "gtest/gtest.h"

#include "math.hpp"

using namespace Yogi::math;

TEST( TMatrix, declareMat4d )
{
    mat4d m;

    for ( int i = 0; i < 4; ++i )
    {
        ASSERT_DOUBLE_EQ( 1.0, m[i][i] );
    }
}

TEST( TMatrix, declareTMatrix16 )
{
    TMatrix<double, 16> m;

    for ( int i = 0; i < 16; ++i )
        ASSERT_DOUBLE_EQ( static_cast<double>( 1.0 ), m[i][i] );
}

TEST( TMatrix, declareViaList )
{
    mat4d m( {
            0, 1, 2, 3,     //
            4, 5, 6, 7,     //
            8, 9, 10, 11,   //
            12, 13, 14, 15  //
    } );

    int v = 0;
    int j = 0;
    while ( j < 4 )
    {
        for ( int i = 0; i < 4; ++i )
        {
            ASSERT_DOUBLE_EQ( static_cast<double>( v ), m[j][i] );
            ++v;
        }
        ++j;
    }
}

TEST( TMatrix, add )
{
    mat4d m1( {
            0, 1, 2, 3,     //
            4, 5, 6, 7,     //
            8, 9, 10, 11,   //
            12, 13, 14, 15  //
    } );
    mat4d m2( {
            20, 21, 22, 23,  //
            24, 25, 26, 27,  //
            28, 29, 30, 31,  //
            32, 33, 34, 35   //
    } );
    mat4d result = m1 + m2;

    int v = 0;
    int x = 20;
    int j = 0;
    while ( j < 4 )
    {
        for ( int i = 0; i < 4; ++i )
        {
            ASSERT_DOUBLE_EQ( static_cast<double>( v + x ), result[j][i] );
            ++v;
            ++x;
        }
        ++j;
    }
}


TEST( TMatrix, subtract )
{
    mat4d m1( {
            0, 1, 2, 3,     //
            4, 5, 6, 7,     //
            8, 9, 10, 11,   //
            12, 13, 14, 15  //
    } );
    mat4d m2( {
            20, 21, 22, 23,  //
            24, 25, 26, 27,  //
            28, 29, 30, 31,  //
            32, 33, 34, 35   //
    } );
    mat4d result = m2 - m1;

    int v = 0;
    int x = 20;
    int j = 0;
    while ( j < 4 )
    {
        for ( int i = 0; i < 4; ++i )
        {
            ASSERT_DOUBLE_EQ( static_cast<double>( x - v ), result[j][i] );
            ++v;
            ++x;
        }
        ++j;
    }
}

TEST( TMatrix, multiply )
{
    mat3d m1( {} );
}

TEST( TMatrix, accessArray )
{
    mat3d m;
    m[0][2] = 10.0;
    m[1][1] = 5.0;
    m[2][0] = 1.0;

    ASSERT_DOUBLE_EQ( 1.0, m[0][0] );
    ASSERT_DOUBLE_EQ( 1.0, m[2][2] );
    ASSERT_DOUBLE_EQ( 10.0, m[0][2] );
    ASSERT_DOUBLE_EQ( 5.0, m[1][1] );
    ASSERT_DOUBLE_EQ( 1.0, m[2][0] );
}

TEST( TMatrix, translate )
{
    mat4d m;  // identity

    vec4d t( { 10.0, 5.0, 2.0, 1.0 } );

    m.translate( t );

    // m[0][3] = 10.0;  // x
    // m[1][3] = 5.0;   // y
    // m[2][3] = 2.0;   // z

    vec4d v( { 0, 0, 0, 1 } );

    vec4d result = m * v;

    ASSERT_DOUBLE_EQ( 10.0, result[0] );
    ASSERT_DOUBLE_EQ( 5.0, result[1] );
    ASSERT_DOUBLE_EQ( 2.0, result[2] );
    ASSERT_DOUBLE_EQ( 1.0, result[3] );
}

TEST( TMatrix, equality )
{
    mat3d m( {
            0, 1, 2,  //
            3, 4, 5,  //
            6, 7, 8   //
    } );
    mat3d t( m );

    ASSERT_TRUE( m.equals( t ) );
    ASSERT_TRUE( m == t );
}


TEST( TMatrix, transpose )
{
    mat3d m( {
            0, 1, 2,  //
            3, 4, 5,  //
            6, 7, 8   //
    } );
    mat3d t( {
            0, 3, 6,  //
            1, 4, 7,  //
            2, 5, 8   //
    } );

    m.transpose();

    ASSERT_TRUE( m == t );
}

// TEST( TMatrix, assignViaArray )
// {
//     TMa
// }