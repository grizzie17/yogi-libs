

#include "conversions.hpp"

#include <math.h>


namespace Yogi { namespace math {


float
normalizeDegrees( float degrees )
{
    if ( degrees < 0.0 )
        return ::fmodf( degrees, -360.0f );
    else
        return ::fmodf( degrees, 360.0f );
}

double
normalizeDegrees( double degrees )
{
    if ( degrees < 0.0 )
        return ::fmod( degrees, -360.0 );
    else
        return ::fmod( degrees, 360.0 );
}


}}  // namespace Yogi::math