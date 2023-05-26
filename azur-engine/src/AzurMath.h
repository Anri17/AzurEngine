#ifndef _MATH_H
#define _MATH_H

#include "vector2float.h"

#include <cfloat>

namespace AzurMath
{
	// TODO: This is 100 digits of PI. Will C++ read all of the digis properly? I honestly do not know.
	const long double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679L;
	vector2float find_point_y(vector2float point0, vector2float point1, float point_x);
	vector2float find_point_x(vector2float point0, vector2float point1, float point_y);
	vector2float find_point_distance(vector2float point0, vector2float point1, float distance);
	float find_distance_between_points(vector2float point0, vector2float point1);
}

#endif // _MATH_H
