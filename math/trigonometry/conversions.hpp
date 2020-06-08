#ifndef HPP_CONVERSIONS_MATH
#define HPP_CONVERSIONS_MATH
#pragma once

#include "constants.hpp"

namespace Yogi { namespace math {


inline float
radiansFromDegrees( float degrees )
{
    return degrees * static_cast<float>( constants::PI ) / 180.0f;
}

inline double
radiansFromDegrees( double degrees )
{
    return degrees * constants::PI / 180.0;
}


inline float
degreesFromRadians( float radians )
{
    return radians * 180.0f / static_cast<float>( constants::PI );
}

inline double
degreesFromRadians( double radians )
{
    return radians * 180.0 / constants::PI;
}


float
normalizeDegrees( float degrees );
double
normalizeDegrees( double degrees );


}}  // namespace Yogi::math


#endif  // HPP_CONVERSIONS_MATH