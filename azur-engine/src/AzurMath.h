#ifndef _MATH_H
#define _MATH_H

#include "vector2float.h"

namespace AzurMath
{
	vector2float find_point_y(vector2float point0, vector2float point1, float point_x);
	vector2float find_point_x(vector2float point0, vector2float point1, float point_y);
	vector2float find_point_distance(vector2float point0, vector2float point1, float distance);
	float find_distance_between_points(vector2float point0, vector2float point1);
}

#endif // _MATH_H
